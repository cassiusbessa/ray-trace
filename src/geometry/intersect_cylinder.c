/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:55:20 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// --- Resolve a equação quadrática ax² + bx + c = 0 ---
t_roots solve_quadratic(float a, float b, float c)
{
    t_roots roots;
    float discriminant;
    float sqrt_disc;
    
    roots.valid = 0;
    roots.t1 = -1;
    roots.t2 = -1;

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return roots;  // Sem soluções reais

    sqrt_disc = sqrt(discriminant);
    roots.t1 = (-b - sqrt_disc) / (2 * a);
    roots.t2 = (-b + sqrt_disc) / (2 * a);
    roots.valid = 1;
    return roots;
}

// --- Verifica se o ponto está dentro da altura do cilindro ---
int is_within_cylinder_height(t_tuple point, t_cylinder c, t_tuple axis)
{
    t_tuple v;
    float h;

    v = subtract_tuple(point, c.position);
    h = vector_dot(v, axis);

    return (h >= 0 && h <= c.height) ? 1 : 0;
}

// --- Interseção do raio com o corpo lateral do cilindro ---
float intersect_cylinder_simple(t_ray ray, t_cylinder c)
{
    t_tuple co;
    t_tuple axis;
    t_tuple d;
    t_tuple oc;
    float a, b, c_coef;
    t_roots roots;
    int i = 0;
    float t;
    t_tuple hit;
    float roots_arr[2];

    co = subtract_tuple(ray.origin, c.position);
    axis = normalize_vector(c.orientation);
    d = subtract_tuple(ray.direction, multiply_tuple(axis, vector_dot(ray.direction, axis)));
    oc = subtract_tuple(co, multiply_tuple(axis, vector_dot(co, axis)));

    a = vector_dot(d, d);
    b = 2 * vector_dot(d, oc);
    c_coef = vector_dot(oc, oc) - (c.diameter / 2) * (c.diameter / 2);

    roots = solve_quadratic(a, b, c_coef);
    if (!roots.valid)
        return -1;

    roots_arr[0] = roots.t1;
    roots_arr[1] = roots.t2;

    while (i < 2)
    {
        t = roots_arr[i];
        if (t >= 0)
        {
            hit = add_tuple(ray.origin, multiply_tuple(ray.direction, t));
            if (is_within_cylinder_height(hit, c, axis))
                return t;
        }
        i++;
    }
    return -1;
}

// --- Interseção do raio com um disco (tampa do cilindro) ---
float intersect_disk(t_ray ray, t_tuple center, t_tuple axis, float radius)
{
    float denom;
    float t;
    t_tuple p;
    t_tuple v;

    denom = vector_dot(ray.direction, axis);
    if (fabs(denom) < EPSILON)
        return -1;

    t = vector_dot(subtract_tuple(center, ray.origin), axis) / denom;
    if (t < 0)
        return -1;

    p = add_tuple(ray.origin, multiply_tuple(ray.direction, t));
    v = subtract_tuple(p, center);

    if (magnitude_vector(v) <= radius)
        return t;

    return -1;
}

// --- Interseção do raio com as tampas (discos) do cilindro ---
float hit_caps(t_ray ray, t_cylinder c)
{
    t_tuple axis;
    t_tuple centers[2];
    float t;
    int i = 0;

    axis = normalize_vector(c.orientation);
    centers[0] = c.position;
    centers[1] = add_tuple(c.position, multiply_tuple(axis, c.height));

    while (i < 2)
    {
        t = intersect_disk(ray, centers[i], axis, c.diameter / 2);
        if (t >= 0)
            return t;
        i++;
    }
    return -1;
}

// --- Interseção total do raio com o cilindro (corpo + tampas) ---
float cylinder_intersect(t_ray ray, t_cylinder c)
{
    float t_body;
    float t_cap;

    t_body = intersect_cylinder_simple(ray, c);  // ou hit_body, se tiver
    t_cap = hit_caps(ray, c);

    if (t_body > 0 && (t_cap < 0 || t_body < t_cap))
        return t_body;

    if (t_cap > 0)
        return t_cap;

    return -1;
}

// --- Calcula a normal no ponto de interseção com o cilindro ---
t_tuple get_normal_cylinder(t_cylinder c, t_tuple point)
{
    t_tuple axis;
    t_tuple base_to_point;
    float projection;
    t_tuple proj;
    t_tuple normal;

    axis = normalize_vector(c.orientation);
    base_to_point = subtract_tuple(point, c.position);
    projection = vector_dot(base_to_point, axis);

    if (projection <= EPSILON)
        return multiply_tuple(axis, -1);

    if (projection >= c.height - EPSILON)
        return axis;

    proj = multiply_tuple(axis, projection);
    normal = subtract_tuple(base_to_point, proj);
    return normalize_vector(normal);
}

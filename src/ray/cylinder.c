/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/07 13:00:25 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder cylinder(void)
{
    t_cylinder c;

    c.position = point_tuple(0, 0, 0);
    c.orientation = vector_tuple(0, 1, 0);  // eixo Y padrão
    c.diameter = 1.0f;
    c.height = 1.0f;
    c.color = create_color(1, 1, 1); // branco padrão, ou o que quiser

    return c;
}


static int check_side_intersections(t_cylinder *cyl, t_ray ray,
    float t0, float t1, t_intersection *xs, int idx)
{
    t_tuple axis;
    t_tuple p0;
    t_tuple p1;
    float y0;
    float y1;

    axis = normalize_vector(cyl->orientation);

    p0 = add_tuple(ray.origin, multiply_tuple(ray.direction, t0));
    y0 = vector_dot(subtract_tuple(p0, cyl->position), axis);
    if (y0 >= 0 && y0 <= cyl->height)
    {
        xs[idx].t = t0;
        xs[idx].object = cyl;
        idx++;
    }

    p1 = add_tuple(ray.origin, multiply_tuple(ray.direction, t1));
    y1 = vector_dot(subtract_tuple(p1, cyl->position), axis);
    if (y1 >= 0 && y1 <= cyl->height)
    {
        xs[idx].t = t1;
        xs[idx].object = cyl;
        idx++;
    }
    return idx;
}


static int solve_cylinder_quadratic(t_cylinder *cyl, t_ray ray, float *t0, float *t1)
{
    float radius = cyl->diameter / 2.0f;
    t_tuple axis = normalize_vector(cyl->orientation);
    t_tuple co = subtract_tuple(ray.origin, cyl->position);

    t_tuple d_proj = subtract_tuple(ray.direction,
                                    multiply_tuple(axis, vector_dot(ray.direction, axis)));
    t_tuple co_proj = subtract_tuple(co,
                                     multiply_tuple(axis, vector_dot(co, axis)));

    float a = vector_dot(d_proj, d_proj);
    float b = 2.0f * vector_dot(d_proj, co_proj);
    float c = vector_dot(co_proj, co_proj) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return 0; // sem solução

    float sqrt_disc = sqrtf(discriminant);
    *t0 = (-b - sqrt_disc) / (2 * a);
    *t1 = (-b + sqrt_disc) / (2 * a);

    return 1; // soluções válidas
}


static int check_cap_intersection(t_cylinder *cyl, t_ray ray,
                                  float cap_height,
                                  t_intersection *xs, int idx)
{
    float radius = cyl->diameter / 2.0f;
    t_tuple axis = normalize_vector(cyl->orientation);

    float denom = vector_dot(ray.direction, axis);
    if (fabs(denom) < EPSILON)
        return idx;

    float t = (cap_height - vector_dot(subtract_tuple(ray.origin, cyl->position), axis)) / denom;
    if (t < 0)
        return idx;

    t_tuple p = add_tuple(ray.origin, multiply_tuple(ray.direction, t));
    t_tuple center = add_tuple(cyl->position, multiply_tuple(axis, cap_height));
    t_tuple v = subtract_tuple(p, center);

    if (vector_dot(v, v) <= radius * radius)
    {
        xs[idx].t = t;
        xs[idx].object = cyl;
        idx++;
    }
    return idx;
}

t_intersection *intersect_cylinder(t_cylinder *cyl, t_ray ray, int *count)
{
    float t0, t1;
    *count = 0;

    if (!solve_cylinder_quadratic(cyl, ray, &t0, &t1))
        return NULL;

    t_intersection *xs = malloc(4 * sizeof(t_intersection));
    if (!xs)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    idx = check_side_intersections(cyl, ray, t0, t1, xs, idx);
    idx = check_cap_intersection(cyl, ray, 0.0f, xs, idx);
    idx = check_cap_intersection(cyl, ray, cyl->height, xs, idx);

    if (idx == 0)
    {
        free(xs);
        return NULL;
    }

    *count = idx;
    return xs;
}

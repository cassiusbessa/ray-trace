/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 20:01:37 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_ray get_local_ray_sphere(t_ray ray, t_object *obj, int *success)
{
    t_matrix inv;
    t_ray local_ray;

    inv = invert_matrix(obj->transform, success);
    if (!*success)
        return ray;

    local_ray = transform_ray(ray, inv, success);
    free_matrix(inv);
    return local_ray;
}

static float compute_sphere_discriminant(t_ray local_ray, float *a, float *b, float *c)
{
    t_tuple sphere_to_ray;

    sphere_to_ray = local_ray.origin;

    *a = vector_dot_product(local_ray.direction, local_ray.direction);
    *b = 2.0f * vector_dot_product(local_ray.direction, sphere_to_ray);
    *c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1.0f;

    return (*b) * (*b) - 4 * (*a) * (*c);
}

static void add_sphere_intersections(float discriminant, float a, float b,
                                     t_intersection_list *list, t_object *obj)
{
    float sqrt_disc;
    float t1;
    float t2;

    if (discriminant < 0.0f)
        return;

    sqrt_disc = sqrtf(discriminant);
    t1 = (-b - sqrt_disc) / (2 * a);
    t2 = (-b + sqrt_disc) / (2 * a);
    add_node_ordered(t1, list, obj);
    add_node_ordered(t2, list, obj);
}

t_intersection_list *intersect_ray_sphere(t_ray ray, t_object *obj)
{
    t_ray   local_ray;
    t_intersection_list *list;
    float a;
    float b;
    float c;
    float discriminant;
    int success = 0;

    local_ray = get_local_ray_sphere(ray, obj, &success);
    if (!success)
        return new_intersection_list();

    discriminant = compute_sphere_discriminant(local_ray, &a, &b, &c);

    list = new_intersection_list();
    if (!list)
        return NULL;

    add_sphere_intersections(discriminant, a, b, list, obj);

    return list;
}

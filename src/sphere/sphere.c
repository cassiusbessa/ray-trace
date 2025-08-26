/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 20:38:48 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_sphere	new_sphere(t_tuple center, float radius)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.transform = identity_matrix(4);
	sphere.material = new_material_default();
	return (sphere);
}

t_intersection_list *intersect_ray_sphere(t_ray ray, t_object *obj)
{
    t_sphere *sphere = (t_sphere *)obj->data;
    t_ray local_ray;
    t_intersection_list *l;
    float a, b, c, discriminant;

    int success;
    t_matrix inv = invert_matrix(sphere->transform, &success);
    if (!success)
    {
        return new_intersection_list();
    }

    local_ray = transform_ray(ray, inv, &success);
    if (!success)
    {
        return new_intersection_list();
    }

    t_tuple sphere_to_ray = local_ray.origin;

    a = vector_dot_product(local_ray.direction, local_ray.direction);
    b = 2.0f * vector_dot_product(local_ray.direction, sphere_to_ray);
    c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1.0f;

    discriminant = b*b - 4*a*c;

    l = new_intersection_list();
    if (!l)
        return NULL;

    if (discriminant < 0.0f)
    {
        return l;
    }

    float sqrt_disc = sqrtf(discriminant);
    float t1 = (-b - sqrt_disc) / (2*a);
    float t2 = (-b + sqrt_disc) / (2*a);

    add_node_ordered(t1, l, obj);
    add_node_ordered(t2, l, obj);

    return l;
}


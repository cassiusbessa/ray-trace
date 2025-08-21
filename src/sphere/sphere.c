/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/08/21 03:00:37 by cassius          ###   ########.fr       */
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

t_intersection_list *intersect_ray_sphere(t_ray ray, t_sphere *sphere)
{
    t_tuple oc;
    t_quad q;
    t_intersection i;
    t_intersection_list *l;
    float a, b, c;
    t_ray local_ray;

    // 1. Transforma o raio para o espaço do objeto
    local_ray = transform_ray(ray, invert_matrix(sphere->transform));

    // 2. Calcula normalmente
    oc = sub_tuples(local_ray.origin, sphere->center);
    a = vector_dot_product(local_ray.direction, local_ray.direction);
    b = 2.0f * vector_dot_product(local_ray.direction, oc);
    c = vector_dot_product(oc, oc) - (sphere->radius * sphere->radius);

    q = ft_quadratic(a, b, c);

    // 3. Transforma em interseção
    i = ft_quad_to_intersection(q, (void *)sphere);

    l = new_intersection_list();
    if (!l)
        return (NULL);
    add_intersection_to_list(l, i);
    return (l);
}


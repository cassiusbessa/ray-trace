/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 09:39:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_sphere new_sphere(t_tuple center, float radius)
{
    t_sphere sphere;

    sphere.center = center;
    sphere.radius = radius;

    return sphere;
}

t_intersection intersect_ray_sphere(t_ray ray, t_sphere *sphere)
{
    // Declarando variáveis
    t_tuple oc;
    float a, b, c;
    t_quad q;
	t_intersection i;

    // Inicializando
    oc = sub_tuples(ray.origin, sphere->center);
    a = vector_dot_product(ray.direction, ray.direction);
    b = 2.0f * vector_dot_product(ray.direction, oc);
    c = vector_dot_product(oc, oc) - (sphere->radius * sphere->radius);

    q = ft_quadratic(a, b, c);

	i = ft_quad_to_intersection(q, (void *)sphere);

	return (i);
}

int intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out)
{
    if (!ray || !obj || !out)
        return 0;
    *out = intersect_ray_sphere(*ray, (t_sphere *)obj->data);
    return (out->count > 0);
}

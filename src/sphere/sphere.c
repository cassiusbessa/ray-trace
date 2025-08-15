/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 21:17:31 by cassius          ###   ########.fr       */
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

t_intersection	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_tuple	oc;
	float	a;
	float	b;
	float	c;

	oc = sub_tuples(ray.origin, sphere.center);
	a = vector_dot_product(ray.direction, ray.direction);
	b = 2.0f * vector_dot_product(ray.direction, oc);
	c = vector_dot_product(oc, oc) - (sphere.radius * sphere.radius);
	return (ft_quad_to_intersection(ft_quadratic(a, b, c)));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/08/21 01:46:33 by cassius          ###   ########.fr       */
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

t_intersection_list	*intersect_ray_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple			oc;
	t_quad			q;
	t_intersection	i;
	t_intersection_list *l;

	float a, b, c;
	oc = sub_tuples(ray.origin, sphere->center);
	a = vector_dot_product(ray.direction, ray.direction);
	b = 2.0f * vector_dot_product(ray.direction, oc);
	c = vector_dot_product(oc, oc) - (sphere->radius * sphere->radius);
	q = ft_quadratic(a, b, c);
	i = ft_quad_to_intersection(q, (void *)sphere);
	l = new_intersection_list();
	if (!l)
		return (NULL);
	add_intersection_to_list(l, i);
	return (l);
}

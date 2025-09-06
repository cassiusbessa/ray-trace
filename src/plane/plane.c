/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/06 00:08:55 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_plane	*new_plane(t_tuple point, t_tuple normal)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = point;
	plane->normal = safe_normalize_vector(normal);
	return (plane);
}

static double	compute_plane_t(t_plane *plane, t_ray ray)
{
	double	denom;
	double	t;

	denom = vector_dot_product(plane->normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (-1);
	t = vector_dot_product(plane->normal, sub_tuples(plane->point, ray.origin)) / denom;
	if (t < 0)
		return (-1);
	return (t);
}

t_intersection_list	*intersect_ray_plane(t_ray ray, t_object *obj)
{
	t_plane *plane;
	double  t;
	t_intersection_list *list;
	t_intersection  inter;

	plane = (t_plane *)obj->data;
	t = compute_plane_t(plane, ray);
	if (t < 0)
		return NULL;
	list = new_intersection_list();
	if (!list)
		return NULL;
	inter = new_intersection(1, t, 0, obj);
	add_intersection_to_list(list, inter);
	return (list);
}

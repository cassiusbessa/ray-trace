/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:37:54 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 23:42:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	normal_at_sphere(t_object *obj, t_tuple world_point)
{
	t_matrix	inv;
	t_matrix	inv_t;
	t_tuple		object_point;
	t_tuple		object_normal;
	t_tuple		world_normal;
	int			success;

	inv = invert_matrix(obj->transform, &success);
	if (!success || !inv.data)
		return (vector(0, 0, 0));
	object_point = matrix_multiply_by_tuple(inv, world_point);
	object_normal = sub_tuples(object_point, point(0, 0, 0));
	object_normal.w = 0;
	inv_t = transpose_matrix(inv);
	world_normal = matrix_multiply_by_tuple(inv_t, object_normal);
	world_normal.w = 0;
	world_normal = safe_normalize_vector(world_normal);
	free_matrix(inv_t);
	free_matrix(inv);
	return (world_normal);
}

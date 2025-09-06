/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:38:27 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 19:32:00 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_bool	local_normal_cylinder_cap(t_cylinder *cyl, t_tuple local_point,
		t_tuple *normal)
{
	float	dist;
	float	epsilon;

	dist = local_point.x * local_point.x + local_point.z * local_point.z;
	epsilon = 1e-4f;
	if (!cyl->closed || dist > cyl->radius * cyl->radius)
		return (0);
	if (local_point.y >= cyl->height / 2.0f - epsilon)
		*normal = vector(0, 1, 0);
	else if (local_point.y <= -cyl->height / 2.0f + epsilon)
		*normal = vector(0, -1, 0);
	else
		return (0);
	return (1);
}

static t_tuple	local_normal_cylinder_side(t_tuple local_point)
{
	t_tuple	lateral;

	lateral = vector(local_point.x, 0, local_point.z);
	if (vector_dot_product(lateral, lateral) < 0)
		lateral = vector(-lateral.x, 0, -lateral.z);
	return (safe_normalize_vector(lateral));
}

static t_tuple	transform_local_to_world_normal(t_matrix transform,
		t_tuple local_normal)
{
	t_matrix	trans_inv;
	t_tuple		world_normal;

	trans_inv = transpose_matrix(transform);
	world_normal = matrix_multiply_by_tuple(trans_inv, local_normal);
	world_normal.w = 0;
	world_normal = safe_normalize_vector(world_normal);
	free_matrix(trans_inv);
	return (world_normal);
}

t_tuple	normal_at_cylinder(t_object *obj, t_tuple world_point)
{
	int			success;
	t_matrix	inv;
	t_cylinder	*cyl;
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;

	inv = invert_matrix(obj->transform, &success);
	if (!success || !inv.data)
		return (vector(0, 0, 0));
	local_point = matrix_multiply_by_tuple(inv, world_point);
	cyl = (t_cylinder *)obj->data;
	if (!local_normal_cylinder_cap(cyl, local_point, &local_normal))
		local_normal = local_normal_cylinder_side(local_point);
	world_normal = transform_local_to_world_normal(inv, local_normal);
	free_matrix(inv);
	return (world_normal);
}

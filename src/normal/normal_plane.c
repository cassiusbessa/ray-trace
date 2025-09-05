/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:39:08 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:59:27 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_tuple transform_normal_to_world(t_object *obj, t_tuple local_normal)
{
    t_matrix inv;
    t_matrix invT;
    t_tuple world_normal;
    int success;

    inv = invert_matrix(obj->transform, &success);
    if (!success || !inv.data)
        return vector(0, 0, 0);

    invT = transpose_matrix(inv);
    world_normal = matrix_multiply_by_tuple(invT, local_normal);
    world_normal.w = 0;
    world_normal = safe_normalize_vector(world_normal);

    free_matrix(inv);
    free_matrix(invT);

    return world_normal;
}

t_tuple normal_at_plane(t_object *obj, t_tuple world_point)
{
    t_plane *plane;
    t_tuple local_normal;

    (void)world_point;

    plane = (t_plane *)obj->data;
    local_normal = plane->normal;
    local_normal.w = 0;

    return transform_normal_to_world(obj, local_normal);
}



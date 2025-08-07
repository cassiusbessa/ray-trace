/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:57:37 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple get_normal_plane(t_plane plane)
{
    return normalize_vector(plane.normal);
}

float intersect_plane_simple(t_ray ray, t_plane plane)
{
    float denom;
    float t;
    t_tuple diff;

    denom = vector_dot(ray.direction, plane.normal);
    if (fabs(denom) < EPSILON)
        return -1;
    diff = subtract_tuple(plane.position, ray.origin);
    t = vector_dot(diff, plane.normal) / denom;
    if (t < EPSILON)
        return -1;
    return (t);
}

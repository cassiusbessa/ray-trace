/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:36:49 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:39:51 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	normal_at(t_object *obj, t_tuple world_point)
{
	if (!obj)
		return (vector(0, 0, 0));
	if (obj->type == SPHERE)
		return (normal_at_sphere(obj, world_point));
	else if (obj->type == CYLINDER)
		return (normal_at_cylinder(obj, world_point));
	else if (obj->type == PLANE)
		return (normal_at_plane(obj, world_point));
	return (vector(0, 0, 0));
}

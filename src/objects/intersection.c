/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 20:24:06 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


#include "miniRT.h"

int intersect_object(t_ray *ray, t_object *obj, t_intersection *out)
{
	if (!obj)
		return (0);
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, obj, out));
	if (obj->type == PLANE)
		return (intersect_plane(ray, obj, out));
	if (obj->type == CYLINDER)
		return (intersect_cylinder(ray, obj, out));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/09/04 09:30:23 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection	new_intersection(int count, float enter, float exit,
		void *object)
{
	t_intersection	result;

	result.count = count;
	result.enter = enter;
	result.exit = exit;
	result.object = object;
	return (result);
}

t_intersection_list *intersect(t_ray ray, t_object *object)
{
    if (object->type == SPHERE)
        return intersect_ray_sphere(ray, object);
    else if (object->type == CYLINDER)
        return intersect_ray_cylinder(ray, object);
    else if (object->type == PLANE)
        return intersect_ray_plane(ray, object);
    return NULL;
}


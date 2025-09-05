/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 17:50:17 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	add_node_ordered(float t, t_intersection_list *list, t_object *o)
{
	t_intersection_node	*n;

	if (!list)
		return ;
	n = malloc(sizeof(t_intersection_node));
	if (!n)
		return ;
	n->t = t;
	n->object = o;
	n->next = NULL;
	if (!list->head)
	{
		list->head = n;
		list->tail = n;
		list->count = 1;
		return ;
	}
	add(n, list);
}

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

t_intersection_list	*intersect(t_ray ray, t_object *object)
{
	if (object->type == SPHERE)
		return (intersect_ray_sphere(ray, object));
	else if (object->type == CYLINDER)
		return (intersect_ray_cylinder(ray, object));
	else if (object->type == PLANE)
		return (intersect_ray_plane(ray, object));
	return (NULL);
}

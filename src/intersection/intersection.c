/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:28:13 by cassius          ###   ########.fr       */
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

static void intersect_object_with_ray(t_intersection_list *dest,
    t_ray *ray,
    t_object *object)
{
    t_intersection_list *src;
    t_intersection_node *node;

    src = intersect(*ray, object);
    if (!src)
    return;
    node = src->head;
    while (node)
    {
        add_node_ordered(node->t, dest, node->object);
        node = node->next;
    }
    free_intersection_list(src);
}

t_intersection_list *intersect_world(t_world *world, t_ray *ray)
{
    t_intersection_list *dest;
    t_object_node   *current_obj;

    if (!world || !ray || !world->objects || !world->objects->head)
        return NULL;

    dest = new_intersection_list();
    if (!dest)
        return NULL;
    current_obj = world->objects->head;
    while (current_obj)
    {
        intersect_object_with_ray(dest, ray, &current_obj->object);
        current_obj = current_obj->next;
    }
    return dest;
}


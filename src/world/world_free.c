/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:30:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:18:53 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_object_node(t_object_node *node)
{
	if (!node)
		return ;
	free_object(&node->object);
	free(node);
}

void	free_light_node(t_point_light_node *node)
{
	if (!node)
		return ;
	free(node);
}

static void	free_object_list(t_object_list *objects)
{
	t_object_node	*curr_obj;
	t_object_node	*next;

	if (!objects)
		return ;
	curr_obj = objects->head;
	while (curr_obj)
	{
		next = curr_obj->next;
		free_object_node(curr_obj);
		curr_obj = next;
	}
	free(objects);
}

static void	free_light_list(t_point_light_list *lights)
{
	t_point_light_node	*curr_light;
	t_point_light_node	*next;

	if (!lights)
		return ;
	curr_light = lights->head;
	while (curr_light)
	{
		next = curr_light->next;
		free_light_node(curr_light);
		curr_light = next;
	}
	free(lights);
}

void	free_world(t_world *world)
{
	if (!world)
		return ;
	free_object_list(world->objects);
	free_light_list(world->lights);
}

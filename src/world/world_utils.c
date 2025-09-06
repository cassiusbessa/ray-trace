/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:22:38 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	add_object_to_world(t_world *world, t_object obj)
{
	t_object_node	*on;

	on = malloc(sizeof(t_object_node));
	if (!on)
		return ;
	on->object = obj;
	on->next = NULL;
	if (!world->objects->head)
		world->objects->head = on;
	else
		world->objects->tail->next = on;
	world->objects->tail = on;
	world->objects->count++;
}

void	add_light_to_world(t_world *world, t_point_light light)
{
	t_point_light_node	*ln;

	ln = malloc(sizeof(t_point_light_node));
	if (!ln)
		return ;
	ln->light = light;
	ln->next = NULL;
	if (!world->lights->head)
		world->lights->head = ln;
	else
		world->lights->tail->next = ln;
	world->lights->tail = ln;
	world->lights->count++;
}

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

void	free_world(t_world *world)
{
	t_object_node		*curr_obj;
	t_object_node		*next;
	t_point_light_node	*curr_light;
	t_point_light_node	*next;

	if (!world)
		return ;
	if (world->objects)
	{
		curr_obj = world->objects->head;
		while (curr_obj)
		{
			next = curr_obj->next;
			free_object_node(curr_obj);
			curr_obj = next;
		}
		free(world->objects);
	}
	if (world->lights)
	{
		curr_light = world->lights->head;
		while (curr_light)
		{
			next = curr_light->next;
			free_light_node(curr_light);
			curr_light = next;
		}
		free(world->lights);
	}
}

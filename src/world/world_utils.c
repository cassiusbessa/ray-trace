/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:18:53 by cassius          ###   ########.fr       */
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

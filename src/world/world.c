/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 21:06:08 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_world	new_world(void)
{
	t_world	world;

	world.objects = malloc(sizeof(t_object_list));
	world.objects->count = 0;
	world.lights = malloc(sizeof(t_point_light_list));
	world.lights->count = 0;
	if (!world.objects || !world.lights)
	{
		free(world.objects);
		free(world.lights);
		world.objects = NULL;
		world.lights = NULL;
		return (world);
	}
	world.objects->head = NULL;
	world.objects->tail = NULL;
	world.lights->head = NULL;
	world.lights->tail = NULL;
	return (world);
}

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

void	free_world(t_world *world)
{
	t_object_node		*on;
	t_point_light_node	*ln;
	t_object_node		*tmp_obj;
	t_point_light_node	*tmp_light;

	on = world->objects->head;
	while (on)
	{
		tmp_obj = on;
		on = on->next;
		free(tmp_obj);
	}
	free(world->objects);
	ln = world->lights->head;
	while (ln)
	{
		tmp_light = ln;
		ln = ln->next;
		free(tmp_light);
	}
	free(world->lights);
}

t_world	default_world(void)
{
	t_world			world;
	t_object		obj1;
	t_sphere		s;
	t_point_light	light;

	world = new_world();
	light = new_point_light(point(-10, 10, -10), new_rgb(1.0f, 1.0f, 1.0f));
	s = new_sphere(point(0, 0, 0), 1.0f);
	obj1.type = SPHERE;
	obj1.data = &s;
	add_object_to_world(&world, obj1);
	set_object_transform(&obj1, scaling_matrix(0.5f, 0.5f, 0.5f));
	add_object_to_world(&world, obj1);
	add_light_to_world(&world, light);
	return (world);
}

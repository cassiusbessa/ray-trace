/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 22:33:36 by cassius          ###   ########.fr       */
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
	world.ambient.ratio = 0.1f;
	world.ambient.color = new_rgb(1.0f, 1.0f, 1.0f);
	return (world);
}

t_world	new_world_with_ambient(t_ambient ambient)
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
	world.ambient = ambient;
	return (world);
}

t_world	default_world(void)
{
	t_world		world;
	t_sphere	*s1;
	t_object	o1;
	t_sphere	*s2;
	t_object	o2;

	world = new_world();
	add_light_to_world(&world, new_point_light(point(-10, 10, -10),
			new_rgb(1.0f, 1.0f, 1.0f)));
	s1 = malloc(sizeof(t_sphere));
	*s1 = new_sphere(point(0, 0, 0), 1.0f);
	o1 = new_object(SPHERE, s1);
	o1.material.color = new_rgb(0.8f, 1.0f, 0.6f);
	o1.material.diffuse = 0.7f;
	o1.material.specular = 0.2f;
	add_object_to_world(&world, o1);
	s2 = malloc(sizeof(t_sphere));
	*s2 = new_sphere(point(0, 0, 0), 1.0f);
	o2 = new_object(SPHERE, s2);
	set_object_transform(&o2, scaling_matrix(0.5f, 0.5f, 0.5f));
	add_object_to_world(&world, o2);
	return (world);
}

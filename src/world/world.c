/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/28 21:32:29 by cassius          ###   ########.fr       */
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


void free_object_node(t_object_node *node)
{
    if (!node)
        return;
    free_object(&node->object);
    free(node);
}

void free_light_node(t_point_light_node *node)
{
    if (!node)
        return;
    free(node);
}

void free_world(t_world *world)
{
    if (!world)
        return;
    if (world->objects)
    {
        t_object_node *curr_obj = world->objects->head;
        while (curr_obj)
        {
            t_object_node *next = curr_obj->next;
            free_object_node(curr_obj);
            curr_obj = next;
        }
        free(world->objects);
    }
    if (world->lights)
    {
        t_point_light_node *curr_light = world->lights->head;
        while (curr_light)
        {
            t_point_light_node *next = curr_light->next;
            free_light_node(curr_light);
            curr_light = next;
        }
        free(world->lights);
    }
}


t_world default_world(void)
{
    t_world world = new_world();

    // Adiciona luz principal
    add_light_to_world(&world,
        new_point_light(point(-10, 10, -10), new_rgb(1.0f, 1.0f, 1.0f))
    );

    // Primeira esfera (com material ajustado)
    t_sphere *s1 = malloc(sizeof(t_sphere));
    *s1 = new_sphere(point(0, 0, 0), 1.0f);

    s1->material.color = new_rgb(0.8f, 1.0f, 0.6f);
    s1->material.diffuse = 0.7f;
    s1->material.specular = 0.2f;

    t_object o1 = {.type = SPHERE, .data = s1};
    add_object_to_world(&world, o1);

    // Segunda esfera (escala 0.5)
    t_sphere *s2 = malloc(sizeof(t_sphere));
    *s2 = new_sphere(point(0, 0, 0), 1.0f);
    s2->transform = scaling_matrix(0.5f, 0.5f, 0.5f);
    t_object o2 = {.type = SPHERE, .data = s2};
    add_object_to_world(&world, o2);

    return world;
}

t_canvas    *render(t_camera cam, t_world *w)
{
    t_canvas *image;
    int     x;
    int     y;
    t_ray   ray;
    t_rgb   color;

    image = new_canvas(cam.hsize, cam.vsize);
    x = 0;
    y = 0;
    while (y < cam.vsize)
    {
        x = 0;
        while (x < cam.hsize)
        {
            ray = ray_for_pixel(cam, x, y);
            color = color_at(w, ray);         
            write_pixel(image, x, y, color);     
            x++;
        }
        y++;
    }
    return image;
}
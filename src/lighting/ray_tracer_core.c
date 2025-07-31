/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/31 17:24:00 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	shade_hit(t_world *world, t_intersection *hit, t_ray ray)
{
	t_material				*material;
	t_tuple					position_pt;
	t_tuple					normalv;
	t_tuple					eyev;
	int						in_shadow;
	t_material_light_params	mlp;
	t_lighting_context		ctx;
	t_color					result;

	material = &hit->object->material;
	position_pt = position(ray, hit->t);
	normalv = compute_normal(hit->object, position_pt);
	eyev = negate_tuple(ray.direction);
	in_shadow = is_shadowed(world, position_pt);

	mlp.material = *material;
	mlp.light = world->light;

	ctx.position = position_pt;
	ctx.eyev = eyev;
	ctx.normalv = normalv;
	ctx.in_shadow = in_shadow;

	result = lighting(mlp, ctx);
	return (result);
}


t_color	color_at(t_world *world, t_ray ray)
{
	int				count;
	t_intersection	*intersections;
	t_intersection	*hit_intersec;
	t_color			result;

	count = 0;
	intersections = intersect_world(world, ray, &count);
	hit_intersec = hit(intersections, count);
	if (hit_intersec)
		result = shade_hit(world, hit_intersec, ray);
	else
		result = color(0, 0, 0); // cor do fundo
	free(intersections);
	return (result);
}


t_tuple	compute_normal(t_sphere *sphere, t_tuple world_point)
{
	t_matrix	inv;
	t_tuple		object_point;
	t_tuple		object_normal;
	t_matrix	inv_transpose;
	t_tuple		world_normal;

	inv = matrix_inverse(sphere->transform);
	object_point = matrix_multiply_by_tuple(inv, world_point);
	object_normal = subtract_tuple(object_point, point_tuple(0, 0, 0));
	inv_transpose = transpose_matrix(inv);
	world_normal = matrix_multiply_by_tuple(inv_transpose, object_normal);
	world_normal.w = 0; // garante que seja vetor
	return (normalize_vector(world_normal));
}


int	is_shadowed(t_world *world, t_tuple point)
{
	t_tuple			lightv;
	float			distance;
	t_tuple			direction;
	t_ray			r;
	int				count;
	t_intersection	*intersections;
	t_intersection	*hit_intersec;
	int				shadowed;

	lightv = subtract_tuple(world->light.position, point);
	distance = magnitude_vector(lightv);
	direction = normalize_vector(lightv);
	r = ray(point, direction);

	count = 0;
	intersections = intersect_world(world, r, &count);
	hit_intersec = hit(intersections, count);

	shadowed = (hit_intersec != NULL && hit_intersec->t < distance);

	free(intersections);
	return (shadowed);
}



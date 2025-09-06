/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:15:39 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	safe_normalize_vector(t_tuple v)
{
	float	mag;
	t_tuple	result;

	mag = 0.0f;
	result = vector(0, 0, 0);
	mag = magnitude_of_vector(v);
	if (mag < EPSILON)
		result = vector(0, 0, 0);
	else
		result = multiply_tuple_by_scalar(v, 1.0f / mag);
	return (result);
}

static t_rgb	ambient_light_contribution(t_world *world, t_material *mat)
{
	t_rgb	result;

	result = multiply_rgb_by_scalar(multiply_rgb_by_rgb(mat->color,
				world->ambient.color), mat->ambient * world->ambient.ratio);
	return (result);
}

static t_rgb	light_contribution(t_world *world, t_material *mat,
		t_point_light light, t_comps comps)
{
	t_lighting_params	params;
	t_rgb				contribution;

	params.position = comps.point;
	params.eyev = comps.eyev;
	params.normalv = comps.normalv;
	params.in_shadow = is_shadowed(world, comps.over_point);
	contribution = lighting_no_ambient(*mat, light, params);
	return (contribution);
}

t_rgb	shade_hit(t_world *world, t_comps comps)
{
	t_material			*mat;
	t_rgb				color;
	t_point_light_node	*current;

	mat = &comps.object->material;
	color = ambient_light_contribution(world, mat);
	current = world->lights->head;
	while (current)
	{
		color = add_rgb(color, light_contribution(world, mat, current->light,
					comps));
		current = current->next;
	}
	return (color);
}

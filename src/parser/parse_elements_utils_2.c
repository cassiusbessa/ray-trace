/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:06:34 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:07:36 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	validate_sphere_params(char **tokens, float radius)
{
	if (!validate_parameter_count(tokens, "Sphere", 4))
		return (0);
	if (radius <= 0)
		return (0);
	return (1);
}

static t_object	create_sphere_object(t_tuple center, float radius, t_rgb color)
{
	t_sphere	*sphere;
	t_object	obj;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		obj.data = NULL;
		return (obj);
	}
	*sphere = new_sphere(point(0, 0, 0), 1.0);
	obj = new_object(SPHERE, sphere);
	obj.material.color = color;
	set_object_transform(&obj, scaling_matrix(radius, radius, radius));
	set_object_transform(&obj, translation_matrix(center.x, center.y,
			center.z));
	return (obj);
}

int	parse_sphere(char *line, t_world *world)
{
	char **tokens;
	t_tuple center;
	float radius;
	t_rgb color;

	tokens = ft_split(line, ' ');
	center = parse_tuple(tokens[1], 1);
	radius = parse_float(tokens[2]);
	if (!validate_sphere_params(tokens, radius))
		return (destroy_2d((void **)tokens), 0);
	if (!validate_and_parse_rgb(tokens[3], &color))
		return (destroy_2d((void **)tokens), 0);
	add_object_to_world(world, create_sphere_object(center, radius, color));
	destroy_2d((void **)tokens);
	return (1);
}
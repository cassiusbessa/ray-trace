/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 20:18:13 by cassius          ###   ########.fr       */
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
	set_object_transform(&obj, translation_matrix(center.x, center.y, center.z));
	return (obj);
}

int	parse_sphere(char *line, t_world *world)
{
	char		**tokens;
	t_tuple		center;
	float		radius;
	t_rgb		color;

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

static int	validate_cylinder_params(char **tokens, float diameter, float height)
{
	if (!validate_parameter_count(tokens, "Cylinder", 7))
		return (0);
	if (diameter <= 0)
		return (0);
	if (height <= 0)
		return (0);
	return (1);
}

int	parse_cylinder_continue(char **tokens, t_world *world, t_cylinder_data data)
{
	t_rgb		color;
	t_bool		closed;
	t_object	obj;

	if (!validate_and_parse_rgb(tokens[5], &color))
		return (destroy_2d((void **)tokens), 0);
	closed = ft_atoi(tokens[6]) != 0;
	obj = new_cylinder_object(data.center, data.orientation, data.diameter,
			data.height, color, closed);
	add_object_to_world(world, obj);
	destroy_2d((void **)tokens);
	return (1);
}

int	parse_cylinder(char *line, t_world *world)
{
	char			**tokens;
	t_cylinder_data	data;

	tokens = ft_split(line, ' ');
	data.center = parse_tuple(tokens[1], 1);
	data.orientation = normalize_vector(parse_tuple(tokens[2], 0));
	data.diameter = parse_float(tokens[3]);
	data.height = parse_float(tokens[4]);
	if (!validate_cylinder_params(tokens, data.diameter, data.height))
		return (destroy_2d((void **)tokens), 0);
	return (parse_cylinder_continue(tokens, world, data));
}

static int	validate_plane_params(char **tokens, t_tuple normal)
{
	if (!validate_parameter_count(tokens, "Plane", 4))
		return (0);
	if (fabs(normal.x) > 1.0 || fabs(normal.y) > 1.0 || fabs(normal.z) > 1.0)
		return (0);
	return (1);
}

static t_plane	*create_plane_object(t_tuple point, t_tuple normal)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane = new_plane(point, normal);
	return (plane);
}

static int	add_plane_to_world(t_world *world, t_plane *plane, t_rgb color,
		char **tokens)
{
	t_object	obj;

	obj = new_object(PLANE, plane);
	obj.material.color = color;
	add_object_to_world(world, obj);
	destroy_2d((void **)tokens);
	return (1);
}

int	parse_plane(char *line, t_world *world)
{
	char		**tokens;
	t_tuple		point;
	t_tuple		normal;
	t_rgb		color;
	t_plane		*plane;

	tokens = ft_split(line, ' ');
	point = parse_tuple(tokens[1], 1);
	normal = parse_tuple(tokens[2], 0);
	if (!validate_plane_params(tokens, normal))
		return (destroy_2d((void **)tokens), 0);
	normal = normalize_vector(normal);
	if (!validate_and_parse_rgb(tokens[3], &color))
		return (destroy_2d((void **)tokens), 0);
	plane = create_plane_object(point, normal);
	if (!plane)
		return (destroy_2d((void **)tokens), 0);
	return (add_plane_to_world(world, plane, color, tokens));
}

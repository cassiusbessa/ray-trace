/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 20:18:13 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	parse_ambient(char *line, t_world *world)
{
	char	**tokens;
	float	ratio;
	t_rgb	color;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Ambient light", 3))
		return (destroy_2d((void **)tokens), 0);
	ratio = parse_float(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (destroy_2d((void **)tokens), 0);
	world->ambient.ratio = ratio;
	if (!validate_and_parse_rgb(tokens[2], &color))
		return (destroy_2d((void **)tokens), 0);
	world->ambient.color = color;
	destroy_2d((void **)tokens);
	return (1);
}

int	parse_camera(char *line, t_camera *camera)
{
	char	**tokens;
	float	fov;
	t_tuple	position;
	t_tuple	direction;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Camera", 4))
		return (destroy_2d((void **)tokens), 0);
	position = parse_tuple(tokens[1], 1);
	direction = normalize_vector(parse_tuple(tokens[2], 0));
	fov = parse_float(tokens[3]);
	if (fov <= 0 || fov >= 180)
		return (destroy_2d((void **)tokens), 0);
	*camera = new_camera(WIDTH, HEIGHT, fov * M_PI / 180.0);
	free_matrix(camera->transform);
	camera->transform = view_transform(position, add_tuples(position,
				direction), vector(0, 1, 0));
	destroy_2d((void **)tokens);
	return (1);
}

int	parse_light(char *line, t_world *world)
{
	char			**tokens;
	t_tuple			position;
	float			brightness;
	t_rgb			color;
	t_point_light	light;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Light", 4))
		return (destroy_2d((void **)tokens), 0);
	position = parse_tuple(tokens[1], 1);
	brightness = parse_float(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
		return (destroy_2d((void **)tokens), 0);
	if (!validate_and_parse_rgb(tokens[3], &color))
		return (destroy_2d((void **)tokens), 0);
	color.r = color.r * brightness;
	color.g = color.g * brightness;
	color.b = color.b * brightness;
	light = new_point_light(position, color);
	add_light_to_world(world, light);
	destroy_2d((void **)tokens);
	return (1);
}

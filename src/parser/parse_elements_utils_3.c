/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:08:38 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:09:07 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	validate_cylinder_params(char **tokens, float diameter,
		float height)
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
	char **tokens;
	t_cylinder_data data;

	tokens = ft_split(line, ' ');
	data.center = parse_tuple(tokens[1], 1);
	data.orientation = normalize_vector(parse_tuple(tokens[2], 0));
	data.diameter = parse_float(tokens[3]);
	data.height = parse_float(tokens[4]);
	if (!validate_cylinder_params(tokens, data.diameter, data.height))
		return (destroy_2d((void **)tokens), 0);
	return (parse_cylinder_continue(tokens, world, data));
}
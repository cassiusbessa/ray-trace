/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:08:38 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 02:32:13 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	validate_cylinder_params(float diameter, float height)
{
	if (diameter <= 0)
		return (0);
	if (height <= 0)
		return (0);
	return (1);
}

int	parse_cylinder_continue(char **tokens, t_world *world, t_cylinder_data data)
{
	t_cylinder_params	params;
	t_rgb				color;
	t_bool				closed;
	t_object			obj;

	if (!validate_and_parse_rgb(tokens[5], &color))
		return (0);
	closed = ft_atoi(tokens[6]) != 0;
	params.center = data.center;
	params.orientation = data.orientation;
	params.diameter = data.diameter;
	params.height = data.height;
	params.color = color;
	params.closed = closed;
	obj = new_cylinder_object(params);
	add_object_to_world(world, obj);
	return (1);
}

int	parse_cylinder(char *line, t_world *world)
{
	char			**tokens;
	t_cylinder_data	data;
	int				result;

	tokens = ft_split(line, ' ');
	if (!validate_parameter_count(tokens, "Cylinder", 7))
		return (destroy_2d((void **)tokens), 0);
	data.center = parse_tuple(tokens[1], 1);
	data.orientation = normalize_vector(parse_tuple(tokens[2], 0));
	data.diameter = parse_float(tokens[3]);
	data.height = parse_float(tokens[4]);
	if (!validate_cylinder_params(data.diameter, data.height))
		return (destroy_2d((void **)tokens), 0);
	result = parse_cylinder_continue(tokens, world, data);
	destroy_2d((void **)tokens);
	return (result);
}

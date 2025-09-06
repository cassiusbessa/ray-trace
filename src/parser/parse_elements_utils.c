/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:30:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:09:09 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	char	**tokens;
	t_tuple	point;
	t_tuple	normal;
	t_rgb	color;
	t_plane	*plane;

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

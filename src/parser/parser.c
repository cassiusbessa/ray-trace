/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:11:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 03:08:55 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	dispatch_primitives(char *line, t_parsed_scene *scene, int fd)
{
	if (starts_with(line, "sp "))
	{
		if (!parse_sphere(line, scene->world))
			return (handle_parse_error("parsing sphere", line, scene, fd));
	}
	else if (starts_with(line, "cy "))
	{
		if (!parse_cylinder(line, scene->world))
			return (handle_parse_error("parsing cylinder", line, scene, fd));
	}
	else if (starts_with(line, "pl "))
	{
		if (!parse_plane(line, scene->world))
			return (handle_parse_error("parsing plane", line, scene, fd));
	}
	else
		return (0);
	return (1);
}

int	dispatch_parse(char *line, t_parsed_scene *scene, int fd)
{
	if (starts_with(line, "A "))
	{
		if (!parse_ambient(line, scene->world))
			return (handle_parse_error("parsing ambient", line, scene, fd));
	}
	else if (starts_with(line, "C "))
	{
		if (!parse_camera(line, &scene->camera))
			return (handle_parse_error("parsing camera", line, scene, fd));
	}
	else if (starts_with(line, "L "))
	{
		if (!parse_light(line, scene->world))
			return (handle_parse_error("parsing light", line, scene, fd));
	}
	else if (!dispatch_primitives(line, scene, fd))
	{
		printf("Error: Unknown element identifier in line: %s\n", line);
		return (0);
	}
	return (1);
}

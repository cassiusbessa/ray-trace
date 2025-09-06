/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:11:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:05:45 by cassius          ###   ########.fr       */
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

static int	dispatch_parse(char *line, t_parsed_scene *scene, int fd)
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
		free(line);
		free_parsed_scene(scene);
		close(fd);
		return (0);
	}
	return (1);
}

static t_parsed_scene	*init_scene(int fd)
{
	t_parsed_scene	*scene;

	scene = malloc(sizeof(t_parsed_scene));
	if (!scene)
		return (close(fd), NULL);
	scene->world = malloc(sizeof(t_world));
	if (!scene->world)
		return (free(scene), close(fd), NULL);
	*(scene->world) = new_world();
	return (scene);
}

static int	process_file_lines(int fd, t_parsed_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line = clean_line(line);
		if (line)
		{
			if (!dispatch_parse(line, scene, fd))
				return (0);
			free(line);
		}
		line = get_next_line(fd);
	}
	return (1);
}

t_parsed_scene	*parse_rt_file(const char *filename)
{
	int				fd;
	t_parsed_scene	*scene;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open file %s\n", filename), NULL);
	scene = init_scene(fd);
	if (!scene)
		return (NULL);
	if (!process_file_lines(fd, scene))
		return (NULL);
	close(fd);
	printf("Successfully parsed file!\n");
	return (scene);
}

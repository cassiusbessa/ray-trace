/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:11:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 22:51:35 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	handle_parse_error(const char *msg, char *line,
		t_parsed_scene *scene, int fd)
{
	printf("Error %s: %s\n", msg, line);
	free(line);
	free_parsed_scene(scene);
	close(fd);
	return (0);
}

int	starts_with(const char *line, const char *prefix)
{
	while (*prefix)
	{
		if (*line != *prefix)
			return (0);
		line++;
		prefix++;
	}
	return (1);
}

static char	*clean_line(char *line)
{
	int	len;

	if (!line || line[0] == '\n' || line[0] == '#' || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

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

t_parsed_scene	*parse_rt_file(const char *filename)
{
	int				fd;
	char			*line;
	t_parsed_scene	*scene;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open file %s\n", filename), NULL);
	scene = malloc(sizeof(t_parsed_scene));
	if (!scene)
		return (close(fd), NULL);
	scene->world = malloc(sizeof(t_world));
	if (!scene->world)
		return (free(scene), close(fd), NULL);
	*(scene->world) = new_world();
	while ((line = get_next_line(fd)) != NULL)
	{
		line = clean_line(line);
		if (!line)
			continue ;
		if (!dispatch_parse(line, scene, fd))
			return (NULL);
		free(line);
	}
	close(fd);
	printf("Successfully parsed file!\n");
	return (scene);
}

void	free_parsed_scene(t_parsed_scene *scene)
{
	if (!scene)
		return ;
	if (scene->world)
	{
		free_world(scene->world);
		free(scene->world);
	}
	free(scene);
}

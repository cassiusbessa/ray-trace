/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 21:11:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 02:42:23 by cassius          ###   ########.fr       */
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
		return (0);
	}
	return (1);
}

static char	*read_entire_file(const char *filename)
{
	int		fd;
	char	*buffer;
	char	*temp;
	char	chunk[1025];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = ft_strdup("");
	if (!buffer)
		return (close(fd), NULL);
	while ((bytes_read = read(fd, chunk, 1024)) > 0)
	{
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(buffer, chunk);
		free(buffer);
		if (!temp)
			return (close(fd), NULL);
		buffer = temp;
	}
	close(fd);
	if (bytes_read < 0)
		return (free(buffer), NULL);
	return (buffer);
}

static char	**split_lines(char *content)
{
	return (ft_split(content, '\n'));
}

static int	process_file_lines_from_array(char **lines, t_parsed_scene *scene)
{
	int		i;
	int		result;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0' && lines[i][0] != '#')
		{
			result = dispatch_parse(lines[i], scene, -1);
			if (!result)
				return (0);
		}
		i++;
	}
	return (1);
}

t_parsed_scene	*parse_rt_file(const char *filename)
{
	t_parsed_scene	*scene;
	char			*file_content;
	char			**lines;

	file_content = read_entire_file(filename);
	if (!file_content)
		return (printf("Error: Cannot read file %s\n", filename), NULL);
	scene = malloc(sizeof(t_parsed_scene));
	if (!scene)
		return (free(file_content), NULL);
	scene->world = malloc(sizeof(t_world));
	if (!scene->world)
		return (free(scene), free(file_content), NULL);
	*(scene->world) = new_world();
	lines = split_lines(file_content);
	free(file_content);
	if (!lines)
		return (free_parsed_scene(scene), NULL);
	if (!process_file_lines_from_array(lines, scene))
	{
		destroy_2d((void **)lines);
		free_parsed_scene(scene);
		return (NULL);
	}
	destroy_2d((void **)lines);
	printf("Successfully parsed file!\n");
	return (scene);
}

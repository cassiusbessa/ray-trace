/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 03:00:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 03:00:00 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static char	*join_and_free(char *buffer, char *chunk)
{
	char	*temp;

	temp = ft_strjoin(buffer, chunk);
	free(buffer);
	return (temp);
}

static char	*read_file_loop(int fd, char *buffer)
{
	char	*temp;
	char	chunk[1025];
	int		bytes_read;

	bytes_read = read(fd, chunk, 1024);
	while (bytes_read > 0)
	{
		chunk[bytes_read] = '\0';
		temp = join_and_free(buffer, chunk);
		if (!temp)
			return (close(fd), NULL);
		buffer = temp;
		bytes_read = read(fd, chunk, 1024);
	}
	if (bytes_read < 0)
		return (free(buffer), NULL);
	return (buffer);
}

static char	*read_entire_file(const char *filename)
{
	int		fd;
	char	*buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = ft_strdup("");
	if (!buffer)
		return (close(fd), NULL);
	buffer = read_file_loop(fd, buffer);
	close(fd);
	return (buffer);
}

t_parsed_scene	*parse_rt_file(const char *filename)
{
	t_parsed_scene	*scene;
	char			*file_content;

	file_content = read_entire_file(filename);
	if (!file_content)
		return (printf("Error: Cannot read file %s\n", filename), NULL);
	scene = init_parsed_scene();
	if (!scene)
		return (free(file_content), NULL);
	if (!process_file_content(file_content, scene))
	{
		free(file_content);
		free_parsed_scene(scene);
		return (NULL);
	}
	free(file_content);
	printf("Successfully parsed file!\n");
	return (scene);
}

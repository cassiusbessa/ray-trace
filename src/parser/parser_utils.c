/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:15:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:36:48 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

char	*clean_line(char *line)
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

int	handle_parse_error(const char *msg, char *line,
		t_parsed_scene *scene, int fd)
{
	printf("Error %s: %s\n", msg, line);
	free(line);
	free_parsed_scene(scene);
	close(fd);
	return (0);
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

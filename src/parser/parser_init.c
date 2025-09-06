/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 03:15:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 03:15:00 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_parsed_scene	*init_parsed_scene(void)
{
	t_parsed_scene	*scene;

	scene = malloc(sizeof(t_parsed_scene));
	if (!scene)
		return (NULL);
	scene->world = malloc(sizeof(t_world));
	if (!scene->world)
		return (free(scene), NULL);
	*(scene->world) = new_world();
	return (scene);
}

int	process_file_content(char *file_content, t_parsed_scene *scene)
{
	char	**lines;
	int		result;

	lines = ft_split(file_content, '\n');
	if (!lines)
		return (0);
	result = process_file_lines_from_array(lines, scene);
	destroy_2d((void **)lines);
	return (result);
}

int	process_file_lines_from_array(char **lines, t_parsed_scene *scene)
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

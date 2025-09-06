/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 01:01:24 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 01:03:20 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

int	main(int argc, char **argv)
{
	t_parsed_scene	*scene;
	t_canvas		*canvas;

	if (argc != 2)
	{
		printf("Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}
	scene = parse_rt_file(argv[1]);
	if (!scene)
	{
		printf("Failed to parse file\n");
		return (1);
	}
	canvas = render(scene->camera, scene->world);
	if (!canvas)
	{
		printf("Failed to render scene\n");
		free_parsed_scene(scene);
		return (1);
	}
	open_mlx_screen(canvas);
	free_parsed_scene(scene);
	return (0);
}

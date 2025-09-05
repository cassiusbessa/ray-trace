/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:21:20 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 16:47:47 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_canvas	*new_canvas(int width, int height)
{
	t_canvas	*canvas;

	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		return (NULL);
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = malloc(sizeof(t_rgb *) * height);
	if (!canvas->pixels)
		return (free(canvas), NULL);
	if (!alloc_pixels(canvas, width, height))
		return (NULL);
	fill_black_canvas(canvas);
	return (canvas);
}

void	free_canvas(t_canvas *canvas)
{
	int	i;

	i = 0;
	while (i < canvas->height)
	{
		free(canvas->pixels[i]);
		i++;
	}
	free(canvas->pixels);
	free(canvas);
}

t_rgb	*pixel_at(t_canvas *canvas, int x, int y)
{
	return (&canvas->pixels[y][x]);
}

void	write_pixel(t_canvas *canvas, int x, int y, t_rgb color)
{
	canvas->pixels[y][x] = color;
}

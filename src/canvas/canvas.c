/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 15:16:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void free_canvas(t_canvas *canvas)
{
    if (!canvas)
        return;
    free(canvas->pixels);
    free(canvas);
}

void	fill_black_canvas(t_canvas *canvas)
{
	int	i;
	int	j;

	i = 0;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			canvas->pixels[i][j].r = 0;
			canvas->pixels[i][j].g = 0;
			canvas->pixels[i][j].b = 0;
			j++;
		}
		i++;
	}
}

t_canvas *new_canvas(int width, int height)
{
    t_canvas *canvas;
	int i;

	canvas = malloc(sizeof(t_canvas));
    if (!canvas)
        return NULL;
    canvas->width = width;
    canvas->height = height;
    canvas->pixels = malloc(sizeof(t_rgb) * width * height);
    if (!canvas->pixels)
    {
        free(canvas);
        return NULL;
    }
    i = 0;
	while (i < width * height)
	{
		canvas->pixels[i].r = 0.0f;
		canvas->pixels[i].g = 0.0f;
		canvas->pixels[i].b = 0.0f;
		i++;
	}
    return (canvas);
}

t_rgb *pixel_at(t_canvas *canvas, int x, int y)
{
    t_rgb *pixel;

	if (!canvas || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
        return NULL;
    pixel = &canvas->pixels[y * canvas->width + x];
	return (pixel);
}

void write_pixel(t_canvas *canvas, int x, int y, t_rgb color)
{
    t_rgb *pixel;

	pixel = pixel_at(canvas, x, y);
    if (pixel)
        *pixel = color;
}


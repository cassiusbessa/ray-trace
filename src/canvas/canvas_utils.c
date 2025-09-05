/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:45:55 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 16:47:44 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

void	free_failed_canvas(t_canvas *canvas, int last)
{
	while (--last >= 0)
		free(canvas->pixels[last]);
	free(canvas->pixels);
	free(canvas);
}

int	alloc_pixels(t_canvas *canvas, int width, int height)
{
	int	i;

	i = -1;
	while (++i < height)
	{
		canvas->pixels[i] = malloc(sizeof(t_rgb) * width);
		if (!canvas->pixels[i])
		{
			free_failed_canvas(canvas, i);
			return (0);
		}
	}
	return (1);
}

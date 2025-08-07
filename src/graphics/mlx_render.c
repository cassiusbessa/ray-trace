/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 09:24:53 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

#include "miniRT.h"

void	draw_canvas_to_image(t_canvas *canvas, t_img *img)
{
	int	x;
	int	y;
	int	pixel;
	t_color	color;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			color = canvas_get_pixel(canvas, x, y);
			pixel = ((int)(color.r * 255) << 16)
				  | ((int)(color.g * 255) << 8)
				  | ((int)(color.b * 255));

			// Cada pixel ocupa 4 bytes (ARGB)
			int	index = (y * img->size_line) + (x * (img->bpp / 8));
			*(int *)(img->data + index) = pixel;
			x++;
		}
		y++;
	}
}

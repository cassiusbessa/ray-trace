/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_to_mlx_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:55:17 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/29 20:19:46 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	rgb_to_int(t_rgb *color)
{
	int	r;
	int	g;
	int	b;
    t_rgb c;

    c = clamp_color(*color);

	r = (int)(c.r * 255);
	g = (int)(c.g * 255);
	b = (int)(c.b * 255);
	return (r << 16 | g << 8 | b);
}

void	canvas_to_mlx_image(t_canvas *canvas, t_mlx *data)
{
	int	x;
	int	y;
	int	color;

	data->img.mlx_img = mlx_new_image(data->mlx_ptr, canvas->width,
			canvas->height);
	if (!data->img.mlx_img)
		return ;
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
		return ;
	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
            color = rgb_to_int(pixel_at(canvas, x, y));
            *(unsigned int *)(data->img.addr + (y
                        * data->img.line_len + x * (data->img.bpp
                            / 8))) = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,
		0);
}

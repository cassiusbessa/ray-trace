/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_to_mlx_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:55:17 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/10 22:06:43 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_img    canvas_to_mlx_image(t_canvas canvas, t_mlx *data)
{
    t_img	img;

    img.mlx_img = mlx_new_image(data->mlx_ptr, canvas.width, canvas.height);
    img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp,
            &img.line_len, &img.endian);
    return (img);
}

int rgb_to_int(t_rgb *color)
{
    int r;
    int g;
    int b;

    r = (int)color->r;
    g = (int)color->g;
    b = (int)color->b;
    return (r << 16 | g << 8 | b);
}

void	img_pix_put(t_img *img, int x, int y, int z)
{
	char	*pixel;
	int		i;
	int		color;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = select_color(z);
	while (i >= 0)
	{
		if (img->endian != 0 && pixel > img->addr)
			*pixel++ = (color >> i) & 0xFF;
		else if (pixel > img->addr)
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
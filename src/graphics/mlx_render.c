/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 11:43:35 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_rgb canvas_get_pixel(t_canvas *canvas, int x, int y)
{
    t_rgb color;

    if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
        color = (t_rgb){0.0f, 0.0f, 0.0f}; // cor padrão fora da tela
    else
        color = canvas->pixels[y * canvas->width + x];

    return color;
}

void draw_canvas_to_image(t_canvas *canvas, t_img *img)
{
    int x = 0;
    int y = 0;
    int pixel;
    t_rgb color;

    while (y < canvas->height)
    {
        x = 0;
        while (x < canvas->width)
        {
            color = canvas_get_pixel(canvas, x, y);

            pixel = ((int)(color.r * 255) << 16)
                  | ((int)(color.g * 255) << 8)
                  | ((int)(color.b * 255));

            int index = (y * img->size_line) + (x * (img->bpp / 8));
            *(int *)(img->data + index) = pixel;

            x++;
        }
        y++;
    }
}


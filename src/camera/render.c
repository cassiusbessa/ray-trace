/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:45:06 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


// Função para "clamp" entre 0 e 1
static float clamp_float(float v)
{
    if (v < 0.0f)
        return 0.0f;
    if (v > 1.0f)
        return 1.0f;
    return v;
}

t_rgb color_to_rgb(t_color c)
{
    t_rgb rgb;

    rgb.r = clamp_float(c.r);
    rgb.g = clamp_float(c.g);
    rgb.b = clamp_float(c.b);

    return rgb;
}


void render(t_world w, t_canvas *canvas)
{
    int y;
    int x;
    t_ray r;
    t_color color;
    t_camera c;

    c = w.camera;
    y = 0;
    while (y < c.vsize)
    {
        x = 0;
        while (x < c.hsize)
        {
            r = ray_for_pixel(c, x, y);
            color = color_at(&w, r);
            write_pixel(canvas, x, y, color_to_rgb(color));
            x++;
        }
        y++;
    }
}

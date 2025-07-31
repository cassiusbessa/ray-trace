/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 16:32:34 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

extern t_color color_at(t_world world, t_ray r);

void render(t_camera c, t_world w, t_canvas *canvas)
{
    int y;
    int x;
    t_ray r;
    t_color color;
    
    y = 0;
    while(y < c.vsize)
    {
        x = 0;
        while(x < c.hsize)
        {
            r = ray_for_pixel(c, x, y);
            color = color_at(w, r);
            write_pixel(canvas, x, y, color);
            x++;
        }
        y++;
    }
}

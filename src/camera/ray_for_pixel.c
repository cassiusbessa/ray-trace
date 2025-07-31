/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_for_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 16:03:33 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_ray ray_for_pixel(t_camera c, int px, int py)
{
    float aspect = (float)c.hsize / (float)c.vsize;
    float half_view = tanf(c.fov / 2);
    float half_width = aspect >= 1 ? half_view : half_view * aspect;
    float half_height = aspect >= 1 ? half_view / aspect : half_view;

    float pixel_size = (half_width * 2) / c.hsize;

    float xoffset = (px + 0.5f) * pixel_size;
    float yoffset = (py + 0.5f) * pixel_size;

    float world_x = half_width - xoffset;
    float world_y = half_height - yoffset;

    t_tuple pixel = multiply_matrix_tuple(inverse(c.transform), point(world_x, world_y, -1));
    t_tuple origin = multiply_matrix_tuple(inverse(c.transform), point(0, 0, 0));
    t_tuple direction = normalize(sub(pixel, origin));

    return ray(origin, direction);
}

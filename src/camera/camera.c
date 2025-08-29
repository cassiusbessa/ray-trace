/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:45:48 by cassius           #+#    #+#             */
/*   Updated: 2025/08/28 22:27:00 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void set_camera_pixel_size(t_camera *cam)
{
    float aspect_ratio;
    float half_view;

    aspect_ratio = (float)cam->hsize / (float)cam->vsize;
    half_view = tan(cam->field_of_view / 2.0f);

    if (aspect_ratio >= 1.0f)
    {
        cam->half_width = half_view;
        cam->half_height = half_view / aspect_ratio;
    }
    else
    {
        cam->half_width = half_view * aspect_ratio;
        cam->half_height = half_view;
    }

    cam->pixel_size = (cam->half_width * 2.0f) / (float)cam->hsize;
}

t_camera new_camera(int hsize, int vsize, float field_of_view)
{
    t_camera cam;

    cam.hsize = hsize;
    cam.vsize = vsize;
    cam.field_of_view = field_of_view;
    cam.transform = identity_matrix(4);
    set_camera_pixel_size(&cam);
    return cam;
}

void    free_camera(t_camera *cam)
{
    if (!cam)
        return;
    free_matrix(cam->transform);
}

t_ray ray_for_pixel(t_camera cam, int px, int py)
{
    int success;
    t_matrix inv = invert_matrix(cam.transform, &success);
    if (!success)
        printf("Warning: Matrix inversion failed in ray_for_pixel\n");

    float xoffset = (px + 0.5f) * cam.pixel_size;
    float yoffset = (py + 0.5f) * cam.pixel_size;

    float world_x = cam.half_width - xoffset;
    float world_y = cam.half_height - yoffset;

    t_tuple pixel = matrix_multiply_by_tuple(inv, point(world_x, world_y, -1));
    t_tuple origin = matrix_multiply_by_tuple(inv, point(0, 0, 0));
    t_tuple direction = normalize_vector(sub_tuples(pixel, origin));

    free_matrix(inv);
    return create_ray(origin, direction);
}




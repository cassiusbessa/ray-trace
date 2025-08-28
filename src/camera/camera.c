/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:45:48 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 21:21:51 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void set_camera_pixel_size(t_camera *cam)
{
    float aspect_ratio;
    float half_view;
    float half_width;

    aspect_ratio = (float)cam->hsize / (float)cam->vsize;
    half_view = tan(cam->field_of_view / 2.0f);

    if (aspect_ratio >= 1.0f)
        half_width = half_view;
    else
        half_width = half_view * aspect_ratio;

    cam->pixel_size = (half_width * 2.0f) / (float)cam->hsize;
}


t_camera    new_camera(int hsize, int vsize, float field_of_view)
{
    t_camera cam;

    cam.hsize = hsize;
    cam.vsize = vsize;
    cam.field_of_view = field_of_view;
    cam.transform = identity_matrix(4);
    set_camera_pixel_size(&cam);
    return (cam);
}



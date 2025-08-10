/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:11:39 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Cria o raio que parte da câmera e passa pelo pixel (px, py)
t_ray camera_ray(t_camera *cam, int px, int py)
{
	double aspect = (double)cam->width / (double)cam->height;
	double fov_adjust = tan((cam->fov * 0.5) * (M_PI / 180.0));
	double x = (2 * ((px + 0.5) / cam->width) - 1) * aspect * fov_adjust;
	double y = (1 - 2 * ((py + 0.5) / cam->height)) * fov_adjust;

	t_vec3 dir = vec3_add(vec3_add(vec3_scale(cam->right, x), vec3_scale(cam->up, y)), cam->forward);
	dir = vec3_normalize(dir);

	return (ray_new(cam->origin, dir));
}


void init_camera(t_camera *cam, t_vec3 origin, t_vec3 look_at, double fov, int width, int height)
{
    cam->origin = origin;
    cam->forward = vec3_normalize(vec3_sub(look_at, origin));  // direção da câmera
    
    t_vec3 up_world = vec3(0, 1, 0);

    // Se forward quase paralelo a up_world, troca o vetor up_world para evitar problema
    if (fabs(vec3_dot(cam->forward, up_world)) > 0.999)
        up_world = vec3(0, 0, 1);  // alternativa

    cam->right = vec3_normalize(vec3_cross(cam->forward, up_world));
    cam->up = vec3_cross(cam->right, cam->forward);
    
    cam->fov = fov;
    cam->width = width;
    cam->height = height;
}



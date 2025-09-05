/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:45:48 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 18:33:55 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_camera	new_camera(int hsize, int vsize, float field_of_view)
{
	t_camera	cam;

	cam.hsize = hsize;
	cam.vsize = vsize;
	cam.field_of_view = field_of_view;
	cam.transform = identity_matrix(4);
	set_camera_pixel_size(&cam);
	return (cam);
}

t_ray	ray_for_pixel(t_camera cam, int px, int py)
{
	t_matrix inv;
	t_tuple pixel;
	t_tuple origin;
	t_tuple direction;

	inv = get_camera_inverse(cam);
	pixel = get_pixel_position(cam, px, py, inv);
	origin = matrix_multiply_by_tuple(inv, point(0, 0, 0));
	direction = normalize_vector(sub_tuples(pixel, origin));
	free_matrix(inv);
	return (create_ray(origin, direction));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:38:27 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 16:44:27 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_camera_pixel_size(t_camera *cam)
{
	float	aspect_ratio;
	float	half_view;

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

t_matrix	get_camera_inverse(t_camera cam)
{
	int			success;
	t_matrix	inv;

	inv = invert_matrix(cam.transform, &success);
	if (!success)
		printf("Warning: Matrix inversion failed in get_camera_inverse\n");
	return (inv);
}

t_tuple	get_pixel_position(t_camera cam, int px, int py, t_matrix inv)
{
	float		xoffset;
	float		yoffset;
	float		world_x;
	float		world_y;

	xoffset = (px + 0.5f) * cam.pixel_size;
	yoffset = (py + 0.5f) * cam.pixel_size;
	world_x = cam.half_width - xoffset;
	world_y = cam.half_height - yoffset;
	return (matrix_multiply_by_tuple(inv, point(world_x, world_y, -1)));
}

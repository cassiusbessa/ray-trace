/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:02:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_canvas	*render(t_camera cam, t_world *w)
{
	t_canvas	*image;
	t_ray		ray;
	t_rgb		color;
	int			x;
	int			y;

	image = new_canvas(cam.hsize, cam.vsize);
	x = 0;
	y = 0;
	while (y < cam.vsize)
	{
		x = 0;
		while (x < cam.hsize)
		{
			ray = ray_for_pixel(cam, x, y);
			color = color_at(w, ray);
			write_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
	return (image);
}

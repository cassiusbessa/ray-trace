/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_mlx_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:57:03 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/15 20:09:23 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	handle_no_event(void *data)
{
    (void)data;
	return (0);
}

static int	close_window(t_mlx *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
	exit(0);
	return (0);
}

static int	handle_key_press(int key, t_mlx *data)
{
	if (key == XK_Escape)
		close_window(data);
	return (0);
}

void	open_mlx_screen(t_canvas *canvas)
{
    t_mlx   *data;

    data = malloc(sizeof(t_mlx));
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, canvas->width, canvas->height, "miniRT");
    canvas_to_mlx_image(canvas, data);
    mlx_loop_hook(data->mlx_ptr, &handle_no_event, data);
    mlx_hook(data->win_ptr, KeyPress, KeyPressMask,
		&handle_key_press, data);
    mlx_loop(data->mlx_ptr);

}
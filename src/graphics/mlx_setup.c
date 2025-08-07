/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 11:43:51 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_mlx init_window(int width, int height, char *title)
{
    t_mlx mlx;

    mlx.mlx_ptr = mlx_init();
    if (!mlx.mlx_ptr)
        exit(EXIT_FAILURE);

    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, width, height, title);
    if (!mlx.win_ptr)
        exit(EXIT_FAILURE);

    mlx.image.img_ptr = mlx_new_image(mlx.mlx_ptr, width, height);
    mlx.image.data = mlx_get_data_addr(mlx.image.img_ptr,
                                       &mlx.image.bpp,
                                       &mlx.image.size_line,
                                       &mlx.image.endian);
    mlx.image.width = width;
    mlx.image.height = height;

    return mlx;
}

void	run_mlx(t_mlx *mlx, t_canvas *canvas)
{
	draw_canvas_to_image(canvas, &mlx->image);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image.img_ptr, 0, 0);

	mlx_hook(mlx->win_ptr, 2, 1L << 0, handle_keypress, mlx); // Tecla
	mlx_hook(mlx->win_ptr, 17, 0, handle_close, mlx);         // Botão "X"

	mlx_loop(mlx->mlx_ptr);
}


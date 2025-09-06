/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:40:04 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:42:01 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "colors.h"

typedef struct s_canvas
{
	int		width;
	int		height;
	t_rgb	**pixels;
}			t_canvas;

// Canvas operations
t_canvas	*new_canvas(int width, int height);
void		free_canvas(t_canvas *canvas);
t_rgb		*pixel_at(t_canvas *canvas, int x, int y);
void		write_pixel(t_canvas *canvas, int x, int y, t_rgb color);
int			alloc_pixels(t_canvas *canvas, int width, int height);
void		free_failed_canvas(t_canvas *canvas, int last);
void		fill_black_canvas(t_canvas *canvas);

#endif

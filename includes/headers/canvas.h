#ifndef CANVAS_H
# define CANVAS_H

# include "colors.h"

typedef struct s_canvas
{
	int		width;
	int		height;
	t_rgb	**pixels;
}	t_canvas;

// Canvas operations
t_canvas	*new_canvas(int width, int height);
void		free_canvas(t_canvas *canvas);
t_rgb		*pixel_at(t_canvas *canvas, int x, int y);
void		write_pixel(t_canvas *canvas, int x, int y, t_rgb color);

#endif

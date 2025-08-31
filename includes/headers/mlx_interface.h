#ifndef MLX_INTERFACE_H
# define MLX_INTERFACE_H

# include "canvas.h"

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx;

// MLX operations
void	open_mlx_screen(t_canvas *canvas);
void	canvas_to_mlx_image(t_canvas *canvas, t_mlx *data);

#endif

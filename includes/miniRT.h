/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/30 09:12:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../utils/libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# define EPSILON 0.0001

typedef int	t_bool;

# define TRUE 1
# define FALSE 0

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}			t_tuple;

typedef struct s_matrix
{
	int		size;
	float	**data;
}			t_matrix;

// ----------------------
// Tuple functions
// ----------------------

t_tuple		new_tuple(float x, float y, float z, t_bool is_point);
t_tuple		add_tuple(t_tuple t1, t_tuple t2);
t_tuple		subtract_tuple(t_tuple t1, t_tuple t2);
t_tuple		multiply_tuple(t_tuple t, float scalar);
t_tuple 	negate_tuple(t_tuple t);
t_tuple		divide_tuple(t_tuple t, float scalar);
t_tuple		normalize_vector(t_tuple t);
t_tuple		vector_cross(t_tuple t1, t_tuple t2);
t_tuple		vector_tuple(float x, float y, float z);
t_tuple		point_tuple(float x, float y, float z);

float		magnitude_vector(t_tuple t);
float		vector_dot(t_tuple t1, t_tuple t2);
int			tuple_equal(t_tuple t1, t_tuple t2);

double		get_tuple_value(t_tuple t, int index);
void		set_tuple_value(t_tuple *t, int index, double value);

// ----------------------
// Matrix functions
// ----------------------

t_matrix	identity_matrix(int size);
t_bool		equal_matrix(t_matrix m1, t_matrix m2);
t_matrix	matrix_multiply_by_matrix(t_matrix a, t_matrix b);
t_tuple		matrix_multiply_by_tuple(t_matrix m, t_tuple t);
t_matrix	transpose_matrix(t_matrix matrix);
t_matrix	submatrix(t_matrix matrix, int row, int col);
t_matrix	matrix_inverse(t_matrix matrix);
t_matrix	new_matrix(int rows, int cols);
int			matrix_determinant(t_matrix matrix);
int			matrix_minor(t_matrix matrix, int row, int col);
int			matrix_cofactor(t_matrix matrix, int row, int col);
int			matrix_is_invertible(t_matrix matrix);

int			matrix_determinant_2x2(t_matrix matrix);
void		print_matrix(t_matrix matrix);
void		free_matrix(t_matrix matrix);

// ----------------------
// Matrix transformations
// ----------------------

t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	rotation_x(float r);
t_matrix	rotation_y(float r);
t_matrix	rotation_z(float r);
t_matrix	shearing(float xy, float xz, float yx, float yz, float zx, float zy);


typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}			t_rgb;

t_rgb		new_rgb(float r, float g, float b);
t_rgb		add_rgb(t_rgb c1, t_rgb c2);
t_rgb		sub_rgb(t_rgb c1, t_rgb c2);
t_rgb		multiply_rgb_by_scalar(t_rgb c, float scalar);
t_rgb		multiply_rgb_by_rgb(t_rgb c1, t_rgb c2);
int			equal_rgb(t_rgb c1, t_rgb c2);

typedef struct s_canvas
{
	int		width;
	int		height;
	t_rgb	**pixels;
}			t_canvas;

t_canvas	*new_canvas(int width, int height);
void		free_canvas(t_canvas *canvas);
t_rgb		*pixel_at(t_canvas *canvas, int x, int y);
void		write_pixel(t_canvas *canvas, int x, int y, t_rgb color);

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}			t_mlx;

void		open_mlx_screen(t_canvas *canvas);
void		canvas_to_mlx_image(t_canvas *canvas, t_mlx *data);


#endif
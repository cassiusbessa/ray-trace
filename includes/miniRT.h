/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/15 15:36:09 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx-linux/mlx.h"
# include "../utils/libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define EPSILON 0.0001
# define TRUE 1
# define FALSE 0
typedef int	t_bool;

/* ************************************************************************** */
/*                                Tuples & Vectors                             */
/* ************************************************************************** */

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

t_tuple		new_tuple(float x, float y, float z, t_bool is_point);
t_tuple		point(float x, float y, float z);
t_tuple		vector(float x, float y, float z);
t_tuple		add_tuples(t_tuple t1, t_tuple t2);
t_tuple		sub_tuples(t_tuple t1, t_tuple t2);
t_tuple		multiply_tuple_by_scalar(t_tuple t, float scalar);
float		magnitude_of_vector(t_tuple t);
t_tuple		normalize_vector(t_tuple t);
float		vector_dot_product(t_tuple t1, t_tuple t2);
t_tuple		vector_cross_product(t_tuple t1, t_tuple t2);
t_bool		equal_tuples(t_tuple t1, t_tuple t2);

/* ************************************************************************** */
/*                                  Colors                                     */
/* ************************************************************************** */

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

t_rgb		new_rgb(float r, float g, float b);
t_rgb		add_rgb(t_rgb c1, t_rgb c2);
t_rgb		sub_rgb(t_rgb c1, t_rgb c2);
t_rgb		multiply_rgb_by_scalar(t_rgb c, float scalar);
t_rgb		multiply_rgb_by_rgb(t_rgb c1, t_rgb c2);
int			equal_rgb(t_rgb c1, t_rgb c2);

/* ************************************************************************** */
/*                                 Canvas & Image                              */
/* ************************************************************************** */

typedef struct s_canvas
{
	int		width;
	int		height;
	t_rgb	**pixels;
}	t_canvas;

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
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_mlx;

void		open_mlx_screen(t_canvas *canvas);
void		canvas_to_mlx_image(t_canvas *canvas, t_mlx *data);

/* ************************************************************************** */
/*                                Matrices                                     */
/* ************************************************************************** */

typedef struct s_matrix
{
	int		size;
	float	**data;
}	t_matrix;

t_matrix	new_matrix(int rows, int cols);
t_matrix	identity_matrix(int size);
void		print_matrix(t_matrix matrix);
void		free_matrix(t_matrix matrix);
t_bool		equal_matrix(t_matrix m1, t_matrix m2);
t_matrix	matrix_multiply_by_matrix(t_matrix a, t_matrix b);
t_tuple		matrix_multiply_by_tuple(t_matrix m, t_tuple t);
t_matrix	transpose_matrix(t_matrix matrix);
int			matrix_determinant_2x2(t_matrix matrix);
t_matrix	submatrix(t_matrix matrix, int row, int col);
double		minor_matrix(t_matrix matrix, int row, int col);
double		cofactor_matrix(t_matrix matrix, int row, int col);
float		determinant_matrix(t_matrix a);
int			is_invertible(t_matrix matrix);
t_matrix	invert_matrix(t_matrix matrix);

/* ************************************************************************** */
/*                             Transformations                                 */
/* ************************************************************************** */

t_matrix translation_matrix(float x, float y, float z);
t_matrix scaling_matrix(float x, float y, float z);
t_matrix rotation_x_matrix(float radians);
t_matrix rotation_y_matrix(float radians);
t_matrix rotation_z_matrix(float radians);
t_matrix shearing_matrix(float xy, float xz, float yx, float yz, float zx, float zy);

/* ************************************************************************** */
/*                                Rays                                        */
/* ************************************************************************** */

typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
}	t_ray;

t_ray		create_ray(t_tuple origin, t_tuple direction);
t_tuple		ray_position(t_ray r, float t);
t_bool		equal_rays(t_ray r1, t_ray r2);
t_ray transform_ray(t_ray r, t_matrix m);


/* ************************************************************************** */
/*                               Objects                                      */
/* ************************************************************************** */

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_object
{
	t_object_type type;
	void *data; // ponteiro para t_sphere, t_plane, etc.
}	t_object;

/* ************************************************************************** */
/*                            Intersections                                   */
/* ************************************************************************** */

typedef struct s_intersection
{
	float count;
	float enter;
	float exit;
	void *object;
}	t_intersection;

typedef struct s_intersections
{
	t_intersection *list;
	int count;
}	t_intersections;

t_intersection	new_intersection(int count, float enter, float exit, void *object);
t_bool			equal_intersections(t_intersection i1, t_intersection i2);
t_intersections	intersections(t_intersection i1, t_intersection i2);
t_intersection	hit(t_intersections xs);
t_intersections intersections_create(int count, t_intersection *list);

/* ************************************************************************** */
/*                               Quadratic Solver                             */
/* ************************************************************************** */

typedef struct s_quad
{
	int		count;
	float	x1;
	float	x2;
}	t_quad;

t_quad			ft_quadratic(float a, float b, float c);
t_intersection	ft_quad_to_intersection(t_quad q, void *object);


/* ************************************************************************** */
/*                               Spheres                                      */
/* ************************************************************************** */

typedef struct s_sphere
{
	t_tuple center;
	float radius;
	t_matrix transform;
}	t_sphere;

t_sphere		new_sphere(t_tuple center, float radius);
t_intersection	intersect_ray_sphere(t_ray ray, t_sphere *sphere);
int				intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out);
void set_object_transform(t_object *obj, t_matrix m);

t_bool float_equal(float a, float b);

int intersect_object(t_ray *ray, t_object *obj, t_intersection *out);
t_intersections intersect_sphere_all(t_ray *ray, t_object *obj);

t_quad solve_quadratic_for_sphere(t_ray ray, t_sphere *sphere);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/06 11:00:20 by emorshhe         ###   ########.fr       */
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
// ----------------------
// Macros e Tipos Básicos
// ----------------------

#define EPSILON 0.0001
#define PI 3.14159265358979323846f

typedef int	t_bool;
#define TRUE 1
#define FALSE 0

// ----------------------
// Structs Matemáticas
// ----------------------

typedef struct s_tuple {
	float x;
	float y;
	float z;
	int   w; // 1: ponto, 0: vetor
} t_tuple;

typedef struct s_matrix {
	int     size;
	float **data;
} t_matrix;

// ----------------------
// Cores e Iluminação
// ----------------------

typedef struct s_color {
	float r;
	float g;
	float b;
} t_color;

typedef struct s_light {
	t_tuple position;
	t_color intensity;
} t_light;

typedef struct s_ambient {
	double   ratio;   // intensidade entre 0.0 e 1.0
	t_color  color;   // cor da luz ambiente (RGB normalizado)
} t_ambient;

typedef struct s_material {
	t_color color;
	float   ambient;
	float   diffuse;
	float   specular;
	float   shininess;
} t_material;

typedef struct s_material_light_params {
	t_material material;
	t_light    light;
} t_material_light_params;

typedef struct s_lighting_context {
	t_tuple position;
	t_tuple eyev;
	t_tuple normalv;
	int     in_shadow;
} t_lighting_context;

// ----------------------
// Canvas e Câmera
// ----------------------

typedef struct s_rgb {
	float r;
	float g;
	float b;
} t_rgb;

typedef struct s_canvas {
	int   width;
	int   height;
	t_rgb *pixels; // array 1D de pixels
} t_canvas;

typedef struct s_camera {
	int      hsize;
	int      vsize;
	float    fov;
	t_matrix transform;
} t_camera;

// ----------------------
// Ray, Objetos e Interseções
// ----------------------

typedef struct s_ray {
	t_tuple origin;
	t_tuple direction;
} t_ray;

typedef struct s_sphere {
	t_matrix   transform;
	t_material material;
} t_sphere;

typedef struct s_intersection {
	float      t;
	t_sphere  *object;
} t_intersection;

// ----------------------
// Objetos e Mundo
// ----------------------

typedef enum e_object_type {
	SPHERE,
	PLANE,
	CYLINDER
} t_object_type;

typedef struct s_object {
	t_object_type   type;
	void           *object; // ponteiro para esfera/plano/cilindro
	struct s_object *next;
} t_object;

typedef struct s_light_list {
	t_light              light;
	struct s_light_list *next;
} t_light_list;

typedef struct s_world {
	t_ambient     ambient_light;
	t_camera      camera;
	t_object     *objects;      // lista ligada de objetos
	t_light_list *lights;       // lista ligada de luzes pontuais
} t_world;



// ----------------------
// Tuple functions
// ----------------------

t_tuple		new_tuple(float x, float y, float z, t_bool is_point);
t_tuple		add_tuple(t_tuple t1, t_tuple t2);
t_tuple		subtract_tuple(t_tuple t1, t_tuple t2);
t_tuple		multiply_tuple(t_tuple t, float scalar);
t_tuple		negate_tuple(t_tuple t);
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

t_matrix	translation(int size, float *data);
t_matrix	scaling(int size, float *data);
t_matrix	rotation_x(float r);
t_matrix	rotation_y(float r);
t_matrix	rotation_z(float r);
t_matrix	shearing(float xy, float xz, float yx, float yz, float zx, float zy);
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_matrix	translation_matrix(float tx, float ty, float tz);

// ----------------------
// Ray functions
// ----------------------

t_ray		ray(t_tuple origin, t_tuple direction);
t_tuple		position(t_ray r, float t);
t_ray		transform_ray(t_ray r, t_matrix m);

// ----------------------
// Sphere functions
// ----------------------

t_sphere	sphere(void);
void		set_transform(t_sphere *s, t_matrix t);

// ----------------------
// Intersection functions
// ----------------------

t_intersection	*intersect(t_sphere *s, t_ray r, int *count);
t_intersection	*hit(t_intersection *xs, int count);
int compare_intersections(const void *a, const void *b);
static t_intersection *resize_intersections(t_intersection *arr, int *capacity);
static int append_intersections(t_intersection **dst, int *total_count, int *capacity, t_intersection *src, int src_count);
t_intersection *intersect_world(t_world *world, t_ray ray, int *count);



// ----------------------
// Light and Material functions
// ----------------------

t_light		point_light(t_tuple position, t_color intensity);
t_material	default_material(void);
t_color		calculate_diffuse(t_material material, t_color effective_color, float light_dot_normal);
t_color		calculate_specular(t_material material, t_light light, t_tuple reflectv, t_tuple eyev);
t_color		lighting_diffuse_specular(t_material_light_params mlp, t_lighting_context ctx);
t_color		lighting(t_material_light_params mlp, t_lighting_context ctx);

// ----------------------
// Color functions
// ----------------------

t_color		color(float r, float g, float b);
t_color		add_color(t_color c1, t_color c2);
t_color		subtract_color(t_color c1, t_color c2);
t_color		multiply_color_scalar(t_color c, float scalar);
t_color		multiply_color(t_color c1, t_color c2);
int			color_equal(t_color c1, t_color c2);

// ----------------------
// Canvas functions
// ----------------------

void		free_canvas(t_canvas *canvas);
void		fill_black_canvas(t_canvas *canvas);
t_canvas	*new_canvas(int width, int height);
t_rgb		*pixel_at(t_canvas *canvas, int x, int y);
void		write_pixel(t_canvas *canvas, int x, int y, t_rgb color);
int			clamp(float v);
void		canvas_to_ppm(t_canvas *canvas, const char *filename);

// ----------------------
// Camera functions
// ----------------------

t_ray		ray_for_pixel(t_camera c, int px, int py);
void		render(t_camera c, t_world w, t_canvas *canvas);

// ----------------------
// Ray tracing core functions
// ----------------------

t_color		shade_hit(t_world *world, t_intersection *hit, t_ray ray);
t_color		color_at(t_world *world, t_ray ray);
t_tuple		compute_normal(t_sphere *sphere, t_tuple point);
int			is_shadowed(t_world *world, t_tuple point);

// ----------------------
// Parser functions
// ----------------------

int     parse_rt_file(const char *filename, t_world *world);
int     parse_ambient(const char *line, t_world *world);
int     parse_camera(const char *line, t_world *world);
int     parse_light(const char *line, t_world *world);
int     parse_sphere(const char *line, t_world *world);
int     parse_plane(const char *line, t_world *world);
int     parse_cylinder(const char *line, t_world *world);

int     line_is_empty_or_comment(const char *line);
int     starts_with(const char *line, const char *prefix);
char    **split_line(const char *line, char delimiter);
void    print_error(const char *msg);

void    free_parsed_world(t_world *world);























t_rgb		new_rgb(float r, float g, float b);
t_rgb		add_rgb(t_rgb c1, t_rgb c2);
t_rgb		sub_rgb(t_rgb c1, t_rgb c2);
t_rgb		multiply_rgb_by_scalar(t_rgb c, float scalar);
t_rgb		multiply_rgb_by_rgb(t_rgb c1, t_rgb c2);
int			equal_rgb(t_rgb c1, t_rgb c2);




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
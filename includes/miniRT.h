/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/10 10:04:35 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
#include <stdbool.h>

// Configurações da janela e constantes globais
# define WIDTH 800
# define HEIGHT 600
# define TITLE "miniRT"
# define EPS 1e-6
# define INF 1e30
#define MAX_RECURSION_DEPTH 5

// -------------------------
// Tipos básicos
// -------------------------
typedef struct s_vec3 {
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_color {
	float r;
	float g;
	float b;
}	t_color;

// -------------------------
// Material
// -------------------------
typedef struct s_material {
    t_color base_color;
    float specular_coef;
    float shininess;
    float reflectivity;  // pode ficar zero por enquanto
    float transparency; // 0.0 (opaco) a 1.0 (totalmente transparente)
    float ior;          // índice de refração (ex: ar=1.0, vidro=1.5)
} t_material;

// -------------------------
// Rayos
// -------------------------
typedef struct s_ray {
	t_vec3 origin;
	t_vec3 dir;  // deve estar normalizado
}	t_ray;

// -------------------------
// Câmera
// -------------------------
typedef struct s_camera {
	t_vec3 origin;
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;
	double fov; // graus
	int width;
	int height;
}	t_camera;

// -------------------------
// Tipos de objetos
// -------------------------
typedef enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_sphere {
	t_vec3 center;
	double radius;
	t_color color;
}	t_sphere;

typedef struct s_plane {
	t_vec3 point;
	t_vec3 normal; // deve estar normalizado
	t_color color;
}	t_plane;

typedef struct s_cylinder {
	t_vec3 center;  // ponto médio
	t_vec3 axis;    // vetor direção, normalizado
	double radius;
	double height;
	t_color color;
}	t_cylinder;

typedef struct s_object {
	t_obj_type type;
	t_material material;
	void *shape;              // ponteiro para t_sphere / t_plane / t_cylinder
	struct s_object *next;    // lista ligada da cena
}	t_object;

// -------------------------
// Luzes
// -------------------------
typedef struct s_ambient_light {
	float intensity;   // [0,1] intensidade da luz ambiente
	t_color color;     // cor da luz ambiente (float r,g,b 0-1)
}	t_ambient_light;

typedef struct s_point_light {
	t_vec3 position;   // posição da luz pontual
	float brightness;  // intensidade [0,1]
	t_color color;     // cor da luz pontual
	t_color specular_color; // default branco
} t_point_light;


typedef struct s_hit {
    float t;
    t_vec3 point;
    t_vec3 normal;
    t_object *object;
} t_hit;
// -------------------------
// Cena completa
// -------------------------
typedef struct s_scene {
	t_object *objects;
	t_camera camera;
	int num_objects;
	t_ambient_light ambient;
	t_point_light *point_lights;
	int n_point_lights;
	t_color background_color;
}	t_scene;

// -------------------------
// Interseção
// -------------------------
typedef struct s_intersection {
	double t;
	t_vec3 point;
	t_vec3 normal;
	t_object *object;
}	t_intersection;

// -------------------------
// MiniLibX
// -------------------------
typedef struct s_mlx {
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;
	int width;
	int height;
}	t_mlx;

// ----------------------------------
// Protótipos das funções
// ----------------------------------

// Validação e logging (src/utils/log.c)
void	print_error(char *message, char **to_free);
void	log_debug(char *msg);
void	check_range(float value, float min, float max, char *msg, char **to_free);
int		is_in_range(float value, float min, float max);

// Manipulação de cores (src/core/lighting.c e src/utils/color_utils.c)
t_color make_color(float r, float g, float b);
t_color add_colors(t_color c1, t_color c2);
t_color apply_ambient_light(t_ambient_light *ambient, t_color obj_color);
t_color clamp_color(t_color c);

int		color_to_int(t_color c);




t_material default_material(void);


// Parser (src/parser/)
int parse_rt_file(char *filename, t_scene *scene);
float	parse_float(char *str);
t_vec3	parse_vec3(char *str);
t_color	parse_color(char *str);
float	ft_atof(const char *nptr);
void	ft_free_split(char **tokens);
int		count_tokens(char **tokens);

// Vetores (src/utils/vec3_ops.c e src/utils/vec3_more.c)
t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double s);
double	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

// Rayos (src/ray/ray.c)
t_ray	ray_new(t_vec3 orig, t_vec3 dir);
t_vec3	ray_at(t_ray r, double t);

// Interseções (src/objects/ e src/renderer/object_hit.c)
int		intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_plane(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_cylinder(t_ray *ray, t_object *obj, t_intersection *out);
int		intersect_object(t_ray *ray, t_object *obj, t_intersection *out);
int		closest_hit(t_ray *ray, t_object *scene, t_intersection *out);

// Utils hit (src/ray/hit.c)
t_vec3	compute_hit_point(t_ray *ray, double t);
t_vec3	compute_normal(t_object *obj, t_vec3 point);

// Renderização e câmera (src/core/camera.c e src/core/renderer.c)
void	render_scene(t_scene *scene, t_mlx *mlx);
t_ray	camera_ray(t_camera *cam, int px, int py);
void init_camera(t_camera *cam, t_vec3 origin, t_vec3 look_at, double fov, int width, int height);
void	put_pixel(t_mlx *mlx, int x, int y, int color);

// MiniLibX utils e eventos (src/mlx/mlx_utils.c)
int		mlx_init_all(t_mlx *mlx, int width, int height);
int		close_window(void *param);
int		handle_key(int keycode, void *param);

// Luz ambiente
t_color apply_ambient_light(t_ambient_light *ambient, t_color obj_color);

// Luz difusa
t_color apply_diffuse_light(t_point_light *light, t_vec3 point, t_vec3 normal, t_color obj_color, float visibility);

// Luz especular
t_color calculate_specular(t_vec3 point, t_vec3 normal, t_vec3 light_pos, t_vec3 view_pos,
    t_color light_color, float brightness,
    float specular_coef, float shininess);
// Sombras
t_ray create_shadow_ray(t_vec3 point, t_vec3 light_pos);
int in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_pos);

// Iluminação geral

t_color calculate_lighting(t_scene *scene, t_vec3 point, t_vec3 normal, t_vec3 view_pos, t_color base, t_object *obj);


// Utilitários de cor e vetor
t_color get_object_color(t_object *obj);
t_vec3 vec3_reflect(t_vec3 v, t_vec3 n);

// Liberação de memória
void free_objects(t_object *obj);
void free_point_lights(t_scene *scene);

// Parser helpers
int line_is_empty_or_comment(const char *line);
int starts_with(const char *str, const char *prefix);
int parse_ambient(const char *line, t_scene *scene);
int parse_camera(const char *line, t_scene *scene);
int parse_point_light(const char *line, t_scene *scene);
int parse_sphere(const char *line, t_scene *scene);
int parse_plane(const char *line, t_scene *scene);
int parse_cylinder(const char *line, t_scene *scene);

void add_object_to_scene(t_scene *scene, t_object *obj);

// em includes/miniRT.h (ou outro header relevante)
t_object *create_object(t_obj_type type, void *shape, t_color base_color, char **tokens,
    int specular_index, int shininess_index,
    int transparency_index, int ior_index);

t_vec3 vec3_neg(t_vec3 v);
t_color vec3_scale_color(t_color c, float s);
int vec3_refract(t_vec3 incident, t_vec3 normal, float eta, t_vec3 *refracted);

int scene_intersect(t_scene *scene, t_ray ray, t_hit *hit);
#endif

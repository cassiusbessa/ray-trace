#ifndef PARSER_H
# define PARSER_H

# include "../miniRT.h"

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_point_light	*lights;
	int				light_count;
	t_sphere		*spheres;
	int				sphere_count;
}	t_scene;

// Parser functions
t_scene	*parse_rt_file(const char *filename);
void	free_scene(t_scene *scene);
void	print_scene_debug(t_scene *scene);
t_world	*scene_to_world(t_scene *scene);

// Internal parsing functions
int		parse_ambient(char *line, t_ambient *ambient);
int		parse_camera(char *line, t_camera *camera);
int		parse_light(char *line, t_point_light *light);
int		parse_sphere(char *line, t_sphere *sphere);

// Utility functions
t_rgb	parse_rgb(char *rgb_str);
t_tuple	parse_tuple(char *tuple_str, int is_point);
float	parse_float(char *str);
char	**split_by_spaces(char *line, int *count);
void	free_tokens(char **tokens, int count);

#endif

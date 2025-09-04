#ifndef PARSER_H
# define PARSER_H

# include "../miniRT.h"

typedef struct s_parsed_scene
{
	t_world		*world;
	t_camera	camera;
}	t_parsed_scene;

// Parser functions
t_parsed_scene	*parse_rt_file(const char *filename);
void			free_parsed_scene(t_parsed_scene *scene);
void			print_parsed_scene_debug(t_parsed_scene *scene);

// Internal parsing functions
int		parse_ambient(char *line, t_world *world);
int		parse_camera(char *line, t_camera *camera);
int		parse_light(char *line, t_world *world);
int		parse_sphere(char *line, t_world *world);
int		parse_cylinder(char *line, t_world *world);

// Utility functions
t_rgb	parse_rgb(char *rgb_str);
int		validate_and_parse_rgb(char *rgb_str, t_rgb *out_rgb);
t_tuple	parse_tuple(char *tuple_str, int is_point);
float	parse_float(char *str);
int		count_tokens(char **tokens);
int		validate_parameter_count(char **tokens, char *element_type, int expected_count);
char	**split_by_spaces(char *line, int *count);
void	free_tokens(char **tokens, int count);

#endif

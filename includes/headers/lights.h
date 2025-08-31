#ifndef LIGHTS_H
# define LIGHTS_H

# include "tuples.h"
# include "colors.h"
# include "materials.h"

typedef struct s_point_light
{
	t_tuple	position;
	t_rgb	intensity;
}	t_point_light;

typedef struct s_point_light_node
{
	struct s_point_light_node	*prev;
	t_point_light				light;
	struct s_point_light_node	*next;
}	t_point_light_node;

typedef struct s_point_light_list
{
	t_point_light_node	*head;
	t_point_light_node	*tail;
	int					count;
}	t_point_light_list;

// Light operations
t_point_light	new_point_light(t_tuple position, t_rgb intensity);
t_rgb			lighting(t_material m, t_point_light light,
					t_tuple position, t_tuple eyev, t_tuple normalv,
					int in_shadow);

// Lighting components
t_rgb			diffuse_component(t_material m, t_point_light light, t_tuple lightv, t_tuple normalv);
t_rgb			specular_component(t_material m, t_point_light light, t_tuple lightv, t_tuple eyev, t_tuple normalv);
t_rgb			calc_diff_spec(t_material m, t_point_light light, t_tuple lightv, t_tuple eyev, t_tuple normalv);

#endif

#ifndef WORLD_H
# define WORLD_H

# include "lights.h"
# include "objects.h"
# include "intersections.h"

typedef struct s_world
{
	t_point_light_list	*lights;
	t_object_list		*objects;
}	t_world;

// World operations
t_world				new_world(void);
void				add_object_to_world(t_world *world, t_object object);
void				add_light_to_world(t_world *world, t_point_light light);
t_world				default_world(void);
void				free_world(t_world *world);
t_intersection_list	*intersect_world(t_world *world, t_ray *ray);
t_bool				is_shadowed(t_world *world, t_tuple point);

#endif

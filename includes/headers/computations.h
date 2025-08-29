#ifndef COMPUTATIONS_H
# define COMPUTATIONS_H

# include "world.h"
# include "rays.h"

typedef struct s_comps
{
	float		t;
	t_object	*object;
	t_tuple		point;
	t_tuple		over_point;
	t_tuple		eyev;
	t_tuple		normalv;
	t_bool		inside;
}	t_comps;

// Computation operations
t_comps	prepare_computations(t_intersection_node i, t_ray r);
t_rgb	shade_hit(t_world *world, t_comps comps);
t_rgb	color_at(t_world *world, t_ray ray);

#endif

#ifndef RAYS_H
# define RAYS_H

# include "tuples.h"
# include "matrices.h"

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

// Ray operations
t_ray	create_ray(t_tuple origin, t_tuple direction);
t_tuple	ray_position(t_ray r, float t);
t_bool	equal_rays(t_ray r1, t_ray r2);
t_ray	transform_ray(t_ray r, t_matrix m, int *success);

#endif

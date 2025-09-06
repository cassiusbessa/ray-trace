#ifndef SPHERES_H
# define SPHERES_H

# include "intersections.h"
# include "materials.h"
# include "quadratic.h"
# include "transformations.h"

typedef struct s_sphere
{
	t_tuple			center;
	float			radius;
}					t_sphere;

typedef struct s_sphere_calc
{
	float			a;
	float			b;
	float			c;
}					t_sphere_calc;

// Sphere operations
t_sphere			new_sphere(t_tuple center, float radius);
void				free_sphere(t_sphere *sphere);
t_intersection_list	*intersect_ray_sphere(t_ray ray, t_object *obj);
t_quad				solve_quadratic_for_sphere(t_ray ray, t_sphere *sphere);
t_tuple				normal_at_sphere(t_object *obj, t_tuple world_point);

#endif

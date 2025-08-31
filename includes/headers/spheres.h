#ifndef SPHERES_H
# define SPHERES_H

# include "materials.h"
# include "transformations.h"
# include "intersections.h"
# include "quadratic.h"

typedef struct s_sphere
{
	t_tuple		center;
	float		radius;
	t_matrix	transform;
	t_material	material;
}	t_sphere;

// Sphere operations
t_sphere			new_sphere(t_tuple center, float radius);
void				free_sphere(t_sphere *sphere);
t_intersection_list	*intersect_ray_sphere(t_ray ray, t_object *obj);
t_quad				solve_quadratic_for_sphere(t_ray ray, t_sphere *sphere);
t_tuple				normal_at(t_object o, t_tuple p);

#endif

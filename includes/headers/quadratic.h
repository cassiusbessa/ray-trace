#ifndef QUADRATIC_H
# define QUADRATIC_H

# include "intersections.h"

typedef struct s_quad
{
	int		count;
	float	x1;
	float	x2;
}	t_quad;

// Quadratic solver
t_quad			ft_quadratic(float a, float b, float c);
t_intersection	ft_quad_to_intersection(t_quad q, void *object);
t_bool			float_equal(float a, float b);

#endif

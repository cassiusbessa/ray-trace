#ifndef TUPLES_H
# define TUPLES_H

# include "types.h"

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

// Tuple creation
t_tuple	new_tuple(float x, float y, float z, t_bool is_point);
t_tuple	point(float x, float y, float z);
t_tuple	vector(float x, float y, float z);

// Tuple operations
t_tuple	add_tuples(t_tuple t1, t_tuple t2);
t_tuple	sub_tuples(t_tuple t1, t_tuple t2);
t_tuple	multiply_tuple_by_scalar(t_tuple t, float scalar);
t_bool	equal_tuples(t_tuple t1, t_tuple t2);

// Vector operations
float	magnitude_of_vector(t_tuple t);
t_tuple	normalize_vector(t_tuple t);
float	vector_dot_product(t_tuple t1, t_tuple t2);
t_tuple	vector_cross_product(t_tuple t1, t_tuple t2);
t_tuple	negate_vector(t_tuple v);
t_tuple	safe_normalize_vector(t_tuple v);
t_tuple	reflect(t_tuple v, t_tuple n);

#endif

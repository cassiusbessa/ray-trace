#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "matrices.h"

typedef struct s_transform_params
{
	float	translation[3];
	float	rotation[3];
	float	scaling[3];
}	t_transform_params;

// Basic transformations
t_matrix	translation_matrix(float x, float y, float z);
t_matrix	scaling_matrix(float x, float y, float z);
t_matrix	rotation_x_matrix(float radians);
t_matrix	rotation_y_matrix(float radians);
t_matrix	rotation_z_matrix(float radians);
t_matrix	shearing_matrix(float xy, float xz, float yx,
				float yz, float zx, float zy);

// Advanced transformations
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_matrix	chain_transformations(t_transform_params params);

#endif

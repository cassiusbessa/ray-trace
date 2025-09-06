/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:41:32 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:57:08 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "matrices.h"

typedef struct s_shearing
{
	float	xy;
	float	xz;
	float	yx;
	float	yz;
	float	zx;
	float	zy;
}			t_shearing;

typedef struct s_transform_params
{
	float	translation[3];
	float	rotation[3];
	float	scaling[3];
}			t_transform_params;

typedef struct s_basis
{
	t_tuple	forward;
	t_tuple	left;
	t_tuple	true_up;
}			t_basis;

// Basic transformations
t_matrix	translation_matrix(float x, float y, float z);
t_matrix	scaling_matrix(float x, float y, float z);
t_matrix	rotation_x_matrix(float radians);
t_matrix	rotation_y_matrix(float radians);
t_matrix	rotation_z_matrix(float radians);
t_matrix	shearing_matrix(t_shearing s);

// Advanced transformations
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_matrix	chain_transformations(t_transform_params params);
// Orientation matrix helpers
void		set_rotation_row_0(t_matrix *rot, double cos_theta,
				double sin_theta, t_tuple axis);
void		set_rotation_row_1(t_matrix *rot, double cos_theta,
				double sin_theta, t_tuple axis);
void		set_rotation_row_2_3(t_matrix *rot, double cos_theta,
				double sin_theta, t_tuple axis);


#endif

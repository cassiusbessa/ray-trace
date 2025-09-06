/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/06 00:56:33 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	compute_rotation_axis(t_tuple orientation, t_tuple *axis,
		double *cos_theta, double *sin_theta)
{
	t_tuple	up;

	up = vector(0, 1, 0);
	*axis = vector_cross_product(up, orientation);
	*cos_theta = vector_dot_product(up, orientation);
	*sin_theta = magnitude_of_vector(*axis);
	*axis = normalize_vector(*axis);
}

static t_matrix	build_rotation_matrix(double cos_theta, double sin_theta,
		t_tuple axis)
{
	t_matrix	rot;

	rot = new_matrix(4, 4);
	set_rotation_row_0(&rot, cos_theta, sin_theta, axis);
	set_rotation_row_1(&rot, cos_theta, sin_theta, axis);
	set_rotation_row_2_3(&rot, cos_theta, sin_theta, axis);
	return (rot);
}

t_matrix	orientation_matrix(t_tuple orientation)
{
	t_tuple		axis;
	double		cos_theta;
	double		sin_theta;
	t_matrix	rot;

	if (orientation.x == 0 && orientation.y == 1 && orientation.z == 0)
	{
		rot = identity_matrix(4);
		return (rot);
	}
	if (orientation.x == 0 && orientation.y == -1 && orientation.z == 0)
	{
		rot = rotation_x_matrix(M_PI);
		return (rot);
	}
	compute_rotation_axis(orientation, &axis, &cos_theta, &sin_theta);
	rot = build_rotation_matrix(cos_theta, sin_theta, axis);
	return (rot);
}

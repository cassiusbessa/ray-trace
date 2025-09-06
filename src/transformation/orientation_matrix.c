/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 20:17:50 by cassius          ###   ########.fr       */
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
	double		x;
	double		y;
	double		z;
	double		one_minus_cos;
	t_matrix	rot;

	x = axis.x;
	y = axis.y;
	z = axis.z;
	one_minus_cos = 1 - cos_theta;
	rot = new_matrix(4, 4);
	rot.data[0][0] = cos_theta + x * x * one_minus_cos;
	rot.data[0][1] = x * y * one_minus_cos - z * sin_theta;
	rot.data[0][2] = x * z * one_minus_cos + y * sin_theta;
	rot.data[0][3] = 0;
	rot.data[1][0] = y * x * one_minus_cos + z * sin_theta;
	rot.data[1][1] = cos_theta + y * y * one_minus_cos;
	rot.data[1][2] = y * z * one_minus_cos - x * sin_theta;
	rot.data[1][3] = 0;
	rot.data[2][0] = z * x * one_minus_cos - y * sin_theta;
	rot.data[2][1] = z * y * one_minus_cos + x * sin_theta;
	rot.data[2][2] = cos_theta + z * z * one_minus_cos;
	rot.data[2][3] = 0;
	rot.data[3][0] = 0;
	rot.data[3][1] = 0;
	rot.data[3][2] = 0;
	rot.data[3][3] = 1;
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

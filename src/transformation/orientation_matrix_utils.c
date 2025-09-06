/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_matrix_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:00:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/06 00:56:33 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_rotation_row_0(t_matrix *rot, double cos_theta,
		double sin_theta, t_tuple axis)
{
	double	x;
	double	y;
	double	z;
	double	one_minus_cos;

	x = axis.x;
	y = axis.y;
	z = axis.z;
	one_minus_cos = 1 - cos_theta;
	rot->data[0][0] = cos_theta + x * x * one_minus_cos;
	rot->data[0][1] = x * y * one_minus_cos - z * sin_theta;
	rot->data[0][2] = x * z * one_minus_cos + y * sin_theta;
	rot->data[0][3] = 0;
}

void	set_rotation_row_1(t_matrix *rot, double cos_theta,
		double sin_theta, t_tuple axis)
{
	double	x;
	double	y;
	double	z;
	double	one_minus_cos;

	x = axis.x;
	y = axis.y;
	z = axis.z;
	one_minus_cos = 1 - cos_theta;
	rot->data[1][0] = y * x * one_minus_cos + z * sin_theta;
	rot->data[1][1] = cos_theta + y * y * one_minus_cos;
	rot->data[1][2] = y * z * one_minus_cos - x * sin_theta;
	rot->data[1][3] = 0;
}

void	set_rotation_row_2_3(t_matrix *rot, double cos_theta,
		double sin_theta, t_tuple axis)
{
	double	x;
	double	y;
	double	z;
	double	one_minus_cos;

	x = axis.x;
	y = axis.y;
	z = axis.z;
	one_minus_cos = 1 - cos_theta;
	rot->data[2][0] = z * x * one_minus_cos - y * sin_theta;
	rot->data[2][1] = z * y * one_minus_cos + x * sin_theta;
	rot->data[2][2] = cos_theta + z * z * one_minus_cos;
	rot->data[2][3] = 0;
	rot->data[3][0] = 0;
	rot->data[3][1] = 0;
	rot->data[3][2] = 0;
	rot->data[3][3] = 1;
}

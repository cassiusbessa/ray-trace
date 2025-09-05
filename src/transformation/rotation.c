/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 20:04:25 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	rotation_x_matrix(float radians)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[1][1] = cos(radians);
	matrix.data[1][2] = -sin(radians);
	matrix.data[2][1] = sin(radians);
	matrix.data[2][2] = cos(radians);
	return (matrix);
}

t_matrix	rotation_y_matrix(float radians)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = cos(radians);
	matrix.data[0][2] = sin(radians);
	matrix.data[2][0] = -sin(radians);
	matrix.data[2][2] = cos(radians);
	return (matrix);
}

t_matrix	rotation_z_matrix(float radians)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = cos(radians);
	matrix.data[0][1] = -sin(radians);
	matrix.data[1][0] = sin(radians);
	matrix.data[1][1] = cos(radians);

	return (matrix);
}
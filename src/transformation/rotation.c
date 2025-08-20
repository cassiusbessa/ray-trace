/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 15:50:23 by emorshhe         ###   ########.fr       */
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
	t_matrix matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = cos(radians);
	matrix.data[0][1] = -sin(radians);
	matrix.data[1][0] = sin(radians);
	matrix.data[1][1] = cos(radians);

	return (matrix);
}
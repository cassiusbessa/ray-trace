/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/30 14:13:26 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	rotation_x(float r)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[1][1] = cos(r);
	matrix.data[1][2] = -sin(r);
	matrix.data[2][1] = sin(r);
	matrix.data[2][2] = cos(r);
	return (matrix);
}

t_matrix	rotation_y(float r)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = cos(r);
	matrix.data[0][2] = sin(r);
	matrix.data[2][0] = -sin(r);
	matrix.data[2][2] = cos(r);
	return (matrix);
}

t_matrix	rotation_z(float r)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = cos(r);
	matrix.data[0][1] = -sin(r);
	matrix.data[1][0] = sin(r);
	matrix.data[1][1] = cos(r);
	return (matrix);
}
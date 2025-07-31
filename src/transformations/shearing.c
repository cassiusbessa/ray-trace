/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/30 14:09:29 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_matrix matrix;

	matrix = identity_matrix(4);
	if (matrix.size < 4)
	{
		printf("❌ ERROR: Shearing matrix must be 4x4.\n");
		return matrix;
	}
	matrix.data[0][1] = xy;
	matrix.data[0][2] = xz;
	matrix.data[1][0] = yx;
	matrix.data[1][2] = yz;
	matrix.data[2][0] = zx;
	matrix.data[2][1] = zy;
	return (matrix);
}

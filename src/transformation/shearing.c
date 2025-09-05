/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 20:05:16 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	shearing_matrix(float xy, float xz, float yx, float yz, float zx,
		float zy)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);

	matrix.data[0][1] = xy;
	matrix.data[0][2] = xz;
	matrix.data[1][0] = yx;
	matrix.data[1][2] = yz;
	matrix.data[2][0] = zx;
	matrix.data[2][1] = zy;
	return (matrix);
}

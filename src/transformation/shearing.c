/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 23:29:46 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	shearing_matrix(t_shearing s)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][1] = s.xy;
	matrix.data[0][2] = s.xz;
	matrix.data[1][0] = s.yx;
	matrix.data[1][2] = s.yz;
	matrix.data[2][0] = s.zx;
	matrix.data[2][1] = s.zy;
	return (matrix);
}

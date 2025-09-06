/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 23:12:45 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	scaling_matrix(float x, float y, float z)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = x;
	matrix.data[1][1] = y;
	matrix.data[2][2] = z;
	return (matrix);
}

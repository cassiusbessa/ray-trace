/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 15:15:04 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	scaling_matrix(float x, float y, float z)
{
	t_matrix	matrix;

	matrix = identity_matrix(4);
	matrix.data[0][0] = x; // escala X
	matrix.data[1][1] = y; // escala Y
	matrix.data[2][2] = z; // escala Z
	return (matrix);
}

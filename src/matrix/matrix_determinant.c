/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:33:24 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:34:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	matrix_determinant_2x2(t_matrix matrix)
{
	return (matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1]
		* matrix.data[1][0]);
}

double	determinant_matrix(t_matrix a)
{
	double det;
	int col;

    det = 0.0;
	if (a.size == 1)
		return (a.data[0][0]);
	if (a.size == 2)
		return (a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0]);

	col = 0;
    while(col < a.size)
	{
		double cof = cofactor_matrix(a, 0, col);
		det += a.data[0][col] * cof;
        col++;
	}
	return (det);
}
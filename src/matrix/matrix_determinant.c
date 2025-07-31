/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_indetify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/30 08:14:02 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int			matrix_determinant(t_matrix matrix);
int			matrix_determinant_2x2(t_matrix matrix);
int			matrix_minor(t_matrix matrix, int row, int col);
int			matrix_cofactor(t_matrix matrix, int row, int col);
int			matrix_is_invertible(t_matrix matrix);

int	matrix_determinant(t_matrix matrix)
{
	int		det;
	int		i;
	int		sign;
	t_matrix	sub;

	if (matrix.size == 2)
		return matrix_determinant_2x2(matrix);
	det = 0;
	i = 0;
	while (i < matrix.size)
	{
		sub = submatrix(matrix, 0, i);
		if (i % 2 == 0)
			sign = 1;
		else
			sign = -1;
		det += sign * matrix.data[0][i] * matrix_determinant(sub);
		free_matrix(sub);
		i++;
	}
	return det;
}

int	matrix_determinant_2x2(t_matrix matrix)
{
	return (matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1]
		* matrix.data[1][0]);
}

int	matrix_minor(t_matrix matrix, int row, int col)
{
	t_matrix	sub;
	int		min;

	sub = submatrix(matrix, row, col);
	min = matrix_determinant(sub);
	return min;
}

int	matrix_cofactor(t_matrix matrix, int row, int col)
{
	int	min;

	min = matrix_minor(matrix, row, col);
	if ((row + col) % 2 != 0)
		min = -min;
	return (min);
}

int	matrix_is_invertible(t_matrix matrix)
{
	if (matrix_determinant(matrix) == 0)
		return (FALSE);
	return (TRUE);
}
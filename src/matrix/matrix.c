/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 14:07:57 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	new_matrix(int rows, int cols)
{
	t_matrix	matrix;
	int			i;
	int			j;

	matrix.size = rows;
	matrix.data = (float **)malloc(rows * sizeof(float *));
	i = 0;
	while (i < rows)
	{
		matrix.data[i] = (float *)malloc(cols * sizeof(float));
		j = 0;
		while (j < cols)
		{
			matrix.data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}

t_matrix	identity_matrix(int size)
{
	t_matrix	matrix;
	int			i;

	matrix = new_matrix(size, size);
	i = 0;
	while (i < size)
	{
		matrix.data[i][i] = 1;
		i++;
	}
	return (matrix);
}

t_bool	equal_matrix(t_matrix m1, t_matrix m2)
{
	int		i;
	int		j;
	float	diff;

	if (m1.size != m2.size)
		return (FALSE);
	i = 0;
	while (i < m1.size)
	{
		j = 0;
		while (j < m1.size)
		{
			diff = m1.data[i][j] - m2.data[i][j];
			if (diff < 0)
				diff = -diff;
			if (diff > EPSILON)
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	matrix_determinant_2x2(t_matrix matrix)
{
	return (matrix.data[0][0] * matrix.data[1][1] - matrix.data[0][1]
		* matrix.data[1][0]);
}

t_matrix	submatrix(t_matrix matrix, int row, int col)
{
	t_matrix sub;
	int i;
	int j;
	int i_sub;
	int j_sub;

	sub = new_matrix(matrix.size - 1, matrix.size - 1);
	i = 0;
	i_sub = 0;
	while (i < matrix.size)
	{
		if (i != row)
		{
			j = 0;
			j_sub = 0;
			while (j < matrix.size)
			{
				if (j != col)
				{
					sub.data[i_sub][j_sub] = matrix.data[i][j];
					j_sub++;
				}
				j++;
			}
			i_sub++;
		}
		i++;
	}
	return (sub);
}
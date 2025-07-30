/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:53:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/23 01:04:57 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


t_matrix matrix_inverse(t_matrix matrix)
{
	float det;
	int i;
	int j;
	t_matrix inv;

	det = (float)matrix_determinant(matrix);
	if (det == 0)
	{
		printf("Error: Matrix is not invertible (determinant is 0).\n");
		exit(1);
	}
	inv = new_matrix(matrix.size, matrix.size);
	i = 0;
	while (i < matrix.size)
	{
		j = 0;
		while (j < matrix.size)
		{
			inv.data[j][i] = (float)matrix_cofactor(matrix, i, j) / det;
			j++;
		}
		i++;
	}
	return (inv);
}


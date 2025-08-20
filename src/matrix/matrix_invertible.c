/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invertible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:30:27 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 13:13:14 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_invertible(t_matrix matrix)
{
	int	determinant;

	determinant = determinant_matrix(matrix);
	return (determinant);
}

t_matrix	invert_matrix(t_matrix matrix)
{
	float		det;
	t_matrix	inverse;
	float		cof;

	int i, j;
	det = determinant_matrix(matrix);
	if (det == 0)
		return (new_matrix(0, 0)); // matriz não invertível
	inverse = new_matrix(matrix.size, matrix.size);
	i = 0;
	while (i < matrix.size)
	{
		j = 0;
		while (j < matrix.size)
		{
			cof = cofactor_matrix(matrix, i, j);
			inverse.data[j][i] = cof / det; // transposta dos cofatores
			j++;
		}
		i++;
	}
	return (inverse);
}

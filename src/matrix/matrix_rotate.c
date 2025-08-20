/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/22 23:37:05 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	transpose_matrix(t_matrix matrix)
{
	t_matrix result;
	int i;
	int j;

	result = new_matrix(matrix.size, matrix.size);
	i = 0;
	while (i < matrix.size)
	{
		j = 0;
		while (j < matrix.size)
		{
			result.data[i][j] = matrix.data[j][i];
			j++;
		}
		i++;
	}
	return (result);
}
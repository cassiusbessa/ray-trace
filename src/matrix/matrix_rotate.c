/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:33:16 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:34:01 by emorshhe         ###   ########.fr       */
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
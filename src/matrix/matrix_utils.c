/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/03 17:35:18 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_matrix(t_matrix matrix)
{
	int	i;

	i = 0;
	while (i < matrix.size)
	{
		free(matrix.data[i]);
		i++;
	}
	free(matrix.data);
}

void	print_matrix(t_matrix matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < matrix.size)
	{
		j = 0;
		while (j < matrix.size)
		{
			printf("%f ", matrix.data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

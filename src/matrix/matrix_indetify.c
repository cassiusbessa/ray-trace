/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_indetify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/06 10:54:13 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

void    print_matrix(t_matrix matrix)
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

void    free_matrix(t_matrix matrix)
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

t_bool	equal_matrix(t_matrix m1, t_matrix m2)
{
	int	i;
	int	j;

	if (m1.size != m2.size)
		return (FALSE);
	i = 0;
	while (i < m1.size)
	{
		j = 0;
		while (j < m1.size)
		{
			if (m1.data[i][j] != m2.data[i][j])
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

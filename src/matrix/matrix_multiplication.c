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

t_matrix	matrix_multiply_by_matrix(t_matrix m1, t_matrix m2)
{
	t_matrix	result;
	int			i;
	int			j;
	int			k;

	result = new_matrix(m1.size, m1.size);
	i = 0;
	while (i < m1.size)
	{
		j = 0;
		while (j < m1.size)
		{
			k = 0;
			while (k < m1.size)
			{
				result.data[i][j] += m1.data[i][k] * m2.data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_tuple	matrix_multiply_by_tuple(t_matrix m, t_tuple t)
{
	t_tuple	result;
	int		i;
	int		j;
	double	value;

	result = new_tuple(0, 0, 0, 0);
	i = 0;
	while (i < m.size)
	{
		j = 0;
		while (j < m.size)
		{
			value = m.data[i][j] * get_tuple_value(t, j);
			set_tuple_value(&result, i, get_tuple_value(result, i) + value);
			j++;
		}
		i++;
	}
	return (result);
}

t_matrix    transpose_matrix(t_matrix matrix)
{
    t_matrix    result;
    int         i;
    int         j;

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

t_matrix	submatrix(t_matrix matrix, int row, int col)
{
	t_matrix sub;
	int i;
	int j;
	int i_sub;
	int j_sub;

	sub = new_matrix(matrix.size - 1, matrix.size - 1);
	i = -1;
	i_sub = 0;
	while (++i < matrix.size)
	{
		if (i != row)
		{
			j = -1;
			j_sub = 0;
			while (++j < matrix.size)
			{
				if (j != col)
					sub.data[i_sub][j_sub++] = matrix.data[i][j];
			}
			i_sub++;
		}
	}
	return (sub);
}



t_matrix	matrix_multiply_by_matrix(t_matrix a, t_matrix b);
t_tuple		matrix_multiply_by_tuple(t_matrix m, t_tuple t);
t_matrix	transpose_matrix(t_matrix matrix);
t_matrix	submatrix(t_matrix matrix, int row, int col);

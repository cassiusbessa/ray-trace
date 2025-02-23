/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:30:27 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/22 22:39:41 by caqueiro         ###   ########.fr       */
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

static double	get_tuple_value(t_tuple t, int index)
{
	if (index == 0)
		return (t.x);
	if (index == 1)
		return (t.y);
	if (index == 2)
		return (t.z);
	return (t.w);
}

static void set_tuple_value(t_tuple *t, int index, double value)
{
    if (index == 0)
        t->x = value;
    if (index == 1)
        t->y = value;
    if (index == 2)
        t->z = value;
    if (index == 3)
        t->w = value;
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

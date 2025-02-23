/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:53:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/22 23:55:11 by caqueiro         ###   ########.fr       */
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

t_matrix    identity_matrix(int size)
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

t_bool    equal_matrix(t_matrix m1, t_matrix m2)
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


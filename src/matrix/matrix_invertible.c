/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invertible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:30:27 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/26 20:34:48 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"



/* ====================== ALLOC DATA ====================== */
static void alloc_matrix_data(t_matrix *m, int size)
{
    m->data = malloc(sizeof(float *) * size);
    if (!m->data)
        return;
    for (int i = 0; i < size; i++)
    {
        m->data[i] = malloc(sizeof(float) * size);
        if (!m->data[i])
        {
            while (--i >= 0)
                free(m->data[i]);
            free(m->data);
            m->data = NULL;
            return;
        }
    }
    m->size = size;
}
static void set_index(t_matrix *a, int row, int col, double value)
{
    if (!a->data || row < 0 || row >= a->size || col < 0 || col >= a->size)
        return;
    a->data[row][col] = (float)value;
}


/* ====================== INVERT_MATRIX ====================== */
t_matrix invert_matrix(t_matrix m, int *success)
{
    t_matrix inv;
    double det;

    ft_bzero(&inv, sizeof(t_matrix));
    inv.size = 4;

    alloc_matrix_data(&inv, 4);
    if (!inv.data)
    {
        *success = 0;
        return inv;
    }

    det = determinant_matrix(m);

    if (fabs(det) < 1e-6)
    {
        *success = 0;

        t_matrix id = identity_matrix(4);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                inv.data[i][j] = id.data[i][j];
        return inv;
    }

    *success = 1;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            set_index(&inv, i, j, cofactor_matrix(m, j, i) / det);

    return inv;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invertible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:33:32 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:34:07 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void set_index(t_matrix *a, int row, int col, double value)
{
    if (!a->data || row < 0 || row >= a->size || col < 0 || col >= a->size)
        return;
    a->data[row][col] = (float)value;
}

static void alloc_matrix_data(t_matrix *m, int size)
{
    int i;

    m->data = malloc(sizeof(float *) * size);
    if (!m->data)
        return;
    i = 0;
    while(i < size)
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
        i++;
    }
    m->size = size;
}

static void copy_identity_matrix(t_matrix *dest)
{
    t_matrix id;
    int i;
    int j;

    id = identity_matrix(4);
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest->data[i][j] = id.data[i][j];
            j++;
        }
        i++;
    }
}

static void compute_inverse_matrix(t_matrix m, t_matrix *inv, double det)
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            set_index(inv, i, j, cofactor_matrix(m, j, i) / det);
            j++;
        }
        i++;
    }
}

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
        copy_identity_matrix(&inv);
        return inv;
    }
    *success = 1;
    compute_inverse_matrix(m, &inv, det);
    return inv;
}


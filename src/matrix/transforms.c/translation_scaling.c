/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_scaling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/30 09:24:15 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix    translation(int size, float *data)
{
    t_matrix    matrix;
    int         i;

    matrix = identity_matrix(size);
    if (size < 4)
    {
        printf("❌ ERROR: Translation matrix must be 4x4.\n");
        return (matrix);
    }
    if (!data)
    {
        printf("❌ ERROR: Null data pointer for scaling.\n");
        return matrix;
    }
    i = 0;
    while(i < size - 1)
    {
        matrix.data[i][size - 1] = data[i];
        i++;
    }
    return (matrix);
}


t_matrix scaling(int size, float *data)
{
    t_matrix    matrix;
    int i;

    matrix = identity_matrix(size);
    if (size < 3)
    {
        printf("❌ ERROR: Scaling matrix must be at least 3x3.\n");
        return (matrix);
    }
    if (!data)
    {
        printf("❌ ERROR: Null data pointer for scaling.\n");
        return matrix;
    }
    i = 0;
    while(i < size - 1)
    {
        matrix.data[i][i] = data[i];
        i++;
    }
    matrix.data[size - 1][size - 1] = 1;
    return (matrix);
}

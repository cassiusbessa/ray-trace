/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:01:26 by cassius           #+#    #+#             */
/*   Updated: 2025/08/13 21:45:22 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int determinant_matrix(t_matrix a)
{
    int det;
    int col;
    
    det = 0;

    if (a.size == 1)
        return a.data[0][0];

    if (a.size == 2)
        return matrix_determinant_2x2(a);
    else 
    {
        col = 0;
        while (col < a.size) 
        {
            det += a.data[0][col] * cofactor_matrix(a, 0, col);
            col++;
        }
    }
    return det;
}
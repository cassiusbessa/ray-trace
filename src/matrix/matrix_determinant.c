/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:01:26 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 13:11:27 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float determinant_matrix(t_matrix a)
{
    float det;
    int col;
    float cof;

    det = 0.0f;

    if (a.size == 1)
        return a.data[0][0];

    if (a.size == 2)
        return matrix_determinant_2x2(a);
    else 
    {
        col = 0;
        while (col < a.size) 
        {
            cof = cofactor_matrix(a, 0, col);
            det += a.data[0][col] * cof;
            col++;
        }
    }
    return det;
}

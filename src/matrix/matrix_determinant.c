/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:01:26 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 20:16:11 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double determinant_matrix(t_matrix a)
{
    double det = 0.0;
    int col;

    if (a.size == 1)
        return a.data[0][0];
    if (a.size == 2)
        return (a.data[0][0] * a.data[1][1] -
                a.data[0][1] * a.data[1][0]);

    for (col = 0; col < a.size; col++)
    {
        double cof = cofactor_matrix(a, 0, col);
        det += a.data[0][col] * cof;
    }
    return det;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:41:07 by cassius           #+#    #+#             */
/*   Updated: 2025/08/13 20:50:15 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int cofactor_matrix(t_matrix matrix, int row, int col)
{
    int minor;

    minor = minor_matrix(matrix, row, col);
    if ((row + col) % 2 == 0)
        return (minor);
    return (-minor);
}
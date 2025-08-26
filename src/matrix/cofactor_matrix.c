/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:41:07 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 20:15:45 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double cofactor_matrix(t_matrix matrix, int row, int col)
{
    double minor = minor_matrix(matrix, row, col);
    if ((row + col) % 2)
        return -minor;
    return minor;
}

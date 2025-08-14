/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 14:10:25 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix translation_matrix(float x, float y, float z)
{
    t_matrix matrix;

    matrix = identity_matrix(4);
    matrix.data[0][3] = x;
    matrix.data[1][3] = y;
    matrix.data[2][3] = z;

    return (matrix);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 16:08:11 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix shearing_matrix(float xy, float xz, float yx, float yz, float zx, float zy)
{
    t_matrix matrix;

    matrix = identity_matrix(4); // Começa com matriz identidade 4x4

    // Define os valores de cisalhamento
    matrix.data[0][1] = xy; // x move em proporção a y
    matrix.data[0][2] = xz; // x move em proporção a z
    matrix.data[1][0] = yx; // y move em proporção a x
    matrix.data[1][2] = yz; // y move em proporção a z
    matrix.data[2][0] = zx; // z move em proporção a x
    matrix.data[2][1] = zy; // z move em proporção a y

    return matrix;
}

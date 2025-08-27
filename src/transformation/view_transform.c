/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/27 19:50:29 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Cria apenas a matriz de orientação da câmera
static t_matrix view_orientation(t_tuple from, t_tuple to, t_tuple up)
{
    t_tuple forward = normalize_vector(sub_tuples(to, from));
    t_tuple upn = normalize_vector(up);
    t_tuple left = vector_cross_product(forward, upn);
    t_tuple true_up = vector_cross_product(left, forward);

    t_matrix orientation = new_matrix(4, 4);

    orientation.data[0][0] = left.x;
    orientation.data[0][1] = left.y;
    orientation.data[0][2] = left.z;
    orientation.data[0][3] = 0.0f;

    orientation.data[1][0] = true_up.x;
    orientation.data[1][1] = true_up.y;
    orientation.data[1][2] = true_up.z;
    orientation.data[1][3] = 0.0f;

    orientation.data[2][0] = -forward.x;
    orientation.data[2][1] = -forward.y;
    orientation.data[2][2] = -forward.z;
    orientation.data[2][3] = 0.0f;

    orientation.data[3][0] = 0.0f;
    orientation.data[3][1] = 0.0f;
    orientation.data[3][2] = 0.0f;
    orientation.data[3][3] = 1.0f;

    return orientation;
}

// Função principal que combina orientação e translação
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up)
{
    t_matrix orientation = view_orientation(from, to, up);
    t_matrix translation = translation_matrix(-from.x, -from.y, -from.z);

    t_matrix result = matrix_multiply_by_matrix(orientation, translation);

    free_matrix(orientation);
    free_matrix(translation);

    return result;
}

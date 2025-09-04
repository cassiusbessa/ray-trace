/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/04 12:48:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix orientation_matrix(t_tuple orientation)
{
    t_tuple up = vector(0, 1, 0); // eixo padrão do cilindro

    // Se já estiver alinhado com o eixo Y positivo, retorna identidade
    if (orientation.x == 0 && orientation.y == 1 && orientation.z == 0)
        return identity_matrix(4);

    // Se estiver alinhado com o eixo Y negativo, gira 180° em X
    if (orientation.x == 0 && orientation.y == -1 && orientation.z == 0)
        return rotation_x_matrix(M_PI);

    // Para qualquer outro vetor, usa Rodrigues
    t_tuple axis = vector_cross_product(up, orientation);
    double cos_theta = vector_dot_product(up, orientation);
    double sin_theta = magnitude_of_vector(axis);

    axis = normalize_vector(axis);

    double x = axis.x;
    double y = axis.y;
    double z = axis.z;
    double one_minus_cos = 1 - cos_theta;

    t_matrix rot = new_matrix(4, 4);

    rot.data[0][0] = cos_theta + x * x * one_minus_cos;
    rot.data[0][1] = x * y * one_minus_cos - z * sin_theta;
    rot.data[0][2] = x * z * one_minus_cos + y * sin_theta;
    rot.data[0][3] = 0;

    rot.data[1][0] = y * x * one_minus_cos + z * sin_theta;
    rot.data[1][1] = cos_theta + y * y * one_minus_cos;
    rot.data[1][2] = y * z * one_minus_cos - x * sin_theta;
    rot.data[1][3] = 0;

    rot.data[2][0] = z * x * one_minus_cos - y * sin_theta;
    rot.data[2][1] = z * y * one_minus_cos + x * sin_theta;
    rot.data[2][2] = cos_theta + z * z * one_minus_cos;
    rot.data[2][3] = 0;

    rot.data[3][0] = 0;
    rot.data[3][1] = 0;
    rot.data[3][2] = 0;
    rot.data[3][3] = 1;

    return rot;
}

// Função segura de orientação da câmera
static t_matrix view_orientation(t_tuple from, t_tuple to, t_tuple up)
{
    t_tuple forward = normalize_vector(sub_tuples(to, from));
    t_tuple upn = normalize_vector(up);

    t_tuple left = vector_cross_product(forward, upn);

    // Proteção: se forward e up são colineares
    if (magnitude_of_vector(left) < 1e-6) {
        if (fabs(upn.y) > 0.99f)
            upn = vector(0, 0, 1); // muda up para Z
        else
            upn = vector(0, 1, 0); // mantém padrão
        left = vector_cross_product(forward, upn);
    }

    left = normalize_vector(left);
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

// Função segura de view_transform
t_matrix view_transform(t_tuple from, t_tuple to, t_tuple up)
{
    t_matrix orientation = view_orientation(from, to, up);
    t_matrix translation = translation_matrix(-from.x, -from.y, -from.z);

    t_matrix result = matrix_multiply_by_matrix(orientation, translation);

    free_matrix(orientation);
    free_matrix(translation);

    return result;
}

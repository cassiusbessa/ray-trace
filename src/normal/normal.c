/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:46:50 by cassius           #+#    #+#             */
/*   Updated: 2025/09/03 09:44:35 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// static t_tuple normal_at_sphere(t_sphere s, t_tuple p)
// {
//     t_tuple normal;

//     normal = sub_tuples(p, s.center);
//     normal.w = 0;
//     return (normalize_vector(normal));
// }

t_tuple normal_at(t_object o, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;
    t_matrix inv;
    t_matrix invT;

    if (o.type == SPHERE)
    {
        // Mundo -> espaço do objeto
        int success;
        inv = invert_matrix(o.transform, &success);
        if (!success || !inv.data)
        {
            return vector(0, 0, 0);
        }

        object_point = matrix_multiply_by_tuple(inv, world_point);

        // Normal no espaço do objeto (esfera centrada na origem)
        object_normal = sub_tuples(object_point, point(0, 0, 0));
        object_normal.w = 0; // garante que é vetor

        // Normal do objeto -> espaço do mundo
        invT = transpose_matrix(inv);
        world_normal = matrix_multiply_by_tuple(invT, object_normal);
        world_normal.w = 0; // garante vetor

        // Normaliza com segurança
        world_normal = safe_normalize_vector(world_normal);

        free_matrix(invT);
        free_matrix(inv);
    }
    else
    {
        world_normal = vector(0, 0, 0);
    }

    return world_normal;
}

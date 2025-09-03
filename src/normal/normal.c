/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:46:50 by cassius           #+#    #+#             */
/*   Updated: 2025/09/03 20:03:21 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// ----------------------------
// Normal de uma esfera
// ----------------------------
t_tuple normal_at_sphere(t_object *obj, t_tuple world_point)
{
    t_matrix inv;
    t_matrix invT;
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;

    int success;
    inv = invert_matrix(obj->transform, &success);
    if (!success || !inv.data)
        return vector(0, 0, 0);

    // Ponto no espaço local do objeto
    object_point = matrix_multiply_by_tuple(inv, world_point);

    // Normal da esfera centrada na origem
    object_normal = sub_tuples(object_point, point(0, 0, 0));
    object_normal.w = 0;

    // Transforma a normal para o espaço do mundo
    invT = transpose_matrix(inv);
    world_normal = matrix_multiply_by_tuple(invT, object_normal);
    world_normal.w = 0;
    world_normal = safe_normalize_vector(world_normal);

    free_matrix(invT);
    free_matrix(inv);

    return world_normal;
}

// ----------------------------
// Normal de um cilindro
// ----------------------------

t_tuple normal_at_cylinder(t_object *obj, t_tuple world_point)
{
    int success;
    t_matrix inv = invert_matrix(obj->transform, &success);
    if (!success || !inv.data)
        return vector(0, 0, 0);

    t_tuple local_point = matrix_multiply_by_tuple(inv, world_point);
    t_cylinder *cyl = (t_cylinder *)obj->data;

    float dist = local_point.x * local_point.x + local_point.z * local_point.z;
    t_tuple local_normal;
    float epsilon = 1e-4f;

    // Top cap
    if (cyl->closed && dist <= cyl->radius * cyl->radius &&
        local_point.y >= cyl->height / 2.0f - epsilon)
    {
        local_normal = vector(0, 1, 0);
        printf("[DEBUG] Cylinder top cap normal local: (%f,%f,%f)\n",
            local_normal.x, local_normal.y, local_normal.z);
    }
    // Bottom cap
    else if (cyl->closed && dist <= cyl->radius * cyl->radius &&
             local_point.y <= -cyl->height / 2.0f + epsilon)
    {
        local_normal = vector(0, -1, 0);
        printf("[DEBUG] Cylinder bottom cap normal local: (%f,%f,%f)\n",
            local_normal.x, local_normal.y, local_normal.z);
    }
    // Lateral
    else
    {
        // Normal lateral inicial
        t_tuple lateral_normal = vector(local_point.x, 0, local_point.z);

        // Garantir que normal lateral aponte para fora
        t_tuple from_center = vector(local_point.x, 0, local_point.z); // vetor do centro até o ponto
        if (vector_dot_product(lateral_normal, from_center) < 0)
            lateral_normal = vector(-lateral_normal.x, 0, -lateral_normal.z);

        local_normal = safe_normalize_vector(lateral_normal);

        printf("[DEBUG] Cylinder side normal local: (%f,%f,%f)\n",
            local_normal.x, local_normal.y, local_normal.z);
    }

    // Transformar para o mundo
    t_matrix trans_inv = transpose_matrix(inv);
    t_tuple world_normal = matrix_multiply_by_tuple(trans_inv, local_normal);
    world_normal.w = 0;
    world_normal = safe_normalize_vector(world_normal);

    printf("[DEBUG] Cylinder normal world: (%f,%f,%f)\n",
        world_normal.x, world_normal.y, world_normal.z);

    free_matrix(inv);
    free_matrix(trans_inv);

    return world_normal;
}


// ----------------------------
// Dispatcher de normal
// ----------------------------
t_tuple normal_at(t_object *obj, t_tuple world_point)
{
    if (!obj)
        return vector(0, 0, 0);

    if (obj->type == SPHERE)
        return normal_at_sphere(obj, world_point);
    else if (obj->type == CYLINDER)
        return normal_at_cylinder(obj, world_point);
    // adicione outros tipos no futuro
    return vector(0, 0, 0);
}

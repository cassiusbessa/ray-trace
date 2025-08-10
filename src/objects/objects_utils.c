/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:18:46 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_objects(t_object *obj)
{
    t_object *tmp;

    while (obj)
    {
        tmp = obj->next;

        if (obj->shape)
            free(obj->shape);

        free(obj);
        obj = tmp;
    }
}
t_object *create_object(t_obj_type type, void *shape, t_color base_color, char **tokens,
    int specular_index, int shininess_index,
    int transparency_index, int ior_index)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return NULL;

    obj->type = type;
    obj->shape = shape;
    obj->material = default_material();
    obj->material.base_color = base_color;

    printf("[DEBUG create_object] Base color: (%.2f, %.2f, %.2f)\n", 
           base_color.r, base_color.g, base_color.b);

    if (tokens[specular_index])
    {
        obj->material.specular_coef = parse_float(tokens[specular_index]);
        printf("[DEBUG create_object] Specular coef (index %d): %f\n", specular_index, obj->material.specular_coef);
    }
    else
        printf("[DEBUG create_object] Specular coef (index %d): NULL\n", specular_index);

    if (tokens[shininess_index])
    {
        obj->material.shininess = parse_float(tokens[shininess_index]);
        printf("[DEBUG create_object] Shininess (index %d): %f\n", shininess_index, obj->material.shininess);
    }
    else
        printf("[DEBUG create_object] Shininess (index %d): NULL\n", shininess_index);

    if (tokens[transparency_index])
    {
        obj->material.transparency = parse_float(tokens[transparency_index]);
        printf("[DEBUG create_object] Transparency (index %d): %f\n", transparency_index, obj->material.transparency);
    }
    else
        printf("[DEBUG create_object] Transparency (index %d): NULL\n", transparency_index);

    if (tokens[ior_index])
    {
        obj->material.ior = parse_float(tokens[ior_index]);
        printf("[DEBUG create_object] IOR (index %d): %f\n", ior_index, obj->material.ior);
    }
    else
        printf("[DEBUG create_object] IOR (index %d): NULL\n", ior_index);

    obj->next = NULL;
    return obj;
}

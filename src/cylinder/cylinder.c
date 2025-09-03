/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:14:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/03 19:09:19 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder new_cylinder(void)
{
    t_cylinder cyl;

    cyl.radius = 1.0f; // cilindro unitário, raio 1
    cyl.height = 2.0f; // altura 2, centrado na origem
    cyl.closed = 0;    // cilindro aberto por padrão
    return cyl;
}

t_object new_cylinder_object(t_tuple center, t_tuple orientation, float diameter, float height, t_rgb color, t_bool closed)
{
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        return (t_object){0};

    *cylinder = new_cylinder();
    cylinder->radius = diameter / 2.0f;
    cylinder->height = height;
    cylinder->closed = closed;

    t_object obj = new_object(CYLINDER, cylinder);
    obj.material = new_material_default();
    obj.material.color = color;

    t_matrix scale = scaling_matrix(cylinder->radius, height / 2.0f, cylinder->radius);
    t_matrix rotate = orientation_matrix(orientation);
    t_matrix translate = translation_matrix(center.x, center.y, center.z);

    t_matrix tmp = matrix_multiply_by_matrix(rotate, scale);
    t_matrix transform = matrix_multiply_by_matrix(translate, tmp);
    set_object_transform(&obj, transform);

    free_matrix(scale);
    free_matrix(rotate);
    free_matrix(translate);
    free_matrix(tmp);

    return obj;
}

// Transformar o raio para o espaço local do cilindro
static t_bool transform_ray_to_local(t_ray ray, t_object *obj, t_ray *local_ray)
{
    int success;
    t_matrix inv = invert_matrix(obj->transform, &success);
    if (!success)
        return FALSE;

    *local_ray = transform_ray(ray, inv, &success);
    free_matrix(inv);
    return success;
}

// Interseção com a lateral do cilindro usando raio local
static void intersect_cylinder_sides(t_ray ray, t_object *obj, t_intersection_list *list)
{
    t_cylinder *cyl = (t_cylinder *)obj->data;
    t_quad q = solve_quadratic_for_cylinder(ray, cyl->radius);

    for (int i = 0; i < q.count; i++)
    {
        float t = (i == 0) ? q.x1 : q.x2;
        float y = ray.origin.y + t * ray.direction.y;

        if (y >= -cyl->height / 2.0f && y <= cyl->height / 2.0f)
            add_node_ordered(t, list, obj);
    }
}

// Interseção com tampas do cilindro
static void intersect_cylinder_caps(t_ray ray, t_object *obj, t_intersection_list *list)
{
    t_cylinder *cyl = (t_cylinder *)obj->data;

    if (!cyl->closed || fabs(ray.direction.y) < EPSILON)
        return;

    // Top cap
    float t_top = (cyl->height / 2.0f - ray.origin.y) / ray.direction.y;
    float x_top = ray.origin.x + t_top * ray.direction.x;
    float z_top = ray.origin.z + t_top * ray.direction.z;
    if ((x_top * x_top + z_top * z_top) <= cyl->radius * cyl->radius)
        add_node_ordered(t_top, list, obj);

    // Bottom cap
    float t_bottom = (-cyl->height / 2.0f - ray.origin.y) / ray.direction.y;
    float x_bot = ray.origin.x + t_bottom * ray.direction.x;
    float z_bot = ray.origin.z + t_bottom * ray.direction.z;
    if ((x_bot * x_bot + z_bot * z_bot) <= cyl->radius * cyl->radius)
        add_node_ordered(t_bottom, list, obj);
}

// Função principal de interseção do cilindro
t_intersection_list *intersect_ray_cylinder(t_ray ray, t_object *obj)
{
    t_ray local_ray;
    t_intersection_list *list = new_intersection_list();
    if (!list)
        return NULL;

    if (!transform_ray_to_local(ray, obj, &local_ray))
        return list;

    intersect_cylinder_sides(local_ray, obj, list);
    intersect_cylinder_caps(local_ray, obj, list);

    return list;
}
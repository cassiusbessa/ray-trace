/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 19:26:09 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int is_shadowed(t_world *world, t_tuple point, t_point_light light)
{
    t_tuple v = sub_tuples(light.position, point);
    float distance = magnitude_of_vector(v);
    t_tuple direction = safe_normalize_vector(v);

    t_ray r = create_ray(point, direction);
    t_intersection_list *xs = intersect_world(world, &r);

    t_intersection_node *current = xs ? xs->head : NULL;
    while (current)
    {
        if (current->t > EPSILON && current->t < distance)
        {
            free_intersection_list(xs);
            return 1;
        }
        current = current->next;
    }

    free_intersection_list(xs);
    return 0;
}

t_tuple safe_normalize_vector(t_tuple v)
{
    float mag = magnitude_of_vector(v);
    if (mag < EPSILON)
    {
        return vector(0, 0, 0);
    }
    return multiply_tuple_by_scalar(v, 1.0f / mag);
}

// ----------------------------
t_rgb shade_hit(t_world *world, t_comps comps)
{
    t_material          *mat;
    t_rgb               color;
    t_point_light_node  *current;

    // pegar o material do objeto atingido
    mat = &((t_sphere *)comps.object->data)->material;

    // inicializar cor acumulada como preto
    color = new_rgb(0, 0, 0);

    // percorre todas as luzes da cena
    current = world->lights->head;
    while (current)
    {
        t_point_light light = current->light;

        // soma a contribuição de cada luz
        t_rgb contribution = lighting(*mat, light,
                                      comps.point,
                                      comps.eyev,
                                      comps.normalv,
                                      0);

        color = add_rgb(color, contribution);

        current = current->next;
    }

    return color;
}


t_rgb color_at(t_world *world, t_ray ray)
{
    t_intersection_list *xs;
    t_intersection_node *hit_node;
    t_comps comps;

    if (!world)
        return new_rgb(0, 0, 0);

    xs = intersect_world(world, &ray);
    hit_node = hit(*xs);
    if (!hit_node)
    {
        free_intersection_list(xs);
        return new_rgb(0, 0, 0);            // nenhuma interseção → preto
    }

    comps = prepare_computations(*hit_node, ray);
    t_rgb color = shade_hit(world, comps);

    free_intersection_list(xs);
    return color;
}





t_intersection_node *get_node(int i,t_intersection_list *list)

{
    t_intersection_node *current;
    int count;

    if (!list || i < 0 || i >= list->count)
        return (NULL);
    current = list->head;
    count = 0;
    while (current)
    {
        if (count == i)
            return (current);
        current = current->next;
        count++;
    }
    return (NULL);
}

t_intersection_list *intersect_world(t_world *world, t_ray *ray)
{
    t_intersection_list *dest;
    t_object_node *current_obj;
    t_intersection_list *src;

    if (!world || !ray || !world->objects || !world->objects->head)
        return NULL;

    dest = new_intersection_list();
    if (!dest)
        return NULL;

    current_obj = world->objects->head;
    while (current_obj)
    {
        src = intersect(*ray, &current_obj->object);
        if (src)
        {
            // Adiciona cada interseção individualmente, mantendo a ordem
            t_intersection_node *node = src->head;
            while (node)
            {
                add_node_ordered(node->t, dest, node->object);
                node = node->next;
            }
            free_intersection_list(src); // libera a lista temporária

        }
        current_obj = current_obj->next;
    }

    return dest;
}

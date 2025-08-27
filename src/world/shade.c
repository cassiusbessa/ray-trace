/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 21:50:38 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


t_simple_intersection make_simple_intersection(float t, t_object *obj)
{
    t_simple_intersection s;
    s.t = t;
    s.object = obj;
    return s;
}
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
    t_rgb result = new_rgb(0, 0, 0);
    t_point_light_node *current = world->lights->head;

    while (current)
    {
        int in_shadow = is_shadowed(world, comps.over_point, current->light);
        t_material mat;
        if (comps.object->type == SPHERE)
            mat = ((t_sphere *)comps.object->data)->material;
        t_tuple lightv = sub_tuples(current->light.position, comps.over_point);
        lightv = safe_normalize_vector(lightv);
        t_rgb surface = lighting(
            mat,
            current->light,
            comps.over_point,
            comps.eyev,
            comps.normalv,
            in_shadow
        );
        result = add_rgb(result, surface);
        current = current->next;
    }
    t_rgb clamped = clamp_color(result);
    return clamped;
}

// ----------------------------
// t_rgb color_at(t_world world, t_ray ray)
// {
//     t_rgb result;
//     t_intersection_list *intersections = intersect_world(&world, &ray);
//     t_intersection_node *hit_node = intersections ? hit(*intersections) : NULL;

//     if (hit_node)
//     {
//         t_simple_intersection i = make_simple_intersection(hit_node->t, hit_node->object);
//         t_comps comps = prepare_computations(i, ray);
//         result = shade_hit(&world, comps);
//     }
//     else
//         result = new_rgb(0, 0, 0);
//     free_intersection_list(intersections);
//     return result;
// }

// ----------------------------

// t_comps prepare_computations(t_intersection_node i, t_ray r)
// {
//     t_comps comps;

//     comps.t = i.t;
//     comps.object = i.object;

//     comps.point = ray_position(r, i.t);
//     comps.eyev = negate_vector(r.direction);
//     comps.normalv = normal_at(*i.object, comps.point);

//     if (magnitude_of_vector(comps.normalv) < EPSILON)
//     {
//         comps.normalv = negate_vector(r.direction);
//     }

//     comps.normalv = safe_normalize_vector(comps.normalv);

//     if (vector_dot_product(comps.normalv, comps.eyev) < 0.0f)
//     {
//         comps.inside = TRUE;
//         comps.normalv = negate_vector(comps.normalv);
//     }
//     else
//         comps.inside = FALSE;

//     comps.over_point = add_tuples(comps.point,
//                                   multiply_tuple_by_scalar(comps.normalv, EPSILON));

//     return comps;
// }



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

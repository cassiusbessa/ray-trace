/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:17:13 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_ray shadow_ray(t_tuple point, t_point_light light, float *distance)
{
    t_tuple v;
    t_tuple direction;
    t_ray r;

    v = sub_tuples(light.position, point);
    *distance = magnitude_of_vector(v);
    direction = safe_normalize_vector(v);
    r = create_ray(point, direction);

    return (r);
}

static t_bool has_blocking_intersection(t_intersection_list *xs, float distance)
{
    t_intersection_node *current;

    current = xs->head;
    while (current)
    {
        if (current->t > SHADOW_EPSILON && current->t < distance - EPSILON)
            return TRUE;
        current = current->next;
    }
    return (FALSE);
}

t_bool is_shadowed(t_world *world, t_tuple point)
{
    t_bool result;
    t_point_light light;
    t_ray r;
    t_intersection_list *xs;
    float distance;

    xs = NULL;
    distance = 0.0f;
    if (!world->lights || !world->lights->head)
        return FALSE;

    light = world->lights->head->light;

    r = shadow_ray(point, light, &distance);
    xs = intersect_world(world, &r);

    result = has_blocking_intersection(xs, distance);
    free_intersection_list(xs);

    return (result);
}

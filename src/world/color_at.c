/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:18:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 21:15:22 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_rgb process_hit(t_world *world, t_ray ray, t_intersection_node *hit_node, t_intersection_list *xs)
{
    t_comps comps;
    t_rgb   color;

    comps = (t_comps){0};
    color = new_rgb(0, 0, 0);
    comps = prepare_computations(*hit_node, ray);
    color = shade_hit(world, comps);
    free_intersection_list(xs);
    return (color);
}

t_rgb color_at(t_world *world, t_ray ray)
{
    t_intersection_list *xs;
    t_intersection_node *hit_node;
    t_rgb   color;

    xs = NULL;
    hit_node = NULL;
    color = new_rgb(0, 0, 0);
    if (!world)
        return (color);
    xs = intersect_world(world, &ray);
    hit_node = hit(*xs);
    if (!hit_node)
    {
        free_intersection_list(xs);
        return (color);
    }
    return (process_hit(world, ray, hit_node, xs));
}

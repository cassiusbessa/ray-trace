/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:54:10 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 22:27:00 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_comps prepare_computations(t_intersection_node i, t_ray r)
{
    t_comps comps;

    comps.t = i.t;
    comps.object = i.object;
    comps.point = ray_position(r, i.t);
    comps.eyev = negate_vector(r.direction);
    comps.normalv = normal_at(*i.object, comps.point);
    comps.inside = 0;
    if (vector_dot_product(comps.normalv, comps.eyev) < 0)
    {
        comps.inside = 1;
        comps.normalv = negate_vector(comps.normalv);
    }
    else
    {
        comps.inside = 0;
    }
    return comps;
}
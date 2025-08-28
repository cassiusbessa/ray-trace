/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:54:10 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 23:15:02 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_comps prepare_computations(t_intersection_node i, t_ray r)
{
    t_comps comps;
    t_tuple point;
    t_tuple eyev;
    t_tuple normalv;
    t_bool inside;

    comps.t = i.t;
    comps.object = i.object;
    point = ray_position(r, i.t);
    eyev = negate_vector(r.direction);

    normalv = normal_at(*i.object, point);

    if (vector_dot_product(normalv, eyev) < 0)
    {
        inside = TRUE;
        normalv = negate_vector(normalv);
    }
    else
        inside = FALSE;
    comps.point = point;
    comps.eyev = eyev;
    comps.normalv = normalv;
    comps.inside = inside;
    comps.over_point = add_tuples(point,
        multiply_tuple_by_scalar(normalv, EPSILON));
    return comps;
}

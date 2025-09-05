/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:54:10 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 16:35:57 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_comps	prepare_computations(t_intersection_node i, t_ray r)
{
	t_comps comps;
	float eps;

	comps.point = ray_position(r, i.t);
	comps.eyev = negate_vector(r.direction);
	comps.normalv = normal_at(i.object, comps.point);
	set_inside(&comps.normalv, comps.eyev, &comps.inside);
	eps = compute_dynamic_epsilon(i.object, comps.point);
	comps.over_point = add_tuples(comps.point,
			multiply_tuple_by_scalar(comps.normalv, eps));
	comps.t = i.t;
	comps.object = i.object;
	return (comps);
}

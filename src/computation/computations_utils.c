/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:30:19 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 16:32:00 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	eps_sphere(t_sphere *s, t_tuple point)
{
	float	dist;

	dist = magnitude_of_vector(sub_tuples(point, s->center));
	return (0.01f * fmaxf(s->radius, dist));
}

static float	eps_cylinder(t_cylinder *c)
{
	float	max_dim;

	max_dim = fmaxf(c->radius, c->height);
	return (0.01f * max_dim);
}

float	compute_dynamic_epsilon(t_object *obj, t_tuple point)
{
	float	eps;
	float	eps_min;

	if (!obj)
		return (SHADOW_EPSILON);
	eps_min = 0.01f;
	eps = SHADOW_EPSILON;
	if (obj->type == SPHERE)
		eps = eps_sphere((t_sphere *)obj->data, point);
	else if (obj->type == CYLINDER)
		eps = eps_cylinder((t_cylinder *)obj->data);
	if (eps < eps_min)
		eps = eps_min;
	return (eps);
}

void	set_inside(t_tuple *normalv, t_tuple eyev, t_bool *inside)
{
	if (vector_dot_product(*normalv, eyev) < 0)
	{
		*inside = TRUE;
		*normalv = negate_vector(*normalv);
	}
	else
		*inside = FALSE;
}

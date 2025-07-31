/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/30 18:47:40 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_ray	ray(t_tuple origin, t_tuple direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_tuple	position(t_ray r, float t)
{
	return (add(r.origin, scale(r.direction, t)));
}

t_ray	transform_ray(t_ray r, t_matrix m)
{
	t_ray	result;

	result.origin = multiply_matrix_tuple(m, r.origin);
	result.direction = multiply_matrix_tuple(m, r.direction);
	return (result);
}

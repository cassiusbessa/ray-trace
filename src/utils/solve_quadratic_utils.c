/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:02:46 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:05:22 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_bool	float_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

static float	ft_discriminant(float a, float b, float c)
{
	return (b * b - 4.0f * a * c);
}

t_quad	ft_quadratic(float a, float b, float c)
{
	t_quad	result;
	float	delta;
	float	sqrt_delta;

	result.count = 0;
	result.x1 = 0.0f;
	result.x2 = 0.0f;
	if (float_equal(a, 0.0f))
		return (result);
	delta = ft_discriminant(a, b, c);
	if (delta < 0.0f)
		return (result);
	if (float_equal(delta, 0.0f))
	{
		result.count = 1;
		result.x1 = -b / (2.0f * a);
		result.x2 = result.x1;
		return (result);
	}
	sqrt_delta = sqrtf(delta);
	result.count = 2;
	result.x1 = (-b - sqrt_delta) / (2.0f * a);
	result.x2 = (-b + sqrt_delta) / (2.0f * a);
	return (result);
}

t_intersection	ft_quad_to_intersection(t_quad q, void *object)
{
	t_intersection	result;

	if (q.count == 0)
	{
		result = new_intersection(0, 0.0f, 0.0f, NULL);
		return (result);
	}
	result = new_intersection(2, q.x1, q.x2, object);
	return (result);
}

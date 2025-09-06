/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:34:47 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 23:09:26 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	magnitude_of_vector(t_tuple t)
{
	if (t.w != 0)
		t.w = 0;
	return (sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2)));
}

t_tuple	normalize_vector(t_tuple t)
{
	t_tuple	normalized;
	double	mag;

	if (t.w != 0)
		t.w = 0;
	mag = magnitude_of_vector(t);
	if (mag < EPSILON)
		return (vector(0, 0, 0));
	normalized.x = t.x / mag;
	normalized.y = t.y / mag;
	normalized.z = t.z / mag;
	normalized.w = 0;
	return (normalized);
}

float	vector_dot_product(t_tuple t1, t_tuple t2)
{
	if (t1.w != 0 || t2.w != 0)
	{
		t1.w = 0;
		t2.w = 0;
	}
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z);
}

t_tuple	vector_cross_product(t_tuple t1, t_tuple t2)
{
	t_tuple	cross;

	if (t1.w != 0 || t2.w != 0)
	{
		t1.w = 0;
		t2.w = 0;
	}
	cross = new_tuple(0, 0, 0, 0);
	cross.x = t1.y * t2.z - t1.z * t2.y;
	cross.y = t1.z * t2.x - t1.x * t2.z;
	cross.z = t1.x * t2.y - t1.y * t2.x;
	cross.w = 0;
	return (cross);
}

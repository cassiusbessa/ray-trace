/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:34:47 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/16 00:37:21 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	magnitude_of_vector(t_tuple t)
{
	if (t.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (-1);
	}
	return (sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2)));
}

t_tuple	normalize_vector(t_tuple t)
{
	t_tuple	normalized;
	float	magnitude;

	if (t.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (new_tuple(0, 0, 0, FALSE));
	}
	magnitude = magnitude_of_vector(t);
	normalized.x = t.x / magnitude;
	normalized.y = t.y / magnitude;
	normalized.z = t.z / magnitude;
	normalized.w = 0;
	return (new_tuple(normalized.x, normalized.y, normalized.z, FALSE));
}

float	vector_dot_product(t_tuple t1, t_tuple t2)
{
	if (t1.w == TRUE || t2.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (-1);
	}
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z);
}

t_tuple	vector_cross_product(t_tuple t1, t_tuple t2)
{
	t_tuple cross;

	if (t1.w == TRUE || t2.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (t1);
	}
	cross = new_tuple(0, 0, 0, FALSE);
	cross.x = t1.y * t2.z - t1.z * t2.y;
	cross.y = t1.z * t2.x - t1.x * t2.z;
	cross.z = t1.x * t2.y - t1.y * t2.x;
	cross.w = 0;
	return (cross);
}
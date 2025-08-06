/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:53:45 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/06 12:11:51 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	normalize_vector(t_tuple t)
{
	t_tuple	normalized;
	float	magnitude;

	if (t.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (new_tuple(0, 0, 0, FALSE));
	}
	magnitude = magnitude_vector(t);
	if (magnitude == 0.0f)
	{
		printf("❌ ERROR: Cannot normalize zero vector.\n");
		return (new_tuple(0, 0, 0, FALSE));
	}
	normalized.x = t.x / magnitude;
	normalized.y = t.y / magnitude;
	normalized.z = t.z / magnitude;
	normalized.w = 0;
	return (new_tuple(normalized.x, normalized.y, normalized.z, FALSE));
}

float	vector_dot(t_tuple t1, t_tuple t2)
{
	if (t1.w == TRUE || t2.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (-1);
	}
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z);
}

t_tuple	vector_cross(t_tuple t1, t_tuple t2)
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
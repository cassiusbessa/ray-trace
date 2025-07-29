/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/29 19:42:37 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	add_tuple(t_tuple t1, t_tuple t2);
t_tuple	subtract_tuple(t_tuple t1, t_tuple t2);
t_tuple	multiply_tuple(t_tuple t, float scalar);


t_tuple	add_tuple(t_tuple t1, t_tuple t2)
{
	t_tuple	result;

	result.x = t1.x + t2.x;
	result.y = t1.y + t2.y;
	result.z = t1.z + t2.z;
	result.w = t1.w;
	return (result);
}

t_tuple	subtract_tuple(t_tuple t1, t_tuple t2)
{
	t_tuple	result;

	result.x = t1.x - t2.x;
	result.y = t1.y - t2.y;
	result.z = t1.z - t2.z;
	result.w = t1.w - t2.w;
	return (result);
}

t_tuple	multiply_tuple(t_tuple t, float scalar)
{
	t_tuple	result;

	result.x = t.x * scalar;
	result.y = t.y * scalar;
	result.z = t.z * scalar;
	result.w = t.w;
	return (result);
}

t_tuple	divide_tuple(t_tuple t, float scalar)
{
	t_tuple	result;

	result.x = t.x / scalar;
	result.y = t.y / scalar;
	result.z = t.z / scalar;
	result.w = t.w;

	return (result);
}

float	magnitude_vector(t_tuple t)
{
	if (t.w == TRUE)
	{
		printf("❌ ERROR: The tuple is a point, not a vector.\n");
		return (-1);
	}
	return (sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2)));
}
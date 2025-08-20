/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/19 08:08:01 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	new_tuple(float x, float y, float z, t_bool is_point);
t_tuple	add_tuples(t_tuple t1, t_tuple t2);
t_tuple	sub_tuples(t_tuple t1, t_tuple t2);
t_tuple	multiply_tuple_by_scalar(t_tuple t, float scalar);

t_tuple	new_tuple(float x, float y, float z, t_bool is_point)
{
	t_tuple	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = is_point;
	return (t);
}

t_tuple	add_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	result;

	result.x = t1.x + t2.x;
	result.y = t1.y + t2.y;
	result.z = t1.z + t2.z;
	result.w = t1.w;
	return (result);
}

t_tuple	sub_tuples(t_tuple t1, t_tuple t2)
{
	t_tuple	result;

	result.x = t1.x - t2.x;
	result.y = t1.y - t2.y;
	result.z = t1.z - t2.z;
	result.w = t1.w - t2.w;
	return (result);
}

t_tuple	multiply_tuple_by_scalar(t_tuple t, float scalar)
{
	t_tuple	result;

	result.x = t.x * scalar;
	result.y = t.y * scalar;
	result.z = t.z * scalar;
	result.w = t.w;
	return (result);
}

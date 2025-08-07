/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:49:59 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	new_tuple(float x, float y, float z, t_bool is_point)
{
	t_tuple	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = is_point;
	return (result);
}

t_tuple point_tuple(float x, float y, float z)
{
    t_tuple result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = TRUE;

    return (result);
}

t_tuple vector_tuple(float x, float y, float z)
{
    t_tuple result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = FALSE;
    return (result);
}

int	tuple_equal(t_tuple t1, t_tuple t2)
{
    return (fabs(t1.x - t2.x) < EPSILON &&
            fabs(t1.y - t2.y) < EPSILON &&
            fabs(t1.z - t2.z) < EPSILON &&
            t1.w == t2.w);
}


t_tuple	negate_tuple(t_tuple t)
{
	t_tuple	result;

	result.x = -t.x;
	result.y = -t.y;
	result.z = -t.z;
	result.w = t.w;

	return (result);
}
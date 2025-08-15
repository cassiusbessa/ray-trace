/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 22:12:52 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection  new_intersection(int count, float enter, float exit)
{
    t_intersection  result;

    result.count = count;
    result.enter = enter;
    result.exit = exit;
    return (result);
}

static t_bool float_equal(float a, float b)
{
    return (fabsf(a - b) < EPSILON);
}

t_bool equal_intersections(t_intersection i1, t_intersection i2)
{
    return (i1.count == i2.count
        && float_equal(i1.enter, i2.enter)
        && float_equal(i1.exit, i2.exit));
}
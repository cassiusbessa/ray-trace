/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/08/21 01:16:38 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection	new_intersection(int count, float enter, float exit,
		void *object)
{
	t_intersection	result;

	result.count = count;
	result.enter = enter;
	result.exit = exit;
	result.object = object;
	return (result);
}

t_bool	equal_intersections(t_intersection i1, t_intersection i2)
{
	return (i1.count == i2.count && float_equal(i1.enter, i2.enter)
		&& float_equal(i1.exit, i2.exit));
}
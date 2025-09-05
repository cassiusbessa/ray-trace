/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:53:45 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 20:45:49 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	print_tuple(t_tuple *t)
{
	printf("x: %f, y: %f, z: %f, w: %d\n", t->x, t->y, t->z, t->w);
}

t_tuple	point(float x, float y, float z)
{
	return (new_tuple(x, y, z, TRUE));
}

t_tuple	vector(float x, float y, float z)
{
	return (new_tuple(x, y, z, FALSE));
}

t_bool	equal_tuples(t_tuple t1, t_tuple t2)
{
	if (fabs(t1.x - t2.x) > EPSILON)
		return (FALSE);
	if (fabs(t1.y - t2.y) > EPSILON)
		return (FALSE);
	if (fabs(t1.z - t2.z) > EPSILON)
		return (FALSE);
	if (t1.w != t2.w)
		return (FALSE);
	return (TRUE);
}

t_tuple	negate_vector(t_tuple v)
{
	return (vector(-v.x, -v.y, -v.z));
}

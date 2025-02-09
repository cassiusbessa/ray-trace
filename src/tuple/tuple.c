/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/09 01:25:49 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	*new_tuple(float x, float y, float z, t_bool is_point);
void		print_tuple(t_tuple *t);
t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*sub_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*multiply_tuple_by_scalar(t_tuple *t, float scalar);

t_tuple	*new_tuple(float x, float y, float z, t_bool is_point)
{
	t_tuple	*t;

	t = malloc(sizeof(t_tuple));
	if (!t)
		return (NULL);
	t->x = x;
	t->y = y;
	t->z = z;
	t->w = (int)is_point;
	return (t);
}

t_tuple	*add_tuples(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*result;

	if(t1->w + t2->w == 2)
		return (NULL);
	result = malloc(sizeof(t_tuple));
	result->x = t1->x + t2->x;
	result->y = t1->y + t2->y;
	result->z = t1->z + t2->z;
	result->w = t1->w + t2->w;
	return (result);
}

t_tuple	*sub_tuple(t_tuple *t1, t_tuple *t2)
{
	t_tuple	*result;

	if (t1->w - t2->w == -1)
		return (NULL);
	result = malloc(sizeof(t_tuple));
	result->x = t1->x - t2->x;
	result->y = t1->y - t2->y;
	result->z = t1->z - t2->z;
	result->w = t1->w - t2->w;
	return (result);
}

t_tuple	*multiply_tuple_by_scalar(t_tuple *t, float scalar)
{
	t_tuple	*result;

	result = malloc(sizeof(t_tuple));
	result->x = t->x * scalar;
	result->y = t->y * scalar;
	result->z = t->z * scalar;
	result->w = t->w;
	return (result);
}

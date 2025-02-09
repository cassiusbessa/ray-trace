/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 22:38:40 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_touple	*new_touple(float x, float y, float z, t_bool is_point);
void		print_touple(t_touple *t);
t_touple	*add_touple(t_touple *t1, t_touple *t2);
t_touple	*sub_touple(t_touple *t1, t_touple *t2);
t_touple	*multiply_tuple_by_scalar(t_touple *t, float scalar);

t_touple	*new_touple(float x, float y, float z, t_bool is_point)
{
	t_touple	*t;

	t = malloc(sizeof(t_touple));
	if (!t)
		return (NULL);
	t->x = x;
	t->y = y;
	t->z = z;
	t->w = (int)is_point;
	return (t);
}

t_touple	*add_touple(t_touple *t1, t_touple *t2)
{
	t_touple	*result;

	if(t1->w + t2->w == 2)
		return (NULL);
	result = malloc(sizeof(t_touple));
	result->x = t1->x + t2->x;
	result->y = t1->y + t2->y;
	result->z = t1->z + t2->z;
	result->w = t1->w + t2->w;
	return (result);
}

t_touple	*sub_touple(t_touple *t1, t_touple *t2)
{
	t_touple	*result;

	if (t1->w - t2->w == -1)
		return (NULL);
	result = malloc(sizeof(t_touple));
	result->x = t1->x - t2->x;
	result->y = t1->y - t2->y;
	result->z = t1->z - t2->z;
	result->w = t1->w - t2->w;
	return (result);
}

t_touple	*multiply_tuple_by_scalar(t_touple *t, float scalar)
{
	t_touple	*result;

	result = malloc(sizeof(t_touple));
	result->x = t->x * scalar;
	result->y = t->y * scalar;
	result->z = t->z * scalar;
	result->w = t->w;
	return (result);
}

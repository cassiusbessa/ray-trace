/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:42:13 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 19:54:08 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_touple	*new_touple(float x, float y, float z, t_bool is_point);
void    print_touple(t_touple *t);

t_touple	*new_touple(float x, float y, float z, t_bool is_point)
{
	t_touple *t;

	t = malloc(sizeof(t_touple));
	if (!t)
		return (NULL);
	t->x = x;
	t->y = y;
	t->z = z;
	t->w = (int)is_point;
	return (t);
}

void    print_touple(t_touple *t)
{
	printf("x: %f, y: %f, z: %f, w: %d\n", t->x, t->y, t->z, t->w);
}
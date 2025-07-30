/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:53:45 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/30 08:22:01 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	print_tuple(t_tuple *t)
{
	printf("x: %f, y: %f, z: %f, w: %d\n", t->x, t->y, t->z, t->w);
}

double	get_tuple_value(t_tuple t, int index)
{
	if (index == 0)
		return (t.x);
	if (index == 1)
		return (t.y);
	if (index == 2)
		return (t.z);
	return (t.w);
}

void	set_tuple_value(t_tuple *t, int index, double value)
{
	if (index == 0)
		t->x = value;
	if (index == 1)
		t->y = value;
	if (index == 2)
		t->z = value;
	if (index == 3)
		t->w = value;
}


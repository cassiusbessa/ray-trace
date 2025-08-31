/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/08/29 19:47:20 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection_node	*hit(t_intersection_list l)
{
	t_intersection_node	*hit;
	t_intersection_node	*current;

	hit = NULL;
	current = l.head;
	while (current)
	{
		if (current->t >= 0.0f)
		{
			if (!hit || current->t < hit->t)
				hit = current;
		}
		current = current->next;
	}
	return (hit);
}

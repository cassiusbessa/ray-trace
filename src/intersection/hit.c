/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:32:21 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:33:57 by emorshhe         ###   ########.fr       */
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

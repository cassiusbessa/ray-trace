/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:32:21 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 21:28:16 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection_node	*get_node(int i, t_intersection_list *list)
{
	t_intersection_node	*current;
	int					count;

	if (!list || i < 0 || i >= list->count)
		return (NULL);
	current = list->head;
	count = 0;
	while (current)
	{
		if (count == i)
			return (current);
		current = current->next;
		count++;
	}
	return (NULL);
}

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

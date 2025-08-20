/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 23:22:59 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection_node	*hit(t_intersection_list l)
{
    t_intersection_node	*hit;

    hit = NULL;
    while (l.head)
    {
        if (l.head->t >= 0.0f)
        {
            if (!hit || l.head->t < hit->t)
                hit = l.head;
        }
        l.head = l.head->next;
    }
    return (hit);
}

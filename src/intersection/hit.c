/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 10:03:26 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection hit(t_intersections xs)
{
    t_intersection result;
    int found;
    int i;

    result = new_intersection(0, 0.0f, 0.0f, NULL);
    i =0;
    found = 0;
    while(i < xs.count)
    {
        if (xs.list[i].enter >= 0.0f)
        {
            if (!found || xs.list[i].enter < result.enter)
            {
                result = xs.list[i];
                found = 1;
            }
        }
        i++;
    }
    return (result);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/06 18:14:37 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void free_parsed_world(t_world *world, int should_free_world)
{
    t_object *current;
    t_object *next;

    if (!world)
        return;

    current = world->objects;
    while (current)
    {
        next = current->next;
        if (current->type == SPHERE)
            free(current->object);
        else if (current->type == PLANE)
            free(current->object);
        else if (current->type == CYLINDER)
            free(current->object);
        
        free(current);
        current = next;
    }
    if (should_free_world)
        free(world);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:32:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int ft_isspace(int c)
{
    return (c == ' '  || 
            c == '\t' || 
            c == '\n' || 
            c == '\v' || 
            c == '\f' || 
            c == '\r');
}


int line_is_empty_or_comment(const char *line)
{
    while (*line)
    {
        if (*line == '#')
            return 1;
        if (!ft_isspace(*line))
            return 0;
        line++;
    }
    return (1);
}

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

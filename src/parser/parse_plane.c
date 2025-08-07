/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:28:53 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object *create_plane(t_tuple position, t_tuple orientation, t_color color)
{
	t_plane *plane;
	t_object *object;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);

	plane->position = position;
	plane->normal = orientation; // ✅ usar 'normal'
	plane->color = color;        // ✅ garantir que 'color' exista na struct

	object = malloc(sizeof(t_object));
	if (!object)
	{
		free(plane);
		return (NULL);
	}

	object->type = PLANE;
	object->object = plane;
	object->next = NULL;

	return (object);
}


int parse_plane(const char *line, t_world *world)
{
    char **tokens;
    t_tuple position;
    t_tuple orientation;
    t_color color;
    t_object *plane;

    tokens = ft_split(line, ' ');
    if(!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
        return (print_error("Plane: invalid number of parameters"), free_split(tokens), -1);
    if (ft_strncmp(tokens[0], "pl", 2) != 0)
        return (print_error("Plane: expected identifier 'pl'"), free_split(tokens), -1);

    if (!parse_vector(tokens[1], &position))
        return (print_error("Plane: invalid position"), free_split(tokens), -1);
    
    if(!parse_vector(tokens[2], &orientation))
        return (print_error("Plane: invalid orientation"), free_split(tokens), -1);
    if(!is_normalized(orientation))
        return (print_error("Plane: orientation vector must be normalized"), free_split(tokens), -1);
    
    if(!parse_color(tokens[3], &color))
        return (print_error("Plane: invalid color"), free_split(tokens), -1);
    
    plane = create_plane(position, orientation, color);
    if (!plane)
        return (print_error("Plane: allocation failed"), free_split(tokens), -1);
    
    add_object_to_world(world, plane);

    free_split(tokens);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/06 14:48:29 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int is_normalized(t_tuple v)
{
    float mag;
    float diff;

    mag = magnitude_vector(v);
    diff = mag - 1.0f;
    if (diff < 0)
        diff = -diff;

    return (diff < 1e-6);
}


t_object *new_cylinder(t_tuple position, t_tuple orientation, float diameter, float height, t_color color)
{
	t_cylinder  *cylinder;
    t_object    *object;

    cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->position = position;
	cylinder->orientation = orientation;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;

    object = malloc(sizeof(t_object));
	if (!object)
	{
		free(cylinder);
		return (NULL);
	}
	object->type = CYLINDER;
	object->object = cylinder;
	object->next = NULL;
	return (object);
}

void add_object_to_world(t_world *world, t_object *new_object)
{
    if (!new_object)
        return ;
    new_object->next = world->objects;
    world->objects = new_object;
}

int parse_cylinder(const char *line,  t_world *world)
{
    char **tokens;
    t_tuple position;
    t_tuple orientation;
    t_color color;
    float diameter;
    float height;
    t_object *cylinder;

    tokens = ft_split(line, ' ');
    if(!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
        return(print_error("Cylinder: invalid number of parameters"), free_split(tokens), -1);
    if(ft_strncmp(tokens[0], "cy", 3) != 0)
        return(print_error("Cylinder: expected identifier 'cy'"), free_split(tokens), -1);
    
    if(!parse_vector(tokens[1], &position))
        return(print_error("Cylinder: invalid position"), free_split(tokens), -1);
        
    if(!parse_vector(tokens[2], &orientation))
        return(print_error("Cylinder: invalid orientation"), free_split(tokens), -1);
    if(!is_normalized(orientation))
        return(print_error("Cylinder: orientation vector must be normalized"), free_split(tokens), -1);
    
    diameter = ft_atod(tokens[3]);
    if(diameter <= 0)
        return(print_error("Cylinder: invalid diameter"), free_split(tokens), -1);
    
    height = ft_atod(tokens[4]);
    if (height <= 0)
        return (print_error("Cylinder: invalid height"), free_split(tokens), -1);
    
    if(!parse_color(tokens[5], &color))
        return(print_error("Cylinder: invalid color"), free_split(tokens), -1);
    
    cylinder = new_cylinder(position, orientation, diameter, height, color);
    if (!cylinder)
        return (print_error("Cylinder: memory allocation failed"), free_split(tokens), -1);
    
    add_object_to_world(world, cylinder);
    free_split(tokens);
    return (0);
}
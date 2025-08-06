/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/06 18:40:29 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_object *create_sphere(t_tuple position, float diameter, t_color color)
{
    t_sphere *sphere;
    t_object *object;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (NULL);

    sphere->position = position;
    sphere->diameter = diameter;
    sphere->color = color;
    
    object = malloc(sizeof(t_object));
    if (!object)
    {
        free(sphere);
        return (NULL);
    }
    object->type = SPHERE;
    object->object = sphere;
    object->next = NULL;

    return (object);
}


int parse_sphere(const char *line, t_world *world)
{
    char **tokens;
    t_tuple position;
    float diameter;
    t_color color;
    t_object *sphere;

    tokens = ft_split(line, ' ');
    if(!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
        return (print_error("Sphere: invalid number of parameters"), free_split(tokens), -1);
    if (ft_strncmp(tokens[0], "sp", 3) != 0)
        return (print_error("Sphere: expected identifier 'sp'"), free_split(tokens), -1);
    if(!parse_point(tokens[1], &position))
        return (print_error("Sphere: invalid position"), free_split(tokens), -1);
    diameter = ft_atod(tokens[2]);
    if(diameter <= 0)
        return (print_error("Sphere: invalid diameter"), free_split(tokens), -1);

    if(!parse_color(tokens[3], &color))
        return (print_error("Sphere: invalid color"), free_split(tokens), -1);

    sphere = create_sphere(position, diameter, color);
    if (!sphere)
        return (print_error("Sphere: memory allocation failed"), free_split(tokens), -1);

    add_object_to_world(world, sphere);
    free_split(tokens);
    return (0);
}
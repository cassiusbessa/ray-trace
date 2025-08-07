/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:22:30 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int parse_light(const char *line, t_world *world)
{
    char **tokens;
    t_tuple position;
    t_color color;
    float intensity;
    t_light *light;
    t_light_list *new_light;
    
    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
        return (print_error("Light: invalid number of parameters"), free_split(tokens), -1);
    if(ft_strncmp(tokens[0], "L", 2) != 0)
        return (print_error("Light: expected identifier 'L'"), free_split(tokens), -1);
    if(!parse_vector(tokens[1], &position))
        return (print_error("Light: invalid position"), free_split(tokens), -1);
    intensity = ft_atod(tokens[2]);
    if(intensity < 0 || intensity > 1)
        return (print_error("Light: invalid intensity"), free_split(tokens), -1);
    if(!parse_color(tokens[3], &color))
        return (print_error("Light: invalid color"), free_split(tokens), -1);

    light = malloc(sizeof(t_light));
    if (!light)
        return (print_error("Light: memory allocation failed"), free_split(tokens), -1);
    
    light->position = position;
    light->intensity = color;
    light->intensity.r *= intensity;
    light->intensity.g *= intensity;
    light->intensity.b *= intensity;

    new_light = malloc(sizeof(t_light_list));
    if(!new_light)
    {
        free(light);
        return (print_error("Light: memory allocation failed"), free_split(tokens), -1);
    }
    new_light->light = *light;
    new_light->next = world->lights;
    world->lights = new_light;

    free(light);
    free_split(tokens);

    return(0);
}
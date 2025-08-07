/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:29:50 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float deg_to_rad(float degrees)
{
    float   radians;

    radians = degrees * (PI / 180.0f);
    return (radians);
}


int parse_camera(const char *line, t_world *world)
{
    char **tokens;
    t_tuple position;
    t_tuple direction;
    float fov;
    float fov_rad;
    t_camera camera;

    tokens = ft_split(line, ' ');
    if(!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
        return (print_error("Camera: invalid number of parameters"), free_split(tokens), -1);
    if (ft_strncmp(tokens[0], "C", 2) != 0)
        return (print_error("Camera: expected identifier 'C'"), free_split(tokens), -1);
    if(!parse_vector(tokens[1], &position))
        return (print_error("Camera: invalid position"), free_split(tokens), -1);
    if(!parse_vector(tokens[2], &direction))
        return (print_error("Camera: invalid orientation"), free_split(tokens), -1);

    fov = ft_atod(tokens[3]);
    if(fov < 0 || fov > 180)
        return (print_error("Camera: invalid FOV"), free_split(tokens), -1);

    fov_rad = deg_to_rad(fov);
    direction = normalize_vector(direction);

    camera.hsize = HSIZE;
    camera.vsize = VSIZE;
    camera.fov = fov_rad;
    camera.transform = view_transform(position, direction, vector_tuple(0, 1, 0));

    world->camera = camera;
    free_split(tokens);
    return (0);
}
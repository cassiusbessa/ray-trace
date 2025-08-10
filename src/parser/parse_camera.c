/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 18:49:18 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int parse_camera(const char *line, t_scene *scene)
{
    char **tokens = ft_split(line, ' ');
    if (!tokens || !tokens[1] || !tokens[2] || !tokens[3])
    {
        ft_free_split(tokens);
        return 0;
    }

    t_vec3 origin = parse_vec3(tokens[1]);
    t_vec3 look_at = parse_vec3(tokens[2]);
    double fov = parse_float(tokens[3]);

    init_camera(&scene->camera, origin, look_at, fov, WIDTH, HEIGHT);

    ft_free_split(tokens);
    return 1;
}




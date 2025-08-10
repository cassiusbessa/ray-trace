/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 19:02:15 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int parse_rt_file(char *filename, t_scene *scene)
{
    int fd;
    char *line;
    int line_number = 0;

    printf("Tentando abrir arquivo: %s\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        print_error("Failed to open file", NULL);

    while ((line = get_next_line(fd)) != NULL)
    {
        line_number++;

        if (line_is_empty_or_comment(line))
        {
            free(line);
            continue;
        }

        if (starts_with(line, "A "))
            parse_ambient(line, scene);
        else if (starts_with(line, "L "))
            parse_point_light(line, scene);
        else if (starts_with(line, "SP "))
            parse_sphere(line, scene);
        else if (starts_with(line, "PL "))
            parse_plane(line, scene);
        else if (starts_with(line, "CY "))
            parse_cylinder(line, scene);
        else if (starts_with(line, "C "))
            parse_camera(line, scene);
        else
            ft_printf("Invalid line prefix at line %d: %s", line_number, line);

        free(line);
    }

    close(fd);
    return 0;
}


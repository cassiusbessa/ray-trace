/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 20:00:34 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int parse_rt_file(const char *filename, t_world *world)
{
    FILE *file;
    char *line;
    size_t len;
    ssize_t read;

    file = fopen(filename, "r");
    if (!file)
        return (fprintf(stderr, "Error opening file: %s\n", filename), -1);

    line = NULL;
    len = 0;
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (line_is_empty_or_comment(line))
            continue;

        if (starts_with(line, "A "))
            parse_ambient(line, world);
        else if (starts_with(line, "C "))
            parse_camera(line, world);
        else if (starts_with(line, "L "))
            parse_light(line, world);
        else if (starts_with(line, "sp "))
            parse_sphere(line, world);
        else if (starts_with(line, "pl "))
            parse_plane(line, world);
        else if (starts_with(line, "cy "))
            parse_cylinder(line, world);
        else
            print_error("Invalid line prefix");
    }

    free(line);
    fclose(file);
    return 0;
}
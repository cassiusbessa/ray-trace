/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:27:11 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include "../../utils/libft/libft.h"

int parse_rt_file(const char *filename, t_world *world)
{
    int fd;
    char *line;
    int line_number;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (fprintf(stderr, "Error opening file: %s\n", filename), -1);
    line_number = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        line_number++;
        if (line_is_empty_or_comment(line))
        {
            free(line);
            continue;
        }
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
            ft_printf("Invalid line prefix at line %d: %s", line_number, line);
        free(line);
    }
    close(fd);
    return 0;
}


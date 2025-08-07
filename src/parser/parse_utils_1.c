/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 13:00:40 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


int starts_with(const char *line, const char *prefix)
{
    while (*prefix)
    {
        if (*line != *prefix)
            return 0;
        line++;
        prefix++;
    }
    return 1;
}

void print_error(const char *msg)
{
    ft_printf("Parser Error: %s\n", msg);
}

int parse_color(const char *str, t_color *out_color)
{
    char **tokens;
    float r;
    float g;
    float b;

    tokens = ft_split(str, ',');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
    {
        free_split(tokens);
        return 0;
    }
    r = ft_atod(tokens[0]);
    g = ft_atod(tokens[1]);
    b = ft_atod(tokens[2]);

    r = r / 255.0f;
    g = g / 255.0f;
    b = b / 255.0f;

    *out_color = create_color(r, g, b);

    free_split(tokens);
    return (1);
}

int parse_vector(const char *str, t_tuple *out_vector)
{
    char **tokens;
    float x;
    float y;
    float z;
    int w;

    tokens = ft_split(str, ',');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
    {
        free_split(tokens);
        return 0;
    }
    x = ft_atod(tokens[0]);
    y = ft_atod(tokens[1]);
    z = ft_atod(tokens[2]);
    if(tokens[3])
    {
        if (tokens[3] && ft_strcmp(tokens[3], "point") == 0)
            w = 1;
        else if (tokens[3] && ft_strcmp(tokens[3], "vector") == 0)
            w = 0;
        else
        {
            free_split(tokens);
            return 0;
        }
    }
    *out_vector = new_tuple(x, y, z, w);
    free_split(tokens);
    return (1);
}

int parse_point(const char *str, t_tuple *point)
{
    char **coords;
    float x, y, z;

    coords = ft_split(str, ',');
    if (!coords || !coords[0] || !coords[1] || !coords[2])
    {
        free_split(coords);
        return 0;
    }

    x = ft_atod(coords[0]);
    y = ft_atod(coords[1]);
    z = ft_atod(coords[2]);

    free_split(coords);

    *point = new_tuple(x, y, z, 1);

    return 1;
}
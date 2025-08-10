/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 09:35:17 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

 
int starts_with(const char *str, const char *prefix)
{
    int i = 0;
    unsigned char s;
    unsigned char p;

    if (!str || !prefix)
        return 0;

    while (prefix[i])
    {
        s = (unsigned char)str[i];
        p = (unsigned char)prefix[i];

        if (ft_tolower(s) != ft_tolower(p))
            return 0;
        i++;
    }
    return 1;
}


void free_point_lights(t_scene *scene)
{
    if (scene->point_lights)
    {
        free(scene->point_lights);
        scene->point_lights = NULL;
        scene->n_point_lights = 0;
    }
}


int line_is_empty_or_comment(const char *line)
{
    int i = 0;

    if (!line)
        return 1; // linha nula considera vazia

    // Pula espaços em branco no início
    while (line[i] && isspace((unsigned char)line[i]))
        i++;

    // Se chegou no fim da string, linha é vazia
    if (line[i] == '\0')
        return 1;

    // Se o primeiro caractere não espaço for '#', é comentário
    if (line[i] == '#')
        return 1;

    return 0; // linha não vazia nem comentário
}

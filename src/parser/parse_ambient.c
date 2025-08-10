/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 17:28:27 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int parse_ambient(const char *line, t_scene *scene)
{
    char **tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
        print_error("Ambient: número inválido de parâmetros", tokens);

    if (ft_strncmp(tokens[0], "A", 2) != 0)
        print_error("Ambient: esperado identificador 'A'", tokens);

    scene->ambient.intensity = ft_atof(tokens[1]);
    if (scene->ambient.intensity < 0 || scene->ambient.intensity > 1)
        print_error("Luz ambiente: intensidade deve estar entre 0 e 1", tokens);
    
    scene->ambient.color = parse_color(tokens[2]);

    ft_free_split(tokens);
    return 0;
}

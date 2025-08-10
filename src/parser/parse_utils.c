/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:31:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 parse_vec3(char *str)
{
   t_vec3 vec;
   char **tokens;

    tokens = ft_split(str, ',');
    if(!tokens)
        print_error("Failed to split vector string", NULL);
    if(!tokens[0] || !tokens[1] || !tokens[2])
    {
        if (count_tokens(tokens) != 3)
            print_error("Invalid vector format, expected 3 components", tokens);
    }
    vec.x = parse_float(tokens[0]);
    vec.y = parse_float(tokens[1]);
    vec.z = parse_float(tokens[2]);
    
    ft_free_split(tokens);
    return (vec);
}t_color parse_color(char *str)
{
    t_color color;
    char **tokens;

    tokens = ft_split(str, ',');
    if (!tokens)
        print_error("Failed to split color string", NULL);

    if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
        print_error("Invalid color format, expected 3 components", tokens);

    // Converter para float (pode ser int, mas convertendo pra float direto)
    float r = atof(tokens[0]);
    float g = atof(tokens[1]);
    float b = atof(tokens[2]);

    // Detectar se está no intervalo [0..1] ou [0..255]
    if (r <= 1.0f && g <= 1.0f && b <= 1.0f) {
        // Já está normalizado
        color = make_color(r, g, b);
    } else {
        // Está no intervalo 0..255, normaliza
        check_range((int)r, 0, 255, "Color component out of range (0-255)", tokens);
        check_range((int)g, 0, 255, "Color component out of range (0-255)", tokens);
        check_range((int)b, 0, 255, "Color component out of range (0-255)", tokens);
        color = make_color(r / 255.0f, g / 255.0f, b / 255.0f);
    }

    ft_free_split(tokens);
    return color;
}


float parse_float(char *str)
{
    float value;

    if (!str || !*str)
        print_error("Invalid float string", NULL);
    value = ft_atof(str);
    return (value);
}


void ft_free_split(char **tokens)
{
    int i;

    if (!tokens)
        return;

    i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }

    free(tokens);
}

int	count_tokens(char **tokens)
{
	int i = 0;
	while (tokens[i])
		i++;
	return i;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:26:52 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	ft_atod(const char *nptr)
{
	int	i;
	double	num;
	int	minus;
    double divisor;
    
	i = 0;
	num = 0.0;
	minus = 1;
    divisor = 10.0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		minus = minus * -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		num = num * 10.0 + (nptr[i] - '0');
		i++;
	}
    if(nptr[i] == '.')
    {
        i++;
        while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
        {
            num += (nptr[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }
	num = num * minus;
	return (num);
}

void free_split(char **tokens)
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

int parse_ambient(const char *line, t_world *world)
{
    char **tokens;

    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
    {
        print_error("Ambient: invalid number of parameters");
        free_split(tokens);
        return -1;
    }

    if (ft_strncmp(tokens[0], "A", 2) != 0)
    {
        print_error("Ambient: expected identifier 'A'");
        free_split(tokens);
        return -1;
    }

    world->ambient_light.ratio = ft_atod(tokens[1]);
    if (world->ambient_light.ratio < 0 || world->ambient_light.ratio > 1)
    {
        print_error("Ambient light: ratio must be between 0 and 1");
        free_split(tokens);
        return -1;
    }

    if (!parse_color(tokens[2], &world->ambient_light.color))
    {
        print_error("Ambient light: invalid color format");
        free_split(tokens);
        return -1;
    }

    free_split(tokens);
    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:04:37 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 20:50:09 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	parse_rgb_component(char *rgb_str, int *i, char *component_str)
{
	int	j;

	j = 0;
	while (rgb_str[*i] && rgb_str[*i] != ',' && rgb_str[*i] != '\0')
	{
		if (j >= 31)
			return (0);
		component_str[j++] = rgb_str[(*i)++];
	}
	component_str[j] = '\0';
	return (1);
}

int	validate_and_parse_rgb(char *rgb_str, t_rgb *out_rgb)
{
	char	components[3][32];
	float	values[3];
	int		i;

	if (!rgb_str || !out_rgb)
		return (0);
	i = 0;
	if (!parse_rgb_component(rgb_str, &i, components[0]) || rgb_str[i++] != ',')
		return (0);
	if (!parse_rgb_component(rgb_str, &i, components[1]) || rgb_str[i++] != ',')
		return (0);
	if (!parse_rgb_component(rgb_str, &i, components[2]) || rgb_str[i] != '\0')
		return (0);
	values[0] = parse_float(components[0]);
	values[1] = parse_float(components[1]);
	values[2] = parse_float(components[2]);
	if (values[0] < 0 || values[0] > 255 || values[1] < 0 || values[1] > 255
		|| values[2] < 0 || values[2] > 255)
		return (0);
	*out_rgb = new_rgb(values[0] / 255.0, values[1] / 255.0, values[2] / 255.0);
	return (1);
}

t_rgb	parse_rgb(char *rgb_str)
{
	t_rgb	result;

	if (!validate_and_parse_rgb(rgb_str, &result))
		return (new_rgb(0, 0, 0));
	return (result);
}

static t_tuple	handle_tuple_parse_error(int is_point)
{
	if (is_point)
		return (point(0, 0, 0));
	return (vector(0, 0, 0));
}

t_tuple	parse_tuple(char *tuple_str, int is_point)
{
	char	components[3][32];
	float	values[3];
	int		i;

	i = 0;
	if (!parse_rgb_component(tuple_str, &i, components[0])
		|| tuple_str[i++] != ',')
		return (handle_tuple_parse_error(is_point));
	if (!parse_rgb_component(tuple_str, &i, components[1])
		|| tuple_str[i++] != ',')
		return (handle_tuple_parse_error(is_point));
	if (!parse_rgb_component(tuple_str, &i, components[2]))
		return (handle_tuple_parse_error(is_point));
	values[0] = parse_float(components[0]);
	values[1] = parse_float(components[1]);
	values[2] = parse_float(components[2]);
	if (is_point)
		return (point(values[0], values[1], values[2]));
	return (vector(values[0], values[1], values[2]));
}

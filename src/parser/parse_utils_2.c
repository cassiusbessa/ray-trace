/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:04:37 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 19:04:37 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int validate_and_parse_rgb(char *rgb_str, t_rgb *out_rgb)
{
	char r_str[32], g_str[32], b_str[32];
	float r, g, b;
	int i, j;

	if (!rgb_str || !out_rgb)
		return 0;

	i = 0;
	j = 0;
	while (rgb_str[i] && rgb_str[i] != ',')
	{
		if (j >= 31)
			return 0;
		r_str[j++] = rgb_str[i++];
	}
	r_str[j] = '\0';
	if (rgb_str[i++] != ',')
		return 0;

	j = 0;
	while (rgb_str[i] && rgb_str[i] != ',')
	{
		if (j >= 31)
			return 0;
		g_str[j++] = rgb_str[i++];
	}
	g_str[j] = '\0';
	if (rgb_str[i++] != ',')
		return 0;

	j = 0;
	while (rgb_str[i] && rgb_str[i] != '\0')
	{
		if (j >= 31)
			return 0;
		b_str[j++] = rgb_str[i++];
	}
	b_str[j] = '\0';
	if (rgb_str[i] != '\0')
		return 0;

	r = parse_float(r_str);
	g = parse_float(g_str);
	b = parse_float(b_str);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return 0;

	*out_rgb = new_rgb(r / 255.0, g / 255.0, b / 255.0);
	return 1;
}

t_rgb parse_rgb(char *rgb_str)
{
	t_rgb result;

	if (!validate_and_parse_rgb(rgb_str, &result))
		return new_rgb(0, 0, 0);

	return result;
}

t_tuple parse_tuple(char *tuple_str, int is_point)
{
	char x_str[32], y_str[32], z_str[32];
	float x, y, z;
	int i, j;

	i = 0;
	j = 0;
	while (tuple_str[i] && tuple_str[i] != ',')
		x_str[j++] = tuple_str[i++];
	x_str[j] = '\0';
	if (tuple_str[i++] != ',')
		return is_point ? point(0, 0, 0) : vector(0, 0, 0);

	j = 0;
	while (tuple_str[i] && tuple_str[i] != ',')
		y_str[j++] = tuple_str[i++];
	y_str[j] = '\0';
	if (tuple_str[i++] != ',')
		return is_point ? point(0, 0, 0) : vector(0, 0, 0);

	j = 0;
	while (tuple_str[i] && tuple_str[i] != '\0')
		z_str[j++] = tuple_str[i++];
	z_str[j] = '\0';

	x = parse_float(x_str);
	y = parse_float(y_str);
	z = parse_float(z_str);

	return is_point ? point(x, y, z) : vector(x, y, z);
}
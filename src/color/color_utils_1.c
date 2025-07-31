/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 15:11:04 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	color(float r, float g, float b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	add_color(t_color c1, t_color c2)
{
	t_color    color;

    color.r = c1.r + c2.r;
    color.g = c1.g + c2.g;

    return (color);
}

t_color	subtract_color(t_color c1, t_color c2)
{
	t_color    color;

    color.r = c1.r - c2.r;
    color.g = c1.g - c2.g;
    color.b = c1.b - c2.b;

    return (color);
}
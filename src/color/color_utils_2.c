/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/31 15:16:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_color	multiply_color_scalar(t_color c, float scalar)
{
	t_color    color;

    if (scalar < 0)
    {
        printf("❌ ERROR: Scalar value cannot be negative for color multiplication.\n");
        return color(0, 0, 0);
    }
    color.r = c.r * scalar;
    color.g = c.g * scalar;
    color.b = c.b * scalar;

    return (color);
}

t_color	multiply_color(t_color c1, t_color c2)
{
	t_color color;

    color.r = c1.r * c2.r;
    color.g = c1.g * c2.g;
    color.b = c1.b * c2.b;

    return (color);
}

int	color_equal(t_color c1, t_color c2)
{
	int r_equal;
	int g_equal;
	int b_equal;

	r_equal = fabs(c1.r - c2.r) < EPSILON;
	g_equal = fabs(c1.g - c2.g) < EPSILON;
	b_equal = fabs(c1.b - c2.b) < EPSILON;

	return (r_equal && g_equal && b_equal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 17:44:40 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color add_colors(t_color c1, t_color c2)
{
    t_color result;
    float r, g, b;

    r = c1.r + c2.r;
    g = c1.g + c2.g;
    b = c1.b + c2.b;

    if(r > 1.0f)
        r = 1.0f;

    if(g > 1.0f)
        g = 1.0f;

    if(b > 1.0f)
        b = 1.0f;

    result.r = r;
    result.g = g;
    result.b = b;

    return (result);
}

static int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int color_to_int(t_color c)
{
    int r;
    int g;
    int b;
    int rgb;

    if(is_in_range(c.r, 0.0f, 1.0f))
        r = (int)(c.r * 255);
    else
    r = (int)c.r;
    if(is_in_range(c.g, 0.0f, 1.0f))
        g = (int)(c.g * 255);
    else
        g = (int)c.g;
    if(is_in_range(c.b, 0.0f, 1.0f))
        b = (int)(c.b * 255);
    else
        b = (int)c.b;

    r = clamp(r, 0, 255);
    g = clamp(g, 0, 255);
    b = clamp(b, 0, 255);

    rgb = (r << 16) | (g << 8) | b;

	return (rgb);
}

t_color make_color(float r, float g, float b)
{
    t_color c;

    c.r = r;
    c.g = g;
    c.b = b;

    return (c);
}

t_color clamp_color(t_color c)
{
    if (c.r < 0.0f) c.r = 0.0f;
    else if (c.r > 1.0f) c.r = 1.0f;

    if (c.g < 0.0f) c.g = 0.0f;
    else if (c.g > 1.0f) c.g = 1.0f;

    if (c.b < 0.0f) c.b = 0.0f;
    else if (c.b > 1.0f) c.b = 1.0f;

    return c;
}

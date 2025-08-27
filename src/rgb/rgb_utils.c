/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:54:58 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 19:27:48 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int equal_rgb(t_rgb c1, t_rgb c2)
{
    float eps = 0.0001f;  // tolerância
    return (fabsf(c1.r - c2.r) < eps &&
            fabsf(c1.g - c2.g) < eps &&
            fabsf(c1.b - c2.b) < eps);
}



t_rgb	clamp_color(t_rgb c)
{
	c.r = fmin(fmax(c.r, 0), 1);
	c.g = fmin(fmax(c.g, 0), 1);
	c.b = fmin(fmax(c.b, 0), 1);
	return (c);
}

void print_rgb(t_rgb c)
{
	printf("RGB(%f, %f, %f)\n", c.r, c.g, c.b);
}
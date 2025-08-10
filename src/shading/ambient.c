/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:26 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color apply_ambient_light(t_ambient_light *ambient, t_color obj_color)
{
	t_color result;

	result = make_color(
        ambient->intensity * ambient->color.r * obj_color.r,
        ambient->intensity * ambient->color.g * obj_color.g,
        ambient->intensity * ambient->color.b * obj_color.b);

	return (result);
}
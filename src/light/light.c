/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:32:40 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 18:33:59 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_point_light	new_point_light(t_tuple position, t_rgb intensity)
{
	t_point_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}
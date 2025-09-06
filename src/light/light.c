/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:32:40 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:27:32 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_point_light	new_point_light(t_tuple position, t_rgb intensity)
{
	t_point_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

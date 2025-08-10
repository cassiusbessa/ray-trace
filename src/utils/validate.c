/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 08:44:31 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_range(float value, float min, float max, char *msg, char **to_free)
{
	if (value < min || value > max)
		print_error(msg, to_free);
}

int	is_in_range(float value, float min, float max)
{
	if (value < min || value > max)
        return (0);

    return (1);
}

t_material default_material(void)
{
	t_material m;
	m.base_color = make_color(1.0f, 1.0f, 1.0f);
	m.specular_coef = 0.2f;
	m.shininess = 32.0f;
	m.reflectivity = 0.0f;
	m.transparency = 0.0f;
	return (m);
}
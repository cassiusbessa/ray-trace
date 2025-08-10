/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 18:33:13 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	ft_atof(const char *nptr)
{
	int		i;
	float	num;
	int		sign;
	float	divisor;

	i = 0;
	num = 0.0f;
	sign = 1;
	divisor = 10.0f;


	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;

	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;

	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		num = num * 10.0f + (nptr[i] - '0');
		i++;
	}

	if (nptr[i] == '.')
	{
		i++;
		while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
		{
			num += (nptr[i] - '0') / divisor;
			divisor *= 10.0f;
			i++;
		}
	}

	return (num * sign);
}

void add_object_to_scene(t_scene *scene, t_object *obj)
{
    if (!scene || !obj)
        return;

    obj->next = scene->objects;
    scene->objects = obj;
}


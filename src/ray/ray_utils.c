/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/15 10:43:39 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	equal_rays(t_ray r1, t_ray r2)
{
	return (equal_tuples(r1.origin, r2.origin) && equal_tuples(r1.direction,
			r2.direction));
}

t_ray	transform_ray(t_ray r, t_matrix m)
{
	t_tuple	new_origin;
	t_tuple	new_direction;
	t_ray	result;

	new_origin = matrix_multiply_by_tuple(m, r.origin);
	new_direction = matrix_multiply_by_tuple(m, r.direction);
	result = create_ray(new_origin, new_direction);
	return (result);
}

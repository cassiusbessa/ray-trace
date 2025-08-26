/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/26 20:37:46 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	equal_rays(t_ray r1, t_ray r2)
{
	return (equal_tuples(r1.origin, r2.origin) && equal_tuples(r1.direction,
			r2.direction));
}


// ====================== transform_ray segura ======================
t_ray transform_ray(t_ray r, t_matrix m, int *success)
{
    t_ray result;
    t_tuple new_origin, new_direction;

    new_origin = matrix_multiply_by_tuple(m, r.origin);

    t_tuple dir = r.direction;
    dir.w = 0;
    new_direction = matrix_multiply_by_tuple(m, dir);

    if (fabs(new_direction.x) < 1e-6 &&
        fabs(new_direction.y) < 1e-6 &&
        fabs(new_direction.z) < 1e-6)
    {
        *success = 0;
    }
    else
    {
        *success = 1;
    }

    result = create_ray(new_origin, new_direction);
    return result;
}


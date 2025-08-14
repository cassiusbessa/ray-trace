/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 18:03:28 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int equal_rays(t_ray r1, t_ray r2)
{
    return equal_tuples(r1.origin, r2.origin) &&
           equal_tuples(r1.direction, r2.direction);
}
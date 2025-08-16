/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:46:50 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 20:51:59 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_tuple normal_at_sphere(t_sphere s, t_tuple p)
{
    t_tuple normal;

    normal = sub_tuples(p, s.center);
    normal.w = 0;
    return (normalize_vector(normal));
}

t_tuple	normal_at(t_object o, t_tuple p)
{
    t_tuple	normal;

    if (o.type == SPHERE)
        normal = normal_at_sphere(*((t_sphere *)o.data), p);

    return (normal);
}


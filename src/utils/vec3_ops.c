/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 09:39:59 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3(double x, double y, double z)
{
    t_vec3 result;
    
    result.x = x;
    result.y = y;
    result.z = z;

    return (result);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return (result);
}
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    
    return (result);
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
    double result;

    result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

    return (result);
}

t_vec3	vec3_scale(t_vec3 v, double s)
{
    t_vec3 result;

    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;

    return (result);
}

t_vec3 vec3_neg(t_vec3 v)
{
    return vec3_scale(v, -1.0);
}

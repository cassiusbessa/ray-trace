/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 14:46:15 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color apply_diffuse_light(t_point_light *light, t_vec3 point, t_vec3 normal, t_color obj_color, float visibility)
{
    t_vec3 light_dir;
    float dot;
    t_color result;

    light_dir = vec3_sub(light->position, point);
    light_dir = vec3_normalize(light_dir);

    dot = vec3_dot(normal, light_dir);

    if (dot < 0)
        dot = 0;

    dot *= visibility;

    result = make_color(
        dot * light->brightness * light->color.r * obj_color.r,
        dot * light->brightness * light->color.g * obj_color.g,
        dot * light->brightness * light->color.b * obj_color.b);

    return result;
}

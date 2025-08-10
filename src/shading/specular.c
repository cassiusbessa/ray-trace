/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 08:56:47 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
t_color calculate_specular(t_vec3 point, t_vec3 normal, t_vec3 light_pos, t_vec3 view_pos,
    t_color light_color, float brightness,
    float specular_coef, float shininess)
{
    t_vec3 light_dir = vec3_normalize(vec3_sub(light_pos, point));
    t_vec3 view_dir = vec3_normalize(vec3_sub(view_pos, point));
    t_vec3 reflect_dir = vec3_normalize(vec3_reflect(vec3_scale(light_dir, -1), normal));

    float spec_angle = fmax(vec3_dot(view_dir, reflect_dir), 0.0f);
    float spec = powf(spec_angle, shininess);
    float intensity = brightness * specular_coef * spec;

    return make_color(light_color.r * intensity,
                      light_color.g * intensity,
                      light_color.b * intensity);
}

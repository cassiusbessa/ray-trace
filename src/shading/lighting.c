/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:26:21 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifndef DEBUG_LIGHTING
#define DEBUG_LIGHTING 0  // muda pra 1 para debug detalhado na iluminação
#endif

t_color calculate_lighting(t_scene *scene, t_vec3 point, t_vec3 normal, t_vec3 view_pos, t_color base, t_object *obj)
{
    t_color result = apply_ambient_light(&scene->ambient, base);
#if DEBUG_LIGHTING
    printf("[DEBUG lighting] Ambient light aplicada: (%.3f, %.3f, %.3f)\n", result.r, result.g, result.b);
#endif

    for (int i = 0; i < scene->n_point_lights; i++)
    {
        t_point_light *light = &scene->point_lights[i];
        t_vec3 light_pos = light->position;

        if (!in_shadow(scene, point, light_pos))
        {
            t_color diffuse = apply_diffuse_light(light, point, normal, base, 1.0f);
            t_color specular = (obj->material.specular_coef > 0.0f)
                ? calculate_specular(point, normal, light_pos, view_pos, light->color, light->brightness,
                                      obj->material.specular_coef, obj->material.shininess)
                : make_color(0, 0, 0);

#if DEBUG_LIGHTING
            printf("[DEBUG lighting] Luz %d:\n", i);
            printf("    Difusa: (%.3f, %.3f, %.3f)\n", diffuse.r, diffuse.g, diffuse.b);
            printf("    Especular: (%.3f, %.3f, %.3f)\n", specular.r, specular.g, specular.b);
#endif

            result = add_colors(result, add_colors(diffuse, specular));

#if DEBUG_LIGHTING
            printf("    Resultado parcial: (%.3f, %.3f, %.3f)\n", result.r, result.g, result.b);
#endif
        }
        else
        {
#if DEBUG_LIGHTING
            printf("[DEBUG lighting] Luz %d está em sombra para o ponto\n", i);
#endif
        }
    }
    t_color final = clamp_color(result);
#if DEBUG_LIGHTING
    printf("[DEBUG lighting] Resultado final após clamp: (%.3f, %.3f, %.3f)\n", final.r, final.g, final.b);
#endif
    return final;
}

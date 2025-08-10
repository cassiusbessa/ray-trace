/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:06:35 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ray_new(t_vec3 orig, t_vec3 dir)
{
    t_ray raio;

    raio.origin = orig;
    raio.dir = vec3_normalize(dir);

    return (raio);
}

t_vec3	ray_at(t_ray r, double t)
{
    t_vec3 offset;
    t_vec3 point; 

    offset = vec3_scale(r.dir, t);  // Direção multiplicada pelo parâmetro t
    point = vec3_add(r.origin, offset);

    return (point);
}


int scene_intersect(t_scene *scene, t_ray ray, t_hit *hit)
{
    int hit_anything = 0;
    double closest_t = INF;
    t_intersection temp_hit;

    for (int i = 0; i < scene->num_objects; i++)
    {
        t_object *obj = &scene->objects[i];

        if (intersect_object(&ray, obj, &temp_hit))
        {
            if (temp_hit.t < closest_t && temp_hit.t > EPS)
            {
                closest_t = temp_hit.t;

                // Copia dados que existem em t_hit
                hit->t = temp_hit.t;
                hit->point = temp_hit.point;
                hit->normal = temp_hit.normal;
                hit->object = temp_hit.object;  // importante para acessar o material depois!

                hit_anything = 1;
            }
        }
    }

    return hit_anything;
}




t_color trace_ray(t_scene *scene, t_ray ray, int depth)
{
    if (depth > MAX_RECURSION_DEPTH)
        return make_color(0, 0, 0); // cor preta

    t_hit hit;
    if (!scene_intersect(scene, ray, &hit))
        return scene->background_color;

    t_object *obj = hit.object;
    t_material mat = obj->material;

    // Cor local na interseção
    t_color local_color = calculate_lighting(scene, hit.point, hit.normal, vec3_neg(ray.dir), mat.base_color, obj);

    // Se transparente, calcular refração
    if (mat.transparency > 0.0f)
    {
        t_vec3 refract_dir;
        if (vec3_refract(ray.dir, hit.normal, mat.ior, &refract_dir))
        {
            t_ray refract_ray = ray_new(hit.point, refract_dir);
            t_color refracted_color = trace_ray(scene, refract_ray, depth + 1);

            // Misturar cor local e refratada pela transparência
            local_color = add_colors(
                vec3_scale_color(local_color, 1.0f - mat.transparency),
                vec3_scale_color(refracted_color, mat.transparency)
            );
        }
        else
        {
            // Reflexão total interna: pode tratar como reflexão simples ou ignorar
            // Por enquanto, retorna cor local
        }
    }

    return clamp_color(local_color);
}

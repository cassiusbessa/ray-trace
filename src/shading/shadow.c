/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/08 14:01:07 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray create_shadow_ray(t_vec3 point, t_vec3 light_pos)
{
	t_ray raio;
    
    t_vec3 dir;
    t_vec3 origin;
    
    dir = vec3_normalize(vec3_sub(light_pos, point));
	origin = vec3_add(point, vec3_scale(dir, EPS));
    raio = ray_new(origin, dir);

    return (raio);
}

int in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_pos)
{
	t_ray shadow_ray; 
	double max_dist; 
	t_intersection hit;
	t_object *cur;


    shadow_ray = create_shadow_ray(point, light_pos);
	max_dist = vec3_length(vec3_sub(light_pos, point));
    cur = scene->objects;
	while (cur)
	{
		if (intersect_object(&shadow_ray, cur, &hit))
			if (hit.t > EPS && hit.t < max_dist)
				return (1);
		cur = cur->next;
	}
	return (0);
}

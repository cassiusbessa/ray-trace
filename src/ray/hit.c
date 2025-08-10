/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 20:27:11 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3 compute_hit_point(t_ray *ray, double t)
{
    t_vec3 point;

    point = ray_at(*ray, t);
    return (point);
}

static t_vec3 compute_normal_sphere_plane(t_object *obj, t_vec3 point)
{
    t_sphere *s;
    t_plane *p;
    t_vec3 tmp;

    if (obj->type == SPHERE)
    {
        s = (t_sphere *)obj->shape;
        tmp = vec3_sub(point, s->center);
        return (vec3_normalize(tmp));
    }
    if (obj->type == PLANE)
    {
        p = (t_plane *)obj->shape;
        return (vec3_normalize(p->normal));
    }
    return (vec3(0, 0, 0)); // fallback
}

static t_vec3 compute_normal_cylinder(t_object *obj, t_vec3 point)
{
    t_cylinder *c;
    t_vec3 tmp;
    double proj;

    c = (t_cylinder *)obj->shape;
    tmp = vec3_sub(point, c->center);
    proj = vec3_dot(tmp, c->axis);
    tmp = vec3_sub(tmp, vec3_scale(c->axis, proj));
    return (vec3_normalize(tmp));
}

t_vec3 compute_normal(t_object *obj, t_vec3 point)
{
    if (obj->type == SPHERE || obj->type == PLANE)
        return compute_normal_sphere_plane(obj, point);
    if (obj->type == CYLINDER)
        return compute_normal_cylinder(obj, point);
    return (vec3(0, 0, 0));
}


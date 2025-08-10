/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 20:19:04 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Ray-plane:
 *    t = dot(P0 - O, n) / dot(D, n)
 * onde P0 é um ponto no plano, n a normal (normalizada).
 */

int intersect_plane(t_ray *ray, t_object *obj, t_intersection *out)
{
    t_plane *p;
    double denom;
    double num;
    double t;

    p = (t_plane *)obj->shape;

    denom = vec3_dot(ray->dir, p->normal);
    if (fabs(denom) < EPS)
        return (0); /* raio paralelo ao plano, sem interseção */

    num = vec3_dot(vec3_sub(p->point, ray->origin), p->normal);
    t = num / denom;

    if (t <= EPS)
        return (0); /* interseção atrás da origem do raio ou muito perto */

    out->t = t;
    out->object = obj;

    return (1); /* interseção válida */
}

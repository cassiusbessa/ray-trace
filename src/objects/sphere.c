/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 09:47:52 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * Algoritmo:
 *   Solve: ||O + tD - C||^2 = R^2
 *   => at^2 + bt + c = 0
 *   a = dot(D,D)
 *   b = 2*dot(oc,D)
 *   c = dot(oc,oc) - R^2
 */


static int solve_quadratic(double a, double b, double c, double *t)
 {
     double discriminant;
     double sqrt_disc;
     double t0, t1;
 
     discriminant = b * b - 4 * a * c;
     if (discriminant < 0.0)
         return 0;
 
     sqrt_disc = sqrt(discriminant);
     t0 = (-b - sqrt_disc) / (2.0 * a);
     t1 = (-b + sqrt_disc) / (2.0 * a);
 
     if (t0 > EPS)
         *t = t0;
     else if (t1 > EPS)
         *t = t1;
     else
         return 0;
 
     return 1;
 }
 
 int intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out)
 {
     t_sphere *s;
     t_vec3 oc;
     double a, b, c;
     double t;
 
     s = (t_sphere *)obj->shape;
     oc = vec3_sub(ray->origin, s->center);
 
     a = vec3_dot(ray->dir, ray->dir);
     b = 2.0 * vec3_dot(oc, ray->dir);
     c = vec3_dot(oc, oc) - s->radius * s->radius;
 
     if (!solve_quadratic(a, b, c, &t))
         return 0;
 
     out->t = t;
     out->object = obj;
 
     return 1;
 }
 
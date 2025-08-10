/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 20:23:37 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Calcula coeficientes da equação quadrática para cilindro infinito */
static void compute_cylinder_quadratic(t_ray *ray, t_cylinder *cy, double *a, double *b, double *c, t_vec3 *oc, double *dv)
{
    t_vec3 d_perp;
    double ocv;
    t_vec3 oc_perp;

    *oc = vec3_sub(ray->origin, cy->center);
    *dv = vec3_dot(ray->dir, cy->axis);

    d_perp = vec3_sub(ray->dir, vec3_scale(cy->axis, *dv));
    ocv = vec3_dot(*oc, cy->axis);
    oc_perp = vec3_sub(*oc, vec3_scale(cy->axis, ocv));

    *a = vec3_dot(d_perp, d_perp);
    *b = 2.0 * vec3_dot(d_perp, oc_perp);
    *c = vec3_dot(oc_perp, oc_perp) - cy->radius * cy->radius;
}

/* Resolve a equação quadrática e retorna o menor t positivo válido */
static int solve_quadratic(double a, double b, double c, double *t)
{
    double disc;
    double sq;
    double t0, t1;

    if (fabs(a) < EPS)
        return 0;

    disc = b * b - 4.0 * a * c;
    if (disc < 0.0)
        return 0;

    sq = sqrt(disc);
    t0 = (-b - sq) / (2.0 * a);
    t1 = (-b + sq) / (2.0 * a);

    *t = (t0 > EPS) ? t0 : ((t1 > EPS) ? t1 : -1.0);
    if (*t <= 0.0)
        return 0;

    return 1;
}

/* Verifica se o ponto da interseção está dentro da altura do cilindro */
static int check_cylinder_height(t_cylinder *cy, t_vec3 oc, double dv, double t)
{
    double proj;

    proj = vec3_dot(oc, cy->axis) + t * dv;

    if (proj < -cy->height * 0.5 || proj > cy->height * 0.5)
        return 0;

    return 1;
}

int intersect_cylinder(t_ray *ray, t_object *obj, t_intersection *out)
{
    t_cylinder *cy = (t_cylinder *)obj->shape;
    double a, b, c, t;
    t_vec3 oc;
    double dv;

    compute_cylinder_quadratic(ray, cy, &a, &b, &c, &oc, &dv);

    if (!solve_quadratic(a, b, c, &t))
        return 0;

    if (!check_cylinder_height(cy, oc, dv, t))
        return 0;

    out->t = t;
    out->object = obj;
    return 1;
}

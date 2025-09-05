/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:02:46 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 20:51:54 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_quad solve_quadratic_for_sphere(t_ray ray, t_sphere *sphere)
{
    t_tuple sphere_to_ray;
    float   a;
    float   b;
    float   c;
    t_quad result;

    (void)sphere;

    sphere_to_ray = sub_tuples(ray.origin, point(0, 0, 0));
    a = vector_dot_product(ray.direction, ray.direction);
    b = 2.0f * vector_dot_product(ray.direction, sphere_to_ray);
    c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1.0f;

    result = ft_quadratic(a, b, c);
    return (result);
}

t_quad solve_quadratic_for_cylinder(t_ray ray, float radius)
{
    float   a;
    float   b;
    float   c;
    t_quad result;

    a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    b = 2.0f * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
    c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - radius * radius;

    if (fabsf(a) < EPSILON)
    {
        result.count = 0;
        result.x1 = 0.0f;
        result.x2 = 0.0f;
        return (result);
    }

    result = ft_quadratic(a, b, c);
    return (result);
}

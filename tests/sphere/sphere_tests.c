/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:20:09 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 22:26:56 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_intersect_ray_sphere(void)
{
    int errors = 0;
    t_intersection intersection;
    t_intersection result;
    t_ray ray;
    t_sphere sphere;

    ray = create_ray(point(0, 0, -5), vector(0, 0 ,1));
    sphere = new_sphere(point(0, 0, 0), 1);
    intersection = intersect_ray_sphere(ray, sphere);
    result = new_intersection(2, 4.0, 6.0);
    errors += test_check(equal_intersections(intersection, result), "Ray should intersect sphere at two points");
    ray = create_ray(point(0, 1, -5), vector(0, 0 ,1));
    intersection = intersect_ray_sphere(ray, sphere);
    result = new_intersection(2, 5.0, 5.0);
    errors += test_check(equal_intersections(intersection, result), "Ray should intersect sphere at two points (tangential)");
    ray = create_ray(point(0, 2, -5), vector(0, 0 ,1));
    intersection = intersect_ray_sphere(ray, sphere);
    result = new_intersection(0, 0.0, 0.0);
    errors += test_check(equal_intersections(intersection, result), "Ray should not intersect sphere");
    ray = create_ray(point(0, 0, 0), vector(0, 0 , 1));
    intersection = intersect_ray_sphere(ray, sphere);
    result = new_intersection(2, -1.0, 1.0);
    errors += test_check(equal_intersections(intersection, result), "Ray should intersect sphere at two points(inside)");

    return errors;
}

int run_test_sphere(void)
{
    int errors = 0;
    errors += test_intersect_ray_sphere();
    if (errors)
        test_failure("Sphere intersection tests failed");
    else
        test_success("Sphere intersection tests passed");
    return errors;
}
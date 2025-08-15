/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:20:09 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 21:31:55 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_intersect_ray_sphere(void)
{
    int errors = 0;
    t_intersection intersection;
    t_intersection result;

    // Test case 1: Ray intersects sphere
    t_ray ray = create_ray(point(0, 0, -5), vector(0, 0 ,1));
    t_sphere sphere = new_sphere(point(0, 0, 0), 1);
    intersection = intersect_ray_sphere(ray, sphere);
    result = new_intersection(2, 4.0, 6.0);
    errors += test_check(equal_intersections(intersection, result), "Ray should intersect sphere at two points");
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
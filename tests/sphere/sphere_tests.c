/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:20:09 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 09:22:03 by emorshhe         ###   ########.fr       */
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

    // Cria esfera
    sphere = new_sphere((t_tuple){0, 0, 0, 1}, 1.0f);

    // Caso 1: Raio intersecta esfera em dois pontos
    ray = create_ray(point(0, 0, -5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &sphere);
    result = new_intersection(2, 4.0f, 6.0f, &sphere);
    errors += test_check(equal_intersections(intersection, result),
        "Ray should intersect sphere at two points");

    // Caso 2: Raio tangencia esfera
    ray = create_ray(point(0, 1, -5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &sphere);
    result = new_intersection(2, 5.0f, 5.0f, &sphere);
    errors += test_check(equal_intersections(intersection, result),
        "Ray should intersect sphere at two points (tangential)");

    // Caso 3: Raio perde a esfera
    ray = create_ray(point(0, 2, -5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &sphere);
    result = new_intersection(0, 0.0f, 0.0f, NULL);
    errors += test_check(equal_intersections(intersection, result),
        "Ray should not intersect sphere");

    // Caso 4: Raio começa dentro da esfera
    ray = create_ray(point(0, 0, 0), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &sphere);
    result = new_intersection(2, -1.0f, 1.0f, &sphere);
    errors += test_check(equal_intersections(intersection, result),
        "Ray should intersect sphere at two points (inside)");

    // Caso 5: Esfera está atrás do raio
    ray = create_ray(point(0, 0, 5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &sphere);
    result = new_intersection(2, -6.0f, -4.0f, &sphere);
    errors += test_check(equal_intersections(intersection, result),
        "Ray should intersect sphere at two points (behind)");

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

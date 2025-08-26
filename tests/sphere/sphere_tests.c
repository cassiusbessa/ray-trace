/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:20:09 by cassius           #+#    #+#             */
/*   Updated: 2025/08/25 20:49:46 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_intersect_ray_sphere(void)
{
    int errors = 0;
    t_intersection_list *intersection;
    t_ray ray;
    t_sphere sphere;
    t_object obj;

    // Inicializa esfera e objeto
    sphere = new_sphere(point(0, 0, 0), 1.0f);
    obj.type = SPHERE;
    obj.data = &sphere;

    // Caso 1: Raio atravessa a esfera
    ray = create_ray(point(0, 0, -5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &obj);
    errors += test_check(intersection->count == 2, "Ray should intersect sphere at two points");
    errors += test_check_double(intersection->head->t, 4.0f, "Ray should intersect sphere at two points (first intersection)");
    errors += test_check_double(intersection->head->next->t, 6.0f, "Ray should intersect sphere at two points (second intersection)");
    free_intersection_list(intersection);

    // Caso 2: Raio tangencia esfera
    ray = create_ray(point(0, 1, -5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &obj);
    errors += test_check(intersection->count == 2, "Ray should tangentially intersect sphere");
    errors += test_check_double(intersection->head->t, 5.0f, "Ray should tangentially intersect sphere");
    errors += test_check_double(intersection->head->next->t, 5.0f, "Ray should tangentially intersect sphere");
    free_intersection_list(intersection);

    // Caso 3: Raio perde a esfera
    ray = create_ray(point(0, 2, -5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &obj);
    errors += test_check(intersection->count == 0, "Ray should not intersect sphere");
    errors += test_check(intersection->head == NULL, "Ray should not intersect sphere (head is NULL)");
    free_intersection_list(intersection);

    // Caso 4: Raio começa dentro da esfera
    ray = create_ray(point(0, 0, 0), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &obj);
    errors += test_check(intersection->count == 2, "Ray should intersect sphere at two points (inside)");
    errors += test_check_double(intersection->head->t, -1.0f, "Ray should intersect sphere at two points (inside)");
    errors += test_check_double(intersection->head->next->t, 1.0f, "Ray should intersect sphere at two points (inside)");
    free_intersection_list(intersection);

    // Caso 5: Esfera está atrás do raio
    ray = create_ray(point(0, 0, 5), vector(0, 0, 1));
    intersection = intersect_ray_sphere(ray, &obj);
    errors += test_check(intersection->count == 2, "Ray should intersect sphere at two points (behind)");
    errors += test_check_double(intersection->head->t, -6.0f, "Ray should intersect sphere at two points (behind - first intersection)");
    errors += test_check_double(intersection->head->next->t, -4.0f, "Ray should intersect sphere at two points (behind - second intersection)");
    free_intersection_list(intersection);

    return errors;
}


static int test_default_material_sphere(void)
{
    int errors = 0;
    t_sphere sphere;
    t_material default_material;

    sphere = new_sphere(point(0, 0, 0), 1.0f);
    default_material = new_material_default();
    errors += test_check(equal_materials(sphere.material, default_material),
        "Sphere should have default material");

    if (errors)
        test_failure("Sphere default material test failed");
    else
        test_success("Sphere default material test passed");
    return errors;
}

static int  test_assign_material_sphere(void)
{
    int errors = 0;
    t_sphere sphere;
    t_material new_material;

    sphere = new_sphere(point(0, 0, 0), 1.0f);
    new_material = new_material_default();
    new_material.color = new_rgb(0.5f, 0.5f, 0.5f);
    sphere.material = new_material;
    errors += test_check(equal_materials(sphere.material, new_material),
        "Sphere material should be assigned correctly");

    if (errors)
        test_failure("Sphere assign material test failed");
    else
        test_success("Sphere assign material test passed");
    return errors;
}


int run_test_sphere(void)
{
    int errors = 0;
    errors += test_intersect_ray_sphere();
    errors += test_default_material_sphere();
    errors += test_assign_material_sphere();
    if (errors)
        test_failure("Sphere tests failed");
    else
        test_success("Sphere tests passed");
    return errors;
}

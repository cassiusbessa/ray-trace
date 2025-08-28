/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:55:14 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 21:52:07 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"


static int test_camera_creation(void)
{
    int errors = 0;
    t_camera cam = new_camera(160, 120, M_PI/2);

    errors += test_check(cam.hsize == 160, "Camera hsize should be 160");
    errors += test_check(cam.vsize == 120, "Camera vsize should be 120");
    errors += test_check_double(cam.field_of_view, M_PI/2, "Camera FOV should be M_PI/2");
    errors += test_check(equal_matrix(cam.transform, identity_matrix(4)), "Camera transform should be identity");

    if (errors)
        test_failure("Camera creation test failed");

    return errors;
}

static int test_camera_pixel_size(void)
{
    int errors = 0;
    t_camera cam1 = new_camera(200, 125, M_PI/2);
    t_camera cam2 = new_camera(125, 200, M_PI/2);

    errors += test_check_double(cam1.pixel_size, 0.01, "Camera 1 pixel size should be 0.01");
    errors += test_check_double(cam2.pixel_size, 0.01, "Camera 2 pixel size should be 0.01");

    if (errors)
        test_failure("Camera pixel size test failed");

    return errors;
}

static int test_ray_for_pixel_center(void)
{
    int errors = 0;
    t_camera cam = new_camera(201, 101, M_PI/2);
    t_ray r = ray_for_pixel(cam, 100, 50); // você precisa implementar ray_for_pixel

    errors += test_check(equal_tuples(r.origin, point(0, 0, 0)), "Ray origin through center should be (0,0,0)");
    errors += test_check(equal_tuples(r.direction, vector(0, 0, -1)), "Ray direction through center should be (0,0,-1)");

    if (errors)
        test_failure("Ray through center test failed");
    else
        test_success("Ray through center test passed");

    return errors;
}

static int test_ray_for_pixel_corner(void)
{
    int errors = 0;
    t_camera cam = new_camera(201, 101, M_PI/2);
    t_ray r = ray_for_pixel(cam, 0, 0); 

    errors += test_check(equal_tuples(r.origin, point(0, 0, 0)), "Ray origin through corner should be (0,0,0)");
    errors += test_check(equal_tuples(r.direction, vector(0.66519, 0.33259, -0.66851)), "Ray direction through corner should match expected");

    if (errors)
        test_failure("Ray through corner test failed");
    else
        test_success("Ray through corner test passed");

    return errors;
}

static int test_ray_transformed_camera(void)
{
    int errors = 0;
    t_camera cam = new_camera(201, 101, M_PI/2);
    cam.transform = matrix_multiply_by_matrix(rotation_y_matrix(M_PI/4), translation_matrix(0, -2, 5));
    t_ray r = ray_for_pixel(cam, 100, 50); 

    errors += test_check(equal_tuples(r.origin, point(0, 2, -5)), "Ray origin with transformed camera should be (0,2,-5)");
    errors += test_check(equal_tuples(r.direction, vector(M_SQRT2/2, 0, -M_SQRT2/2)), "Ray direction with transformed camera should match expected");

    if (errors)
        test_failure("Ray transformed camera test failed");
    else
        test_success("Ray transformed camera test passed");

    return errors;
}

int run_camera_tests(void)
{
    int errors = 0;

    errors += test_camera_creation();
    errors += test_camera_pixel_size();
    errors += test_ray_for_pixel_center();
    errors += test_ray_for_pixel_corner();
    errors += test_ray_transformed_camera();

    if (errors)
        test_failure("Camera tests failed");
    else
        test_success("Camera tests passed");

    return errors;
}

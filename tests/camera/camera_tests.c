/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:55:14 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 21:13:23 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_camera_creation(void)
{
    int errors = 0;
    t_camera cam = new_camera(160, 120, M_PI/2);

    test_check(cam.hsize == 160, "Camera hsize should be 160");
    test_check(cam.vsize == 120, "Camera vsize should be 120");
    test_check_double(cam.field_of_view, M_PI/2, "Camera FOV should be M_PI/2");
    test_check(equal_matrix(cam.transform, identity_matrix(4)), "Camera transform should be identity");

    if (errors)
        test_failure("Camera creation test failed with %d errors\n");
    else
        test_success("Camera creation test passed\n");
    return (errors);
}

static int  test_camera_pixel_size(void)
{
    int errors = 0;
    t_camera cam1 = new_camera(200, 125, M_PI/2);
    t_camera cam2 = new_camera(125, 200, M_PI/2);
    errors += test_check_double(cam1.pixel_size, 0.01, "Camera 1 pixel size should be 0.01");
    errors += test_check_double(cam2.pixel_size, 0.01, "Camera 2 pixel size should be 0.01");
    if (errors)
        test_failure("Camera pixel size test failed with errors\n");
    else
        test_success("Camera pixel size test passed\n");
    return (errors);
}



int run_camera_tests(void)
{
    int errors = 0;

    errors += test_camera_creation();
    errors += test_camera_pixel_size();
    if (errors)
        test_failure("Camera tests failed\n");
    else
        test_success("Camera tests passed\n");

    return (errors);
}


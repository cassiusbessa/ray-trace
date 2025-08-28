/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:55:14 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 21:02:18 by cassius          ###   ########.fr       */
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

int run_camera_tests(void)
{
    int errors = 0;

    errors += test_camera_creation();
    if (errors)
        test_failure("Camera tests failed with %d errors\n");
    else
        test_success("Camera tests passed\n");

    return (errors);
}


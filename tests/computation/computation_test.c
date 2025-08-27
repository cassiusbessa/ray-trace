/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:00:07 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 22:34:47 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_prepare_computations(void)
{
    int errors = 0;

    t_ray r = create_ray(point(0, 0, 0), vector(0, 0, 1));
    t_object shape;
    shape.type = SPHERE;
    t_sphere sphere_data = new_sphere(point(0, 0, 0), 1.0f);
    shape.data = &sphere_data;
    t_intersection_node i = {.t = 1.0, .object = &shape, .next = NULL};
    t_comps comps = prepare_computations(i, r);
    errors += test_check(float_equal(comps.t, i.t), "Expected t = 4.0");
    errors += test_check(comps.object == &shape, "Expected object to be shape");
    errors += test_check(equal_tuples(comps.point, point(0, 0, 1)), "Expected point = (0, 0, 1)");
    errors += test_check(equal_tuples(comps.eyev, vector(0, 0, -1)), "Expected eyev = (0, 0, -1)");
    errors += test_check(equal_tuples(comps.normalv, vector(0, 0, -1)), "Expected normalv = (0, 0, -1)");
    errors += test_check(comps.inside == 1, "Expected inside = 1");

    if (errors)
        test_failure("Prepare computations test failed\n");
    else
        test_success("Prepare computations test passed\n");
    return errors;
}

int run_computation_tests(void)
{
    int errors = 0;

    errors += test_prepare_computations();
    
    if (errors)
        test_failure("Computation tests failed with errors\n");
    else
        test_success("Computation tests passed\n");

    return errors;
}
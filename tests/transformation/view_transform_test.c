/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:05:12 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/27 19:53:40 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_view_transform_default_orientation(void)
{
    int errors = 0;

    t_tuple from = point(0, 0, 0);
    t_tuple to = point(0, 0, -1);
    t_tuple up = vector(0, 1, 0);

    t_matrix t = view_transform(from, to, up);
    t_matrix id = identity_matrix(4);

    errors += test_check(equal_matrix(t, id),
                         "Default view transform should be identity");

    if (errors)
        test_failure("View transform default orientation test failed\n");


    free_matrix(t);
    free_matrix(id);
    return errors;
}

static int test_view_transform_positive_z_direction(void)
{
    int errors = 0;

    t_tuple from = point(0, 0, 0);
    t_tuple to = point(0, 0, 1);
    t_tuple up = vector(0, 1, 0);

    t_matrix t = view_transform(from, to, up);
    t_matrix expected = scaling_matrix(-1, 1, -1);

    errors += test_check(equal_matrix(t, expected),
                         "View transform looking in +z should scale -1,1,-1");

    if (errors)
        test_failure("View transform +z direction test failed\n");


    free_matrix(t);
    free_matrix(expected);
    return errors;
}

static int test_view_transform_moves_world(void)
{
    int errors = 0;

    t_tuple from = point(0, 0, 8);
    t_tuple to   = point(0, 0, 0);
    t_tuple up   = vector(0, 1, 0);

    t_matrix t = view_transform(from, to, up);
    t_matrix expected = translation_matrix(0, 0, -8);

    errors += test_check(equal_matrix(t, expected),
                         "View transform does not match expected translation");

    if (errors)
        test_failure("View transformation moves world test failed\n");


    free_matrix(t);
    free_matrix(expected);
    return errors;
}

static int test_view_transform_arbitrary(void)
{
    int errors = 0;

    t_tuple from = point(1, 3, 2);
    t_tuple to   = point(4, -2, 8);
    t_tuple up   = vector(1, 1, 0);

    t_matrix t = view_transform(from, to, up);

    // Matriz esperada fornecida no feature
    t_matrix expected = new_matrix(4, 4);
    expected.data[0][0] = -0.50709; expected.data[0][1] = 0.50709;  expected.data[0][2] = 0.67612;  expected.data[0][3] = -2.36643;
    expected.data[1][0] = 0.76772;  expected.data[1][1] = 0.60609;  expected.data[1][2] = 0.12122;  expected.data[1][3] = -2.82843;
    expected.data[2][0] = -0.35857; expected.data[2][1] = 0.59761;  expected.data[2][2] = -0.71714; expected.data[2][3] = 0.0;
    expected.data[3][0] = 0.0;      expected.data[3][1] = 0.0;      expected.data[3][2] = 0.0;      expected.data[3][3] = 1.0;

    errors += test_check(equal_matrix(t, expected),
                         "Arbitrary view transform does not match expected matrix");

    if (errors)
        test_failure("Arbitrary view transformation test failed\n");

    free_matrix(t);
    free_matrix(expected);
    return errors;
}

int run_test_view_transform(void)
{
    int errors = 0;

    errors += test_view_transform_default_orientation();
    errors += test_view_transform_positive_z_direction();
    errors += test_view_transform_moves_world();
    errors += test_view_transform_arbitrary();

    if (errors)
        test_failure("View transform tests failed\n");
    else
        test_success("View transform tests passed");

    return errors;
}

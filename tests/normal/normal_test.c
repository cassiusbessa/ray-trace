/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:32:16 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 20:44:17 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_normal_sphere(void)
{
    t_object o;
    t_sphere s;
    t_tuple n;
    int errors = 0;

    s = new_sphere(point(0, 0, 0), 1);
    o.type = SPHERE;
    o.data = &s;
    n = normal_at(o, point(1, 0, 0));
    errors += test_check(equal_tuples(n, vector(1, 0, 0)), "Normal at point (1, 0, 0) should be (1, 0, 0)");
    n = normal_at(o, point(0, 1, 0));
    errors += test_check(equal_tuples(n, vector(0, 1, 0)), "Normal at point (0, 1, 0) should be (0, 1, 0)");
    n = normal_at(o, point(0, 0, 1));
    errors += test_check(equal_tuples(n, vector(0, 0, 1)), "Normal at point (0, 0, 1) should be (0, 0, 1)");
    n = normal_at(o, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    errors += test_check(equal_tuples(n, vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)), "Normal at point (sqrt(3)/3, sqrt(3)/3, sqrt(3)/3) should be (sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)");

    if (errors)
        test_failure("Normal tests failed");
    else
        test_success("Normal tests passed");
    return (errors);
}

static int test_normal_is_normalized_vector(void)
{
    t_object o;
    t_sphere s;
    t_tuple n;
    t_tuple n2;
    int errors = 0;

    s = new_sphere(point(0, 0, 0), 1);
    o.type = SPHERE;
    o.data = &s;
    n = normal_at(o, point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    n2 = normalize_vector(n);
    errors += test_check(equal_tuples(n2, vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)), "Normal at point (sqrt(3)/3, sqrt(3)/3, sqrt(3)/3) should be (sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)");
    if (errors)
        test_failure("Normal is normalized vector test failed");
    else
        test_success("Normal is normalized vector test passed");
    return (errors);
}

static int test_normal_on_translated_sphere(void)
{
    t_object o;
    t_sphere s;
    t_tuple n;
    t_matrix t;
    int errors = 0;

    s = new_sphere(point(0, 0, 0), 1);
    o.type = SPHERE;
    o.data = &s;
    t = translation_matrix(0, 1, 0);
    set_object_transform(&o, t);
    n = normal_at(o, point(0, 1.70711, -0.70711));
    errors += test_check(equal_tuples(n, vector(0, 0.70711, -0.70711)), "Normal at point (0, 1.70711, -0.70711) should be (0, 0.70711, -0.70711)");
    return (errors);
}

// static int test_normal_on_scaled_sphere(void)
// {
//     t_object o;
//     t_sphere s;
//     t_tuple n;
//     t_matrix sm;
//     t_matrix rm;
//     t_matrix scaled;
//     int errors = 0;

//     s = new_sphere(point(0, 0, 0), 1);
//     o.type = SPHERE;
//     o.data = &s;
//     sm = scaling_matrix(1, 0.5, 1);
//     rm = rotation_z_matrix(M_PI / 5);
//     scaled = matrix_multiply_by_matrix(sm, rm);
//     print_matrix(scaled);
//     set_object_transform(&o, scaled);
//     n = normal_at(o, point(0, sqrt(2) / 2, -sqrt(2) / 2));
//     printf("n x: %f\n", n.x);
//     printf("n y: %f\n", n.y);
//     printf("n z: %f\n", n.z);
//     errors += test_check(equal_tuples(n, vector(0, 0.97014f, -0.24254f)), "Normal at point (0, sqrt(2)/2, -sqrt(2)/2) should be (0, 0.97014, -0.24254)");
    
//     if (errors)
//         test_failure("Normal on scaled sphere test failed");
//     else
//         test_success("Normal on scaled sphere test passed");
//     return (errors);
// }

int run_normal_tests(void)
{
    int errors = 0;

    errors += test_normal_sphere();
    errors += test_normal_is_normalized_vector();
    errors += test_normal_on_translated_sphere();
    // errors += test_normal_on_scaled_sphere();

    if (errors)
        test_failure("Normal tests failed");
    else
        test_success("Normal tests passed");
    return (errors);
}
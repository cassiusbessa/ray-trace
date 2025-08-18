/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:32:16 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 19:34:10 by cassius          ###   ########.fr       */
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

    return (errors);
}

int run_normal_tests(void)
{
    int errors = 0;

    errors += test_normal_sphere();
    errors += test_normal_is_normalized_vector();

    if (errors)
        test_failure("Normal tests failed");
    else
        test_success("Normal tests passed");
    return (errors);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:50:32 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 21:03:11 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_reflect_vector(void)
{
    int errors = 0;
    t_tuple v;
    t_tuple n;
    t_tuple r;

    v = vector(1, -1, 0);
    n = vector(0, 1, 0);
    r = reflect(v, n);
    errors += test_check(equal_tuples(r, vector(1, 1, 0)), "Reflection of (1, -1, 0) over (0, 1, 0) should be (1, 1, 0)");

    if (errors)
        test_failure("Reflect vector tests failed");
    else
        test_success("Reflect vector tests passed");
    return (errors);
}

static int test_slanted_surface_reflect(void)
{
    int errors = 0;
    t_tuple v;
    t_tuple n;
    t_tuple r;

    v = vector(0, -1, 0);
    n = vector(sqrt(2)/2, sqrt(2)/2, 0); // Normal at 45 degrees
    r = reflect(v, n);
    errors += test_check(equal_tuples(r, vector(1, 0, 0)), "Reflection of (1, -1, 0) over (sqrt(2)/2, sqrt(2)/2, 0) should be (1, 0, 0)");

    if (errors)
        test_failure("SlantedReflect vector tests failed");
    else
        test_success("Slanted Reflect vector tests passed");
    return (errors);
}

int run_reflect_tests(void)
{
    int errors = 0;

    errors += test_reflect_vector();
    errors += test_slanted_surface_reflect();

    if (errors)
        test_failure("Reflect tests failed");
    else
        test_success("Reflect tests passed");
    return (errors);
}
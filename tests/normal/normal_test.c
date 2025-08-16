/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:32:16 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 21:05:00 by cassius          ###   ########.fr       */
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

    return (errors);
}

int run_normal_tests(void)
{
    int errors = 0;

    errors += test_normal_sphere();

    if (errors)
        test_failure("Normal tests failed");
    else
        test_success("Normal tests passed");
    return (errors);
}
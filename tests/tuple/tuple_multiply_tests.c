/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_multiply_tests.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:38:54 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:10:50 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	test_multiply_tuple_by_scalar(void)
{
    t_tuple	t1;
    t_tuple	result;
    int			errors;

    errors = 0;
    t1 = new_tuple(1, -2, 3, TRUE);
    result = multiply_tuple_by_scalar(t1, 3.5);
    errors += test_check_double(result.x, 3.5, "result.x should be 3.5");
    errors += test_check_double(result.y, -7, "result.y should be -7");
    errors += test_check_double(result.z, 10.5, "result.z should be 10.5");
    errors += test_check(result.w == 1, "result.w should be 1 (point)");
    if (errors == 0)
        test_success("test_multiply_tuple_by_scalar pass!");
    else
        test_failure("test_multiply_tuple_by_scalar failed.");
    return (errors);
}

int test_multiply_tuple_by_fraction(void)
{
    t_tuple	t1;
    t_tuple	result;
    int			errors;

    errors = 0;
    t1 = new_tuple(1, -2, 3, FALSE);
    result = multiply_tuple_by_scalar(t1, 0.5);
    errors += test_check_double(result.x, 0.5, "result.x should be 0.5");
    errors += test_check_double(result.y, -1, "result.y should be -1");
    errors += test_check_double(result.z, 1.5, "result.z should be 1.5");
    errors += test_check(result.w == 0, "result.w should be 0 (vector)");
    if (errors == 0)
        test_success("test_multiply_tuple_by_fraction pass!");
    else
        test_failure("test_multiply_tuple_by_fraction failed.");
    return (errors);
}
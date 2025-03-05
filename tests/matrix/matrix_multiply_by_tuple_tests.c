/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply_by_tuple_tests.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:05:29 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/22 22:21:46 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix matrix_a(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 2;
    matrix.data[0][2] = 3;
    matrix.data[0][3] = 4;
    matrix.data[1][0] = 2;
    matrix.data[1][1] = 4;
    matrix.data[1][2] = 4;
    matrix.data[1][3] = 2;
    matrix.data[2][0] = 8;
    matrix.data[2][1] = 6;
    matrix.data[2][2] = 4;
    matrix.data[2][3] = 1;
    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 1;
    return (matrix);
}

static t_tuple tuple(void)
{
    t_tuple tuple;

    tuple = new_tuple(1, 2, 3, 1);
    return (tuple);
}

static t_tuple tuple_result(void)
{
    t_tuple tuple;

    tuple = new_tuple(18, 24, 33, 1);
    return (tuple);
}

int     test_multiply_matrix_by_tuple(void)
{
    t_matrix    a;
    t_tuple     b;
    t_tuple     result;
    t_tuple     expected;
    int         errors;

    a = matrix_a();
    b = tuple();
    result = matrix_multiply_by_tuple(a, b);
    expected = tuple_result();
    errors = 0;
    errors += test_check_double(result.x, expected.x, "multiply_matrix_by_tuple failed for x");
    errors += test_check_double(result.y, expected.y, "multiply_matrix_by_tuple failed for y");
    errors += test_check_double(result.z, expected.z, "multiply_matrix_by_tuple failed for z");
    errors += test_check_double(result.w, expected.w, "multiply_matrix_by_tuple failed for w");
    free_matrix(a);
    if (errors)
        test_failure("test_multiply_matrix_by_tuple");
    else
        test_success("test_multiply_matrix_by_tuple");
    return (errors);
}
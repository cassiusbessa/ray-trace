/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_matrix_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:41:16 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/22 23:47:44 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix matrix_a(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = 0;
    matrix.data[0][1] = 9;
    matrix.data[0][2] = 3;
    matrix.data[0][3] = 0;
    matrix.data[1][0] = 9;
    matrix.data[1][1] = 8;
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 8;
    matrix.data[2][0] = 1;
    matrix.data[2][1] = 8;
    matrix.data[2][2] = 5;
    matrix.data[2][3] = 3;
    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 5;
    matrix.data[3][3] = 8;
    return (matrix);
}

static t_matrix matrix_b(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = 0;
    matrix.data[0][1] = 9;
    matrix.data[0][2] = 1;
    matrix.data[0][3] = 0;
    matrix.data[1][0] = 9;
    matrix.data[1][1] = 8;
    matrix.data[1][2] = 8;
    matrix.data[1][3] = 0;
    matrix.data[2][0] = 3;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 5;
    matrix.data[2][3] = 5;
    matrix.data[3][0] = 0;
    matrix.data[3][1] = 8;
    matrix.data[3][2] = 3;
    matrix.data[3][3] = 8;
    return (matrix);
}

static int test_transpose_matrix(void)
{
    t_matrix    a;
    t_matrix    result;
    t_matrix    expected;
    int         errors;

    a = matrix_a();
    result = transpose_matrix(a);
    expected = matrix_b();
    errors = 0;
    errors += test_check(equal_matrix(result, expected), "Test transpose_matrix");
    free_matrix(a);
    free_matrix(result);
    free_matrix(expected);
    if (errors)
        test_failure("test_transpose_matrix");
    else
        test_success("test_transpose_matrix");
    return (errors);
}

int rotate_matrix_tests(void)
{
    int errors;

    errors = 0;
    errors += test_transpose_matrix();
    if (errors)
        test_failure("rotate_matrix_tests");
    else
        test_success("rotate_matrix_tests");
    return (errors);
}
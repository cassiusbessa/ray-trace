/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply_by_matrix_tests.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:21:33 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 09:05:13 by emorshhe         ###   ########.fr       */
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
    matrix.data[1][0] = 5;
    matrix.data[1][1] = 6;
    matrix.data[1][2] = 7;
    matrix.data[1][3] = 8;
    matrix.data[2][0] = 9;
    matrix.data[2][1] = 8;
    matrix.data[2][2] = 7;
    matrix.data[2][3] = 6;
    matrix.data[3][0] = 5;
    matrix.data[3][1] = 4;
    matrix.data[3][2] = 3;
    matrix.data[3][3] = 2;
    return (matrix);

}

static t_matrix matrix_b(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = -2;
    matrix.data[0][1] = 1;
    matrix.data[0][2] = 2;
    matrix.data[0][3] = 3;
    matrix.data[1][0] = 3;
    matrix.data[1][1] = 2;
    matrix.data[1][2] = 1;
    matrix.data[1][3] = -1;
    matrix.data[2][0] = 4;
    matrix.data[2][1] = 3;
    matrix.data[2][2] = 6;
    matrix.data[2][3] = 5;
    matrix.data[3][0] = 1;
    matrix.data[3][1] = 2;
    matrix.data[3][2] = 7;
    matrix.data[3][3] = 8;
    return (matrix);
}

static t_matrix matrix_result(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = 20;
    matrix.data[0][1] = 22;
    matrix.data[0][2] = 50;
    matrix.data[0][3] = 48;
    matrix.data[1][0] = 44;
    matrix.data[1][1] = 54;
    matrix.data[1][2] = 114;
    matrix.data[1][3] = 108;
    matrix.data[2][0] = 40;
    matrix.data[2][1] = 58;
    matrix.data[2][2] = 110;
    matrix.data[2][3] = 102;
    matrix.data[3][0] = 16;
    matrix.data[3][1] = 26;
    matrix.data[3][2] = 46;
    matrix.data[3][3] = 42;
    return (matrix);
}

static int  test_multiply_matrix_by_matrix(void)
{
    t_matrix	matrix1;
    t_matrix	matrix2;
    t_matrix	result;
    t_matrix    expected;
    int			errors;

    errors = 0;
    matrix1 = matrix_a();
    matrix2 = matrix_b();
    expected = matrix_result();
    result = matrix_multiply_by_matrix(matrix1, matrix2);
    errors += test_check(equal_matrix(result, expected), "matrix1 * matrix2 should be equal to matrix_result");
    free_matrix(matrix1);
    free_matrix(matrix2);
    free_matrix(result);
    free_matrix(expected);
    if (errors)
        test_failure("test_multiply_matrix_by_matrix");
    else
        test_success("test_multiply_matrix_by_matrix");
    return (errors);
}

int all_multiply_matrix_by_matrix_tests(void)
{
    int errors;

    errors = 0;
    errors += test_multiply_matrix_by_matrix();
    return (errors);
}
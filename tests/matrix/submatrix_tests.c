/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrix_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:05:12 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/12 20:21:29 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

t_matrix matrix_a(void)
{
    t_matrix    matrix;

    matrix = new_matrix(3, 3);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 5;
    matrix.data[0][2] = 0;
    matrix.data[1][0] = -3;
    matrix.data[1][1] = 2;
    matrix.data[1][2] = 7;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = 6;
    matrix.data[2][2] = -3;
    return (matrix);
}

t_matrix matrix_b(void)
{
    t_matrix    matrix;

    matrix = new_matrix(2, 2);
    matrix.data[0][0] = -3;
    matrix.data[0][1] = 2;
    matrix.data[1][0] = 0;
    matrix.data[1][1] = 6;
    return (matrix);
}

static int  submatrix_3x3(void)
{
    t_matrix    matrix;
    t_matrix    sub;
    t_matrix    expected;
    int         error;

    matrix = matrix_a();
    expected = matrix_b();
    sub = submatrix(matrix, 0, 2);
    error = test_check(equal_matrix(sub, expected), "submatrix_3x3");
    free_matrix(matrix);
    free_matrix(sub);
    free_matrix(expected);
    if (error)
        test_failure("submatrix_3x3");
    else
        test_success("submatrix_3x3");
    return (error);
}

t_matrix matrix_c(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = -6;
    matrix.data[0][1] = 1;
    matrix.data[0][2] = 1;
    matrix.data[0][3] = 6;
    matrix.data[1][0] = -8;
    matrix.data[1][1] = 5;
    matrix.data[1][2] = 8;
    matrix.data[1][3] = 6;
    matrix.data[2][0] = -1;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 8;
    matrix.data[2][3] = 2;
    matrix.data[3][0] = -7;
    matrix.data[3][1] = 1;
    matrix.data[3][2] = -1;
    matrix.data[3][3] = 1;
    return (matrix);
}

t_matrix matrix_d(void)
{
    t_matrix    matrix;

    matrix = new_matrix(3, 3);
    matrix.data[0][0] = -6;
    matrix.data[0][1] = 1;
    matrix.data[0][2] = 6;
    matrix.data[1][0] = -8;
    matrix.data[1][1] = 8;
    matrix.data[1][2] = 6;
    matrix.data[2][0] = -7;
    matrix.data[2][1] = -1;
    matrix.data[2][2] = 1;
    return (matrix);
}

static int  submatrix_4x4(void)
{
    t_matrix    matrix;
    t_matrix    sub;
    t_matrix    expected;
    int         error;

    matrix = matrix_c();
    expected = matrix_d();
    sub = submatrix(matrix, 2, 1);
    error = test_check(equal_matrix(sub, expected), "submatrix_4x4");
    free_matrix(matrix);
    free_matrix(sub);
    free_matrix(expected);
    if (error)
        test_failure("submatrix_4x4");
    else
        test_success("submatrix_4x4");
    return (error);
}

int test_submatrix(void)
{
    int error;

    error = 0;
    error += submatrix_3x3();
    error += submatrix_4x4();
    return (error);
}
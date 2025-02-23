/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrix_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:05:12 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/23 01:16:38 by caqueiro         ###   ########.fr       */
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

int test_submatrix(void)
{
    int error;

    error = 0;
    error += submatrix_3x3();
    return (error);
}
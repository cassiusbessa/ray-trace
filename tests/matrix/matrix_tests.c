/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:56:04 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/23 00:22:40 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix mock_matrix(void)
{
    t_matrix	matrix;
    int			i;
    int			j;

    matrix = new_matrix(4, 4);
    i = 0;
    while (i < matrix.size)
    {
        j = 0;
        while (j < matrix.size)
        {
            matrix.data[i][j] = rand() % 100;
            j++;
        }
        i++;
    }
    return (matrix);
}

static int  test_create_matrix(void)
{
    t_matrix	matrix;
    int			errors;

    errors = 0;
    matrix = new_matrix(4, 4);
    errors += test_check(matrix.size == 4, "matrix.size should be 4");
    errors += test_check(matrix.data[0][0] == 0, "matrix.data[0][0] should be 0");
    errors += test_check(matrix.data[0][1] == 0, "matrix.data[0][1] should be 0");
    errors += test_check(matrix.data[0][3] == 0, "matrix.data[0][3] should be 0");
    errors += test_check(matrix.data[1][0] == 0, "matrix.data[1][0] should be 0");
    errors += test_check(matrix.data[2][3] == 0, "matrix.data[2][3] should be 0");
    errors += test_check(matrix.data[3][0] == 0, "matrix.data[3][0] should be 0");
    errors += test_check(matrix.data[3][1] == 0, "matrix.data[3][1] should be 0");
    errors += test_check(matrix.data[3][2] == 0, "matrix.data[3][2] should be 0");
    errors += test_check(matrix.data[3][3] == 0, "matrix.data[3][3] should be 0");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_create_matrix pass!");
    else
        test_failure("test_create_matrix failed.");
    return (errors);
}

static int test_equals_marix(void)
{
    t_matrix	matrix1;
    t_matrix	matrix2;
    int			errors;

    errors = 0;
    matrix1 = new_matrix(4, 4);
    matrix2 = new_matrix(4, 4);
    errors += test_check(equal_matrix(matrix1, matrix2), "matrix1 should be equal to matrix2");
    free_matrix(matrix1);
    free_matrix(matrix2);
    if (errors == 0)
        test_success("test_equals_matrix pass!");
    else
        test_failure("test_equals_matrix failed.");
    return (errors);
}

static int test_not_equals_marix(void)
{
    t_matrix	matrix1;
    t_matrix	matrix2;
    int			errors;

    errors = 0;
    matrix1 = mock_matrix();
    matrix2 = mock_matrix();
    errors += test_check(!equal_matrix(matrix1, matrix2), "matrix1 should not be equal to matrix2");
    free_matrix(matrix1);
    free_matrix(matrix2);
    if (errors == 0)
        test_success("test_not_equals_matrix pass!");
    else
        test_failure("test_not_equals_matrix failed.");
    return (errors);
}

int all_matrix_tests(void)
{
    int errors;

    errors = 0;
    errors += test_create_matrix();
    errors += test_equals_marix();
    errors += test_not_equals_marix();
    errors += all_multiply_matrix_by_matrix_tests();
    errors += test_multiply_matrix_by_tuple();
    errors += identity_matrix_tests();
    errors += rotate_matrix_tests();
    errors += test_determinant_2x2_matrix();
    if (errors == 0)
        ft_printf("\n🎉 All matrix tests fine!\n");
    else
        ft_printf("\n❌ %d matrix tests failed.\n", errors);
    return (errors);
}
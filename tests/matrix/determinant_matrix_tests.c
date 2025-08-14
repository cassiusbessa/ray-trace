/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant_matrix_tests.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:04:21 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 08:53:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix    matrix_a(void)
{
    t_matrix	matrix;

    matrix = new_matrix(2, 2);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 5;
    matrix.data[1][0] = -3;
    matrix.data[1][1] = 2;
    return (matrix);
}

static t_matrix matrix_b(void)
{
    t_matrix    matrix;

    matrix = new_matrix(3, 3);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 2;
    matrix.data[0][2] = 6;
    matrix.data[1][0] = -5;
    matrix.data[1][1] = 8;
    matrix.data[1][2] = -4;
    matrix.data[2][0] = 2;
    matrix.data[2][1] = 6;
    matrix.data[2][2] = 4;
    return (matrix);
}

static t_matrix matrix_c(void)
{
    t_matrix    matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = -2;
    matrix.data[0][1] = -8;
    matrix.data[0][2] = 3;
    matrix.data[0][3] = 5;
    matrix.data[1][0] = -3;
    matrix.data[1][1] = 1;
    matrix.data[1][2] = 7;
    matrix.data[1][3] = 3;
    matrix.data[2][0] = 1;
    matrix.data[2][1] = 2;
    matrix.data[2][2] = -9;
    matrix.data[2][3] = 6;
    matrix.data[3][0] = -6;
    matrix.data[3][1] = 7;
    matrix.data[3][2] = 7;
    matrix.data[3][3] = -9;
    return (matrix);
}



static int   test_determinant_2x2_matrix(void)
{
    t_matrix	matrix;
    float		determinant;
    float		expected;
    int			errors;

    matrix = matrix_a();
    determinant = matrix_determinant_2x2(matrix);
    expected = 17;
    errors = 0;
    errors += test_check_double(determinant, expected, "determinant_2x2_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_determinant_2x2_matrix pass!");
    else
        test_failure("test_determinant_2x2_matrix failed.");
    return (errors);
}

static int test_determinant_matrix1(void)
{
    t_matrix    matrix;
    float      determinant;
    float      expected;
    int     errors;

    matrix = matrix_b();
    determinant = determinant_matrix(matrix);
    expected = -196;
    errors = 0;
    errors += test_check_double(determinant, expected, "determinant_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_determinant_matrix pass!");
    else
        test_failure("test_determinant_matrix failed.");
    return (errors);
}

static int test_determinant_matrix2(void)
{
    t_matrix    matrix;
    float      determinant;
    float      expected;
    int     errors;

    matrix = matrix_c();
    determinant = determinant_matrix(matrix);
    expected = -4071;
    errors = 0;
    errors += test_check_double(determinant, expected, "determinant_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_determinant_matrix pass!");
    else
        test_failure("test_determinant_matrix failed.");
    return (errors);
}

int test_determinant_matrix(void)
{
    int errors;

    errors = 0;
    errors += test_determinant_2x2_matrix();
    errors += test_determinant_matrix1();
    errors += test_determinant_matrix2();
    if (errors == 0)
        printf("✅ All determinant_matrix_tests passed!\n");
    else
        printf("❌ Some determinant_matrix_tests failed.\n");
    return (errors);
}
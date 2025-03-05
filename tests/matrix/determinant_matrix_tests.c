/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant_matrix_tests.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:04:21 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/23 00:32:49 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix	matrix_c(void)
{
    t_matrix	matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = 2;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[0][3] = 0;
    matrix.data[1][0] = 0;
    matrix.data[1][1] = 3;
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 0;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = 5;
    matrix.data[2][3] = 0;
    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 23;
    return (matrix);
}

static t_matrix	matrix_b(void)
{
    t_matrix	matrix;

    matrix = new_matrix(3, 3);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 5;
    matrix.data[0][2] = 0;
    matrix.data[1][0] = -3;
    matrix.data[1][1] = 2;
    matrix.data[1][2] = 7;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = 6;
    matrix.data[2][2] = 1;
    return (matrix);
}
static t_matrix	matrix_a(void)
{
    t_matrix	matrix;

    matrix = new_matrix(2, 2);
    matrix.data[0][0] = 1;
    matrix.data[0][1] = 5;
    matrix.data[1][0] = -3;
    matrix.data[1][1] = 2;
    return (matrix);
}

int	test_determinant_2x2_matrix(void)
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

int test_determinant_3x3_matrix(void)
{
    t_matrix	matrix;
    float		determinant;
    float		expected;
    int			errors;

    matrix = matrix_b();
    determinant = matrix_determinant(matrix);
    expected = -25;
    errors = 0;
    errors += test_check_double(determinant, expected, "determinant_3x3_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_determinant_3x3_matrix pass!");
    else
        test_failure("test_determinant_3x3_matrix failed.");
    return (errors);
}

int test_determinant_4x4_matrix(void)
{
    t_matrix	matrix;
    float		determinant;
    float		expected;
    int			errors;

    matrix = matrix_c();
    determinant = matrix_determinant(matrix);
    expected = 690;
    errors = 0;
    errors += test_check_double(determinant, expected, "determinant_4x4_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_determinant_4x4_matrix pass!");
    else
        test_failure("test_determinant_4x4_matrix failed.");
    return (errors);
}
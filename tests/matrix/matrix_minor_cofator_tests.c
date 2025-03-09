/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_minor_cofator_tests.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:20:33 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/03/05 18:20:33 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix	matrix_b(void)
{
	t_matrix	matrix;

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

static t_matrix	matrix_a(void)
{
	t_matrix	matrix;

	matrix = new_matrix(3, 3);
    matrix.data[0][0] = 3;
    matrix.data[0][1] = 5;
    matrix.data[0][2] = 0;
    matrix.data[1][0] = 2;
    matrix.data[1][1] = -1;
    matrix.data[1][2] = -7;
    matrix.data[2][0] = 6;
    matrix.data[2][1] = -1;
    matrix.data[2][2] = 5;
	return (matrix);
}

static t_matrix	matrix_c(void)
{
	t_matrix	matrix;

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

int test_minor_matrix(void)
{
    t_matrix	matrix;
    int			minor_matrix;
    int			expected;
    int			errors;

    matrix = matrix_a();
    expected = 25;
    minor_matrix = matrix_minor(matrix, 1, 0);
    errors = 0;
    errors += test_check_double(minor_matrix, expected, "minor_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_minor_matrix pass!");
    else
        test_failure("test_minor_matrix failed.");
    return (errors);
}

int test_cofactor_determinant_3x3_matrix(void)
{
	t_matrix	matrix;
	int			cofactor_00;
	int 		cofactor_01;
	int 		cofactor_02;
	int			det;
	int			errors = 0;

	matrix = matrix_c();
	cofactor_00 = matrix_cofactor(matrix, 0, 0);
	cofactor_01 = matrix_cofactor(matrix, 0, 1);
	cofactor_02 = matrix_cofactor(matrix, 0, 2);
	det = matrix_determinant(matrix);
	errors += test_check_double(cofactor_00, 56, "cofactor_matrix[0][0]");
	errors += test_check_double(cofactor_01, 12, "cofactor_matrix[0][1]");
	errors += test_check_double(cofactor_02, -46, "cofactor_matrix[0][2]");
	errors += test_check_double(det, -196, "determinant_matrix");
	free_matrix(matrix);
	if (errors == 0)
		test_success("test_cofactor_determinant_3x3_matrix pass!");
	else
		test_failure("test_cofactor_determinant_3x3_matrix failed.");
	return (errors);
}

int test_cofactor_determinant_4x4_matrix(void)
{
	t_matrix	matrix;
	int			cofactor_00;
	int 		cofactor_01;
	int 		cofactor_02;
	int 		cofactor_03;
	int			det;
	int			errors = 0;

	matrix = matrix_b();
	cofactor_00 = matrix_cofactor(matrix, 0, 0);
	cofactor_01 = matrix_cofactor(matrix, 0, 1);
	cofactor_02 = matrix_cofactor(matrix, 0, 2);
	cofactor_03 = matrix_cofactor(matrix, 0, 3);
	det = matrix_determinant(matrix);
	errors += test_check_double(cofactor_00, 690, "cofactor_matrix[0][0]");
	errors += test_check_double(cofactor_01, 447, "cofactor_matrix[0][1]");
	errors += test_check_double(cofactor_02, 210, "cofactor_matrix[0][2]");
	errors += test_check_double(cofactor_03, 51, "cofactor_matrix[0][3]");
	errors += test_check_double(det, -4071, "determinant_matrix");
	free_matrix(matrix);
	if (errors == 0)
		test_success("test_cofactor_determinant_4x4_matrix pass!");
	else
		test_failure("test_cofactor_determinant_4x4_matrix failed.");
	return (errors);
}
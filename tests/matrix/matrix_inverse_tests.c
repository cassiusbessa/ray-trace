/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse_tests.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 00:18:53 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/03/09 00:18:53 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix matrix_f(void)
{
	t_matrix matrix;

	matrix = new_matrix(4, 4);
	matrix.data[0][0] = 9;
	matrix.data[0][1] = 3;
	matrix.data[0][2] = 0;
	matrix.data[0][3] = 9;
	matrix.data[1][0] = -5;
	matrix.data[1][1] = -2;
	matrix.data[1][2] = -6;
	matrix.data[1][3] = -3;
	matrix.data[2][0] = -4;
	matrix.data[2][1] = 9;
	matrix.data[2][2] = 6;
	matrix.data[2][3] = 4;
	matrix.data[3][0] = -7;
	matrix.data[3][1] = 6;
	matrix.data[3][2] = 6;
	matrix.data[3][3] = 2;
	return (matrix);
}
static t_matrix matrix_g(void)
{
	t_matrix matrix;

	matrix = new_matrix(4, 4);
	matrix.data[0][0] = 3;
	matrix.data[0][1] = -9;
	matrix.data[0][2] = 7;
	matrix.data[0][3] = 3;
	matrix.data[1][0] = 3;
	matrix.data[1][1] = -8;
	matrix.data[1][2] = 2;
	matrix.data[1][3] = -9;
	matrix.data[2][0] = -4;
	matrix.data[2][1] = 4;
	matrix.data[2][2] = 4;
	matrix.data[2][3] = 1;
	matrix.data[3][0] = -6;
	matrix.data[3][1] = 5;
	matrix.data[3][2] = -1;
	matrix.data[3][3] = 1;
	return (matrix);
}

static t_matrix matrix_h(void)
{
	t_matrix matrix;

	matrix = new_matrix(4, 4);
	matrix.data[0][0] = 8;
	matrix.data[0][1] = 2;
	matrix.data[0][2] = 2;
	matrix.data[0][3] = 2;
	matrix.data[1][0] = 3;
	matrix.data[1][1] = -1;
	matrix.data[1][2] = 7;
	matrix.data[1][3] = 0;
	matrix.data[2][0] = 7;
	matrix.data[2][1] = 0;
	matrix.data[2][2] = 5;
	matrix.data[2][3] = 4;
	matrix.data[3][0] = 6;
	matrix.data[3][1] = -2;
	matrix.data[3][2] = 0;
	matrix.data[3][3] = 5;
	return (matrix);
}

static t_matrix matrix_e(void)
{
	t_matrix matrix;

	matrix = new_matrix(4, 4);
	matrix.data[0][0] = 8;
	matrix.data[0][1] = -5;
	matrix.data[0][2] = 9;
	matrix.data[0][3] = 2;
	matrix.data[1][0] = 7;
	matrix.data[1][1] = 5;
	matrix.data[1][2] = 6;
	matrix.data[1][3] = 1;
	matrix.data[2][0] = -6;
	matrix.data[2][1] = 0;
	matrix.data[2][2] = 9;
	matrix.data[2][3] = 6;
	matrix.data[3][0] = -3;
	matrix.data[3][1] = 0;
	matrix.data[3][2] = -9;
	matrix.data[3][3] = -4;
	return (matrix);
}

static t_matrix matrix_d(void)
{
	t_matrix matrix;

	matrix = new_matrix(4, 4);
	matrix.data[0][0] = -5;
	matrix.data[0][1] = 2;
	matrix.data[0][2] = 6;
	matrix.data[0][3] = -8;
	matrix.data[1][0] = 1;
	matrix.data[1][1] = -5;
	matrix.data[1][2] = 1;
	matrix.data[1][3] = 8;
	matrix.data[2][0] = 7;
	matrix.data[2][1] = 7;
	matrix.data[2][2] = -6;
	matrix.data[2][3] = -7;
	matrix.data[3][0] = 1;
	matrix.data[3][1] = -3;
	matrix.data[3][2] = 7;
	matrix.data[3][3] = 4;
	return (matrix);
}

int test_inverse_matrix(void)
{
	t_matrix matrix;
	t_matrix inv;
	float det;
	int errors;

	matrix = matrix_d();
	inv = matrix_inverse(matrix);
	det = (float)matrix_determinant(matrix);
	errors = 0;
	
	errors += test_check_double(det, 532.0, "determinant_matrix");
	errors += test_check_double(matrix_cofactor(matrix, 2, 3), -160, "cofactor_matrix[2][3]");
	errors += test_check_double(inv.data[3][2], -160.0 / det, "inverse_matrix[3][2]");
	errors += test_check_double(matrix_cofactor(matrix, 3, 2), 105, "cofactor_matrix[3][2]");
	errors += test_check_double(inv.data[2][3], 105.0 / det, "inverse_matrix[2][3]");

	errors += test_check_double(inv.data[0][0], 0.21805, "inverse_matrix[0][0]");
	errors += test_check_double(inv.data[0][1], 0.45113, "inverse_matrix[0][1]");
	errors += test_check_double(inv.data[0][2], 0.24060, "inverse_matrix[0][2]");
	errors += test_check_double(inv.data[0][3], -0.04511, "inverse_matrix[0][3]");

	errors += test_check_double(inv.data[1][0], -0.80827, "inverse_matrix[1][0]");
	errors += test_check_double(inv.data[1][1], -1.45677, "inverse_matrix[1][1]");
	errors += test_check_double(inv.data[1][2], -0.44361, "inverse_matrix[1][2]");
	errors += test_check_double(inv.data[1][3], 0.52068, "inverse_matrix[1][3]");

	errors += test_check_double(inv.data[2][0], -0.07895, "inverse_matrix[2][0]");
	errors += test_check_double(inv.data[2][1], -0.22368, "inverse_matrix[2][1]");
	errors += test_check_double(inv.data[2][2], -0.05263, "inverse_matrix[2][2]");
	errors += test_check_double(inv.data[2][3], 0.19737, "inverse_matrix[2][3]");

	errors += test_check_double(inv.data[3][0], -0.52256, "inverse_matrix[3][0]");
	errors += test_check_double(inv.data[3][1], -0.81391, "inverse_matrix[3][1]");
	errors += test_check_double(inv.data[3][2], -0.30075, "inverse_matrix[3][2]");
	errors += test_check_double(inv.data[3][3], 0.30639, "inverse_matrix[3][3]");

	free_matrix(matrix);
	free_matrix(inv);
	if (errors == 0)
		test_success("test_inverse_matrix pass!");
	else
		test_failure("test_inverse_matrix failed.");
	return (errors);
}

int test_inverse_matrix_2(void)
{
	t_matrix matrix;
	t_matrix inv;
	int errors;

	matrix = matrix_e();
	inv = matrix_inverse(matrix);
	errors = 0;
	
	errors += test_check_double(inv.data[0][0], -0.15385, "inverse2[0][0]");
	errors += test_check_double(inv.data[0][1], -0.15385, "inverse2[0][1]");
	errors += test_check_double(inv.data[0][2], -0.28205, "inverse2[0][2]");
	errors += test_check_double(inv.data[0][3], -0.53846, "inverse2[0][3]");

	errors += test_check_double(inv.data[1][0], -0.07692, "inverse2[1][0]");
	errors += test_check_double(inv.data[1][1], 0.12308, "inverse2[1][1]");
	errors += test_check_double(inv.data[1][2], 0.02564, "inverse2[1][2]");
	errors += test_check_double(inv.data[1][3], 0.03077, "inverse2[1][3]");

	errors += test_check_double(inv.data[2][0], 0.35897, "inverse2[2][0]");
	errors += test_check_double(inv.data[2][1], 0.35897, "inverse2[2][1]");
	errors += test_check_double(inv.data[2][2], 0.43590, "inverse2[2][2]");
	errors += test_check_double(inv.data[2][3], 0.92308, "inverse2[2][3]");

	errors += test_check_double(inv.data[3][0], -0.69231, "inverse2[3][0]");
	errors += test_check_double(inv.data[3][1], -0.69231, "inverse2[3][1]");
	errors += test_check_double(inv.data[3][2], -0.76923, "inverse2[3][2]");
	errors += test_check_double(inv.data[3][3], -1.92308, "inverse2[3][3]");

	free_matrix(matrix);
	free_matrix(inv);
	if (errors == 0)
		test_success("test_inverse_matrix_2 pass!");
	else
		test_failure("test_inverse_matrix_2 failed.");
	return (errors);
}
int test_inverse_matrix_3(void)
{
	t_matrix matrix;
	t_matrix inv;
	int errors;

	matrix = matrix_f();
	inv = matrix_inverse(matrix);
	errors = 0;
	
	errors += test_check_double(inv.data[0][0], -0.04074, "inverse3[0][0]");
	errors += test_check_double(inv.data[0][1], -0.07778, "inverse3[0][1]");
	errors += test_check_double(inv.data[0][2], 0.14444, "inverse3[0][2]");
	errors += test_check_double(inv.data[0][3], -0.22222, "inverse3[0][3]");

	errors += test_check_double(inv.data[1][0], -0.07778, "inverse3[1][0]");
	errors += test_check_double(inv.data[1][1], 0.03333, "inverse3[1][1]");
	errors += test_check_double(inv.data[1][2], 0.36667, "inverse3[1][2]");
	errors += test_check_double(inv.data[1][3], -0.33333, "inverse3[1][3]");

	errors += test_check_double(inv.data[2][0], -0.02901, "inverse3[2][0]");
	errors += test_check_double(inv.data[2][1], -0.14630, "inverse3[2][1]");
	errors += test_check_double(inv.data[2][2], -0.10926, "inverse3[2][2]");
	errors += test_check_double(inv.data[2][3], 0.12963, "inverse3[2][3]");

	errors += test_check_double(inv.data[3][0], 0.17778, "inverse3[3][0]");
	errors += test_check_double(inv.data[3][1], 0.06667, "inverse3[3][1]");
	errors += test_check_double(inv.data[3][2], -0.26667, "inverse3[3][2]");
	errors += test_check_double(inv.data[3][3], 0.33333, "inverse3[3][3]");

	free_matrix(matrix);
	free_matrix(inv);
	if (errors == 0)
		test_success("test_inverse_matrix_3 pass!");
	else
		test_failure("test_inverse_matrix_3 failed.");
	return (errors);
}

int test_multiply_by_inverse(void)
{
	t_matrix A;
	t_matrix B;
	t_matrix C;
	t_matrix invB;
	t_matrix result;
	int errors;
	int i;
	int j;

	A = matrix_g();
	B = matrix_h();
	C = matrix_multiply_by_matrix(A, B);
	invB = matrix_inverse(B);
	result = matrix_multiply_by_matrix(C, invB);

	errors = 0;
	i = 0;
	while (i < A.size)
	{
		j = 0;
		while (j < A.size)
		{
			errors += test_check_double(result.data[i][j], A.data[i][j], "multiply_by_inverse element");
			j++;
		}
		i++;
	}
	if (errors == 0)
		test_success("test_multiply_by_inverse pass!");
	else
		test_failure("test_multiply_by_inverse failed.");

	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(invB);
	free_matrix(result);
	return (errors);
}
int all_matrix_inverse_tests(void)
{
	int errors;

	errors = 0;
	errors += test_inverse_matrix();
	errors += test_inverse_matrix_2();
	errors += test_inverse_matrix_3();
	errors += test_multiply_by_inverse();
	return (errors);
}
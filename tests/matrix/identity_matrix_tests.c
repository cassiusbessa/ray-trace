/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix_tests.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:45:04 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/22 23:58:47 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix	matrix_a(void)
{
	t_matrix	matrix;

	matrix = new_matrix(4, 4);
	matrix.data[0][0] = 0;
	matrix.data[0][1] = 1;
	matrix.data[0][2] = 2;
	matrix.data[0][3] = 4;
	matrix.data[1][0] = 1;
	matrix.data[1][1] = 2;
	matrix.data[1][2] = 4;
	matrix.data[1][3] = 8;
	matrix.data[2][0] = 2;
	matrix.data[2][1] = 4;
	matrix.data[2][2] = 8;
	matrix.data[2][3] = 16;
	matrix.data[3][0] = 4;
	matrix.data[3][1] = 8;
	matrix.data[3][2] = 16;
	matrix.data[3][3] = 32;
	return (matrix);
}

static t_tuple	tuple_result(void)
{
	t_tuple	tuple;

	tuple = new_tuple(1, 2, 3, 4);
	return (tuple);
}

static int	test_multiply_identity_matrix_for_tuple(void)
{
	t_matrix	identity;
	t_tuple		b;
	t_tuple		result;
	t_tuple		expected;
	int			errors;

    identity = identity_matrix(4);
    b = new_tuple(1, 2, 3, 4);
    result = matrix_multiply_by_tuple(identity, b);
    expected = tuple_result();
    errors = 0;
    errors += test_check_double(result.x, expected.x, "multiply_identity_matrix_for_tuple");
    errors += test_check_double(result.y, expected.y, "multiply_identity_matrix_for_tuple");
    errors += test_check_double(result.z, expected.z, "multiply_identity_matrix_for_tuple");
    errors += test_check_double(result.w, expected.w, "multiply_identity_matrix_for_tuple");
    free_matrix(identity);
    if (errors)
        printf("❌ test_multiply_identity_matrix_for_tuple failed\n");
    else
        printf("✅ test_multiply_identity_matrix_for_tuple passed\n");
    return (errors);
}

static int	test_multiply_matrix_for_identity(void)
{
	t_matrix m;
	t_matrix expected;
    t_matrix result;
    int errors;

    m = identity_matrix(4);
    expected = matrix_a();
    result = matrix_multiply_by_matrix(m, expected);
    errors = 0;
    errors += !equal_matrix(result, expected);
    free_matrix(m);
    free_matrix(expected);
    free_matrix(result);
    if (errors)
        printf("❌ test_multiply_matrix_for_identity failed\n");
    else
        printf("✅ test_multiply_matrix_for_identity passed\n");
    return (errors);
}

int    identity_matrix_tests(void)
{
    int errors;

    errors = 0;
    errors += test_multiply_identity_matrix_for_tuple();
    errors += test_multiply_matrix_for_identity();
    if (errors)
        printf("❌ identity_matrix_tests failed\n");
    else
        printf("✅ identity_matrix_tests passed\n");
    return (errors);
}
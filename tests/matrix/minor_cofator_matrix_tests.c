/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_cofator_matrix_tests.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:20:33 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/03/05 18:20:33 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

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

int test_minor_matrix(void)
{
    t_matrix	matrix;
    int			minor_matrix;
    int			expected;
    int			errors;

    matrix = matrix_a();
    expected = 25;
    minor_matrix = minor(matrix, 1, 0);
    errors = 0;
    errors += test_check_double(minor_matrix, expected, "minor_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_minor_matrix pass!");
    else
        test_failure("test_minor_matrix failed.");
    return (errors);
}

int test_cofactor_matrix(void)
{
    t_matrix	matrix;
    int			cofactor_matrix;
    int			expected;
    int			errors;

    matrix = matrix_a();
    expected = -25;
    cofactor_matrix = cofactor(matrix, 1, 0);
    errors = 0;
    errors += test_check_double(cofactor_matrix, expected, "cofactor_matrix");
    free_matrix(matrix);
    if (errors == 0)
        test_success("test_cofactor_matrix pass!");
    else
        test_failure("test_cofactor_matrix failed.");
    return (errors);
}
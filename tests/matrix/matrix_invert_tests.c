/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invert_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:26:17 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/03/05 19:26:17 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix	matrix_b(void)
{
	t_matrix	matrix;

	matrix = new_matrix(4, 4);
    matrix.data[0][0] = -4;
    matrix.data[0][1] = 2;
    matrix.data[0][2] = -2;
    matrix.data[0][3] = -3;
    matrix.data[1][0] = 9;
    matrix.data[1][1] = 6;
    matrix.data[1][2] = 2;
    matrix.data[1][3] = 6;
    matrix.data[2][0] = 0;
    matrix.data[2][1] = -5;
    matrix.data[2][2] = 1;
    matrix.data[2][3] = -5;
    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = 0;
	return (matrix);
}

static t_matrix	matrix_a(void)
{
	t_matrix	matrix;

	matrix = new_matrix(4, 4);
    matrix.data[0][0] = 6;
    matrix.data[0][1] = 4;
    matrix.data[0][2] = 4;
    matrix.data[0][3] = 4;
    matrix.data[1][0] = 5;
    matrix.data[1][1] = 5;
    matrix.data[1][2] = 7;
    matrix.data[1][3] = 6;
    matrix.data[2][0] = 4;
    matrix.data[2][1] = -9;
    matrix.data[2][2] = 3;
    matrix.data[2][3] = -7;
    matrix.data[3][0] = 9;
    matrix.data[3][1] = 1;
    matrix.data[3][2] = 7;
    matrix.data[3][3] = -6;
	return (matrix);
}

int test_is_invertible_matrix(void)
{
    t_matrix	matrix_00;
    t_matrix	matrix_01;
    int			errors;

    matrix_00 = matrix_a();
    matrix_01 = matrix_b();
    errors = 0;
    errors += test_check_double(matrix_is_invertible(matrix_00), TRUE, "is_invertible_matrix_00");
    errors += test_check_double(matrix_is_invertible(matrix_01), FALSE, "is_invertible_matrix_01");
    free_matrix(matrix_00);
    free_matrix(matrix_01);
    if (errors == 0)
        test_success("test_is_invertible_matrix pass!");
    else
        test_failure("test_is_invertible_matrix failed.");
    return (errors);
}
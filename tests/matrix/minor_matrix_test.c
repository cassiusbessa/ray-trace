/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_matrix_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:21:29 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 20:02:34 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static t_matrix matrix_a(void)
{
    t_matrix    matrix;

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
    t_matrix    matrix;
    double         minor;
    double         expected_minor;
    int         errors;

    matrix = matrix_a();
    minor = minor_matrix(matrix, 1, 0);
    expected_minor = 25;
    errors = 0;
    errors += test_check_double(minor, expected_minor, "minor_matrix");
    if (errors)
        test_failure("minor_matrix");
    else
        test_success("minor_matrix");
    free_matrix(matrix);
    return (errors);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normalize_tests.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:29:49 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 23:32:43 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int	test_normalize_vector_4_0_0(void)
{
    t_touple	*vector;
    t_touple	*normalized;
    int			errors;

    errors = 0;
    vector = new_touple(4, 0, 0, FALSE);
    normalized = normalize_vector(vector);
    errors += test_check_double(normalized->x, 1, "normalized.x should be 1");
    errors += test_check_double(normalized->y, 0, "normalized.y should be 0");
    errors += test_check_double(normalized->z, 0, "normalized.z should be 0");
    errors += test_check(normalized->w == 0, "normalized.w should be 0 (vector)");
    free(vector);
    free(normalized);
    if (errors == 0)
        test_success("test_normalize_vector_4_0_0 pass!");
    return (errors);
}

static int	test_normalize_vector_1_2_3(void)
{
    t_touple	*vector;
    t_touple	*normalized;
    int			errors;

    errors = 0;
    vector = new_touple(1, 2, 3, FALSE);
    normalized = normalize_vector(vector);
    errors += test_check_double(normalized->x, 0.26726, "normalized.x should be 0.26726");
    errors += test_check_double(normalized->y, 0.53452, "normalized.y should be 0.53452");
    errors += test_check_double(normalized->z, 0.80178, "normalized.z should be 0.80178");
    errors += test_check(normalized->w == 0, "normalized.w should be 0 (vector)");
    free(vector);
    free(normalized);
    if (errors == 0)
        test_success("test_normalize_vector_1_2_3 pass!");
    return (errors);
}

int all_vector_normalize_tests(void)
{
    int errors;

    errors = 0;
    errors += test_normalize_vector_4_0_0();
    errors += test_normalize_vector_1_2_3();
    return (errors);
}
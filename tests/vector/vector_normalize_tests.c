/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normalize_tests.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:29:49 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:15:10 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int	test_normalize_vector_4_0_0(void)
{
    t_tuple	vector;
    t_tuple	normalized;
    int			errors;

    errors = 0;
    vector = new_tuple(4, 0, 0, FALSE);
    normalized = normalize_vector(vector);
    errors += test_check_double(normalized.x, 1, "normalized.x should be 1");
    errors += test_check_double(normalized.y, 0, "normalized.y should be 0");
    errors += test_check_double(normalized.z, 0, "normalized.z should be 0");
    errors += test_check(normalized.w == 0, "normalized.w should be 0 (vector)");
    if (errors == 0)
        test_success("test_normalize_vector_4_0_0 pass!");
    else
        test_failure("test_normalize_vector_4_0_0 failed.");
    return (errors);
}

static int	test_normalize_vector_1_2_3(void)
{
    t_tuple	vector;
    t_tuple	normalized;
    int			errors;

    errors = 0;
    vector = new_tuple(1, 2, 3, FALSE);
    normalized = normalize_vector(vector);
    errors += test_check_double(normalized.x, 0.26726, "normalized.x should be 0.26726");
    errors += test_check_double(normalized.y, 0.53452, "normalized.y should be 0.53452");
    errors += test_check_double(normalized.z, 0.80178, "normalized.z should be 0.80178");
    errors += test_check(normalized.w == 0, "normalized.w should be 0 (vector)");
    if (errors == 0)
        test_success("test_normalize_vector_1_2_3 pass!");
    else
        test_failure("test_normalize_vector_1_2_3 failed.");
    return (errors);
}

static int  test_magnitude_of_normalized_vector(void)
{
    t_tuple	vector;
    t_tuple	normalized;
    float		magnitude;
    int			errors;

    errors = 0;
    vector = new_tuple(1, 2, 3, FALSE);
    normalized = normalize_vector(vector);
    magnitude = magnitude_of_vector(normalized);
    errors += test_check_double(magnitude, 1, "magnitude should be 1");
    if (errors == 0)
        test_success("test_magnitude_of_normalized_vector pass!");
    else
        test_failure("test_magnitude_of_normalized_vector failed.");
    return (errors);
}

int all_vector_normalize_tests(void)
{
    int errors;

    errors = 0;
    errors += test_normalize_vector_4_0_0();
    errors += test_normalize_vector_1_2_3();
    errors += test_magnitude_of_normalized_vector();
    return (errors);
}
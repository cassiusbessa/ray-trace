/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_magnitude_tests.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:58:31 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:14:14 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int	test_magnitude_of_vector_1_0_0(void)
{
    t_tuple	vector;
    float		magnitude;
    int			errors;

    errors = 0;
    vector = new_tuple(1, 0, 0, FALSE);
    magnitude = magnitude_of_vector(vector);
    errors += test_check_double(magnitude, 1, "magnitude should be 1");
    if (errors == 0)
        test_success("test_magnitude_of_vector_1_0_0 pass!");
    else
        test_failure("test_magnitude_of_vector_1_0_0 failed.");
    return (errors);
}

static int	test_magnitude_of_vector_0_1_0(void)
{
    t_tuple	vector;
    float		magnitude;
    int			errors;

    errors = 0;
    vector = new_tuple(0, 1, 0, FALSE);
    magnitude = magnitude_of_vector(vector);
    errors += test_check_double(magnitude, 1, "magnitude should be 1");
    if (errors == 0)
        test_success("test_magnitude_of_vector_0_1_0 pass!");
    else
        test_failure("test_magnitude_of_vector_0_1_0 failed.");
    return (errors);
}

static int	test_magnitude_of_vector_0_0_1(void)
{
    t_tuple	vector;
    float		magnitude;
    int			errors;

    errors = 0;
    vector = new_tuple(0, 0, 1, FALSE);
    magnitude = magnitude_of_vector(vector);
    errors += test_check_double(magnitude, 1, "magnitude should be 1");
    if (errors == 0)
        test_success("test_magnitude_of_vector_0_0_1 pass!");
    else
        test_failure("test_magnitude_of_vector_0_0_1 failed.");
    return (errors);
}

static int	test_magnitude_of_vector_1_2_3(void)
{
    t_tuple	vector;
    float		magnitude;
    int			errors;

    errors = 0;
    vector = new_tuple(1, 2, 3, FALSE);
    magnitude = magnitude_of_vector(vector);
    errors += test_check_double(magnitude, sqrt(14), "magnitude should be sqrt(14)");
    if (errors == 0)
        test_success("test_magnitude_of_vector_1_2_3 pass!");
    else
        test_failure("test_magnitude_of_vector_1_2_3 failed.");
    return (errors);
}

static int	test_magnitude_of_vector_neg_1_neg_2_neg_3(void)
{
    t_tuple	vector;
    float		magnitude;
    int			errors;

    errors = 0;
    vector = new_tuple(-1, -2, -3, FALSE);
    magnitude = magnitude_of_vector(vector);
    errors += test_check_double(magnitude, sqrt(14), "magnitude should be sqrt(14)");
    if (errors == 0)
        test_success("test_magnitude_of_vector_neg_1_neg_2_neg_3 pass!");
    else
        test_failure("test_magnitude_of_vector_neg_1_neg_2_neg_3 failed.");
    return (errors);
}

int all_vector_magnitude_tests(void)
{
    int	errors;

    errors = 0;
    errors += test_magnitude_of_vector_1_0_0();
    errors += test_magnitude_of_vector_0_1_0();
    errors += test_magnitude_of_vector_0_0_1();
    errors += test_magnitude_of_vector_1_2_3();
    errors += test_magnitude_of_vector_neg_1_neg_2_neg_3();
    return (errors);
}
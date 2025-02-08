/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_op_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:40:07 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 20:40:58 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int test_add_tuples(void)
{
	t_touple	*t1;
	t_touple	*t2;
	t_touple	*result;
	int			errors;

	errors = 0;
	t1 = new_touple(3, -2, 5, TRUE);
	t2 = new_touple(-2, 3, 1, FALSE);
	result = add_touple(t1, t2);
	errors += test_check_double(result->x, 1, "result.x should be 1");
	errors += test_check_double(result->y, 1, "result.y should be 1");
	errors += test_check_double(result->z, 6, "result.z should be 6");
	errors += test_check(result->w == 1, "result.w should be 1 (point)");
	free(t1);
	free(t2);
	free(result);
	if (errors == 0)
		test_success("test_add_tuples pass!");
	return (errors);
}

int test_sub_points(void)
{
	t_touple	*t1;
	t_touple	*t2;
	t_touple	*result;
	int			errors;

	errors = 0;
	t1 = new_touple(3, 2, 1, TRUE);
	t2 = new_touple(5, 6, 7, TRUE);
	result = sub_touple(t1, t2);
	errors += test_check_double(result->x, -2, "result.x should be -2");
	errors += test_check_double(result->y, -4, "result.y should be -4");
	errors += test_check_double(result->z, -6, "result.z should be -6");
	errors += test_check(result->w == 0, "result.w should be 0 (vector)");
	free(t1);
	free(t2);
	free(result);
	if (errors == 0)
		test_success("test_sub_points pass!");
	return (errors);
}

int test_sub_vector_from_point(void)
{
	t_touple	*t1;
	t_touple	*t2;
	t_touple	*result;
	int			errors;

	errors = 0;
	t1 = new_touple(3, 2, 1, TRUE);
	t2 = new_touple(5, 6, 7, FALSE);
	result = sub_touple(t1, t2);
	errors += test_check_double(result->x, -2, "result.x should be -2");
	errors += test_check_double(result->y, -4, "result.y should be -4");
	errors += test_check_double(result->z, -6, "result.z should be -6");
	errors += test_check(result->w == 1, "result.w should be 1 (point)");
	free(t1);
	free(t2);
	free(result);
	if (errors == 0)
		test_success("test_sub_vector_from_point pass!");
	return (errors);
}

int test_sub_vectors(void)
{
	t_touple	*t1;
	t_touple	*t2;
	t_touple	*result;
	int			errors;

	errors = 0;
	t1 = new_touple(3, 2, 1, FALSE);
	t2 = new_touple(5, 6, 7, FALSE);
	result = sub_touple(t1, t2);
	errors += test_check_double(result->x, -2, "result.x should be -2");
	errors += test_check_double(result->y, -4, "result.y should be -4");
	errors += test_check_double(result->z, -6, "result.z should be -6");
	errors += test_check(result->w == 0, "result.w should be 0 (vector)");
	free(t1);
	free(t2);
	free(result);
	if (errors == 0)
		test_success("test_sub_vectors pass!");
	return (errors);
}

int test_sub_vector_from_zero_vector(void)
{
	t_touple	*t1;
	t_touple	*t2;
	t_touple	*result;
	int			errors;

	errors = 0;
	t1 = new_touple(0, 0, 0, FALSE);
	t2 = new_touple(1, -2, 3, FALSE);
	result = sub_touple(t1, t2);
	errors += test_check_double(result->x, -1, "result.x should be -1");
	errors += test_check_double(result->y, 2, "result.y should be 2");
	errors += test_check_double(result->z, -3, "result.z should be -3");
	errors += test_check(result->w == 0, "result.w should be 0 (vector)");
	free(t1);
	free(t2);
	free(result);
	if (errors == 0)
		test_success("test_sub_vector_from_zero_vector pass!");
	return (errors);
}
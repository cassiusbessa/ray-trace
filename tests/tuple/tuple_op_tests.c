/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_op_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:52:18 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:22:02 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../tests.h"

int test_add_tuples(void)
{
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	result;
	int			errors;

	errors = 0;
	t1 = new_tuple(3, -2, 5, TRUE);
	t2 = new_tuple(-2, 3, 1, FALSE);
	result = add_tuples(t1, t2);
	errors += test_check_double(result.x, 1, "result.x should be 1");
	errors += test_check_double(result.y, 1, "result.y should be 1");
	errors += test_check_double(result.z, 6, "result.z should be 6");
	errors += test_check(result.w == 1, "result.w should be 1 (point)");
	if (errors == 0)
		test_success("test_add_tuples pass!");
	else
		test_failure("test_add_tuples failed.");
	return (errors);
}

int test_sub_points(void)
{
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	result;
	int			errors;

	errors = 0;
	t1 = new_tuple(3, 2, 1, TRUE);
	t2 = new_tuple(5, 6, 7, TRUE);
	result = sub_tuples(t1, t2);
	errors += test_check_double(result.x, -2, "result.x should be -2");
	errors += test_check_double(result.y, -4, "result.y should be -4");
	errors += test_check_double(result.z, -6, "result.z should be -6");
	errors += test_check(result.w == 0, "result.w should be 0 (vector)");
	if (errors == 0)
		test_success("test_sub_points pass!");
	else
		test_failure("test_sub_points failed.");
	return (errors);
}

int test_sub_vector_from_point(void)
{
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	result;
	int			errors;

	errors = 0;
	t1 = new_tuple(3, 2, 1, TRUE);
	t2 = new_tuple(5, 6, 7, FALSE);
	result = sub_tuples(t1, t2);
	errors += test_check_double(result.x, -2, "result.x should be -2");
	errors += test_check_double(result.y, -4, "result.y should be -4");
	errors += test_check_double(result.z, -6, "result.z should be -6");
	errors += test_check(result.w == 1, "result.w should be 1 (point)");
	if (errors == 0)
		test_success("test_sub_vector_from_point pass!");
	else
		test_failure("test_sub_vector_from_point failed.");
	return (errors);
}

int test_sub_vectors(void)
{
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	result;
	int			errors;

	errors = 0;
	t1 = new_tuple(3, 2, 1, FALSE);
	t2 = new_tuple(5, 6, 7, FALSE);
	result = sub_tuples(t1, t2);
	errors += test_check_double(result.x, -2, "result.x should be -2");
	errors += test_check_double(result.y, -4, "result.y should be -4");
	errors += test_check_double(result.z, -6, "result.z should be -6");
	errors += test_check(result.w == 0, "result.w should be 0 (vector)");
	if (errors == 0)
		test_success("test_sub_vectors pass!");
	else
		test_failure("test_sub_vectors failed.");
	return (errors);
}

int test_sub_vector_from_zero_vector(void)
{
	t_tuple	t1;
	t_tuple	t2;
	t_tuple	result;
	int			errors;

	errors = 0;
	t1 = new_tuple(0, 0, 0, FALSE);
	t2 = new_tuple(1, -2, 3, FALSE);
	result = sub_tuples(t1, t2);
	errors += test_check_double(result.x, -1, "result.x should be -1");
	errors += test_check_double(result.y, 2, "result.y should be 2");
	errors += test_check_double(result.z, -3, "result.z should be -3");
	errors += test_check(result.w == 0, "result.w should be 0 (vector)");
	if (errors == 0)
		test_success("test_sub_vector_from_zero_vector pass!");
	else
		test_failure("test_sub_vector_from_zero_vector failed.");
	return (errors);
}
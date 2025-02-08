/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:29:08 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 20:28:58 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "tests.h"

int	test_tuple_as_point(void)
{
	t_touple	*point;
	int			errors;

	errors = 0;
	point = new_touple(4.3, -4.2, 3.1, TRUE);
	if (!point)
		return (ft_printf("❌ Failed to allocate memory for the tuple.\n"));
	errors += test_check_double(point->x, 4.3, "point.x should be 4.3");
	errors += test_check_double(point->y, -4.2, "point.y should be -4.2");
	errors += test_check_double(point->z, 3.1, "point.z should be 3.1");
	errors += test_check(point->w == 1, "point.w should be 1 (point)");
	errors += test_check(point->w == TRUE, "point should be a point");
	errors += test_check(point->w != FALSE, "point should not be a vector");
	free(point);
	if (errors == 0)
		test_success("test_tuple_as_point pass!");
	return (errors);
}

int	test_tuple_as_vector(void)
{
	t_touple	*vector;
	int			errors;

	errors = 0;
	vector = new_touple(4.3, -4.2, 3.1, FALSE);
	if (!vector)
		return (ft_printf("❌ Failed to allocate memory for the tuple.\n"));
	errors += test_check_double(vector->x, 4.3, "vector.x should be 4.3");
	errors += test_check_double(vector->y, -4.2, "vector.y should be -4.2");
	errors += test_check_double(vector->z, 3.1, "vector.z should be 3.1");
	errors += test_check(vector->w == 0, "vector.w should be 0 (vector)");
	errors += test_check(vector->w == FALSE, "vector should be a vector");
	errors += test_check(vector->w != TRUE, "vector should not be a point");
	free(vector);
	if (errors == 0)
		test_success("test_tuple_as_vector pass!");
	return (errors);
}

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

int	main(void)
{
	int	errors;

	errors = 0;
	errors += test_tuple_as_point();
	errors += test_tuple_as_vector();
	errors += test_add_tuples();
	if (errors == 0)
		ft_printf("\n🎉 All tests fine!\n");
	else
		ft_printf("\n❌ %d tests failed.\n", errors);
	return (errors);
}

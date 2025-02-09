/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_common_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:29:08 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/09 01:25:16 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	test_tuple_as_point(void)
{
	t_tuple	*point;
	int			errors;

	errors = 0;
	point = new_tuple(4.3, -4.2, 3.1, TRUE);
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
	t_tuple	*vector;
	int			errors;

	errors = 0;
	vector = new_tuple(4.3, -4.2, 3.1, FALSE);
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


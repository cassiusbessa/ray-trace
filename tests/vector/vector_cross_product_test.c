/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cross_product_test.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 00:53:22 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/16 01:17:43 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int	test_cross_product_1_2_3_2_3_4(void)
{
	t_tuple	vector1;
	t_tuple	vector2;
	t_tuple	cross;
	int		errors;

	errors = 0;
	vector1 = new_tuple(1, 2, 3, FALSE);
	vector2 = new_tuple(2, 3, 4, FALSE);
	cross = vector_cross_product(vector1, vector2);
	errors += test_check_double(cross.x, -1, "cross.x should be -1");
	errors += test_check_double(cross.y, 2, "cross.y should be 2");
	errors += test_check_double(cross.z, -1, "cross.z should be -1");
	errors += test_check(cross.w == 0, "cross.w should be 0 (vector)");
	if (errors == 0)
		test_success("test_cross_product_1_2_3_2_3_4 pass!");
	else
		test_failure("test_cross_product_1_2_3_2_3_4 failed.");
	return (errors);
}

static int	test_cross_product_2_3_4_1_2_3(void)
{
	t_tuple	vector1;
	t_tuple	vector2;
	t_tuple	cross;
	int		errors;

	errors = 0;
	vector1 = new_tuple(2, 3, 4, FALSE);
	vector2 = new_tuple(1, 2, 3, FALSE);
	cross = vector_cross_product(vector1, vector2);
	errors += test_check_double(cross.x, 1, "cross.x should be 1");
	errors += test_check_double(cross.y, -2, "cross.y should be -2");
	errors += test_check_double(cross.z, 1, "cross.z should be 1");
	errors += test_check(cross.w == 0, "cross.w should be 0 (vector)");
	if (errors == 0)
		test_success("test_cross_product_2_3_4_1_2_3 pass!");
	else
		test_failure("test_cross_product_2_3_4_1_2_3 failed.");
	return (errors);
}

int	all_vector_cross_product_tests(void)
{
	int errors;

	errors = 0;
	errors += test_cross_product_1_2_3_2_3_4();
	errors += test_cross_product_2_3_4_1_2_3();
	if (errors == 0)
		ft_printf("\n🎉 All vector cross product tests fine!\n");
	else
		ft_printf("\n❌ %d vector cross product tests failed.\n", errors);
	return (errors);
}
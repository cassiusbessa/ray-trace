/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:43:28 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 22:04:13 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	int	errors;

	errors = 0;
	errors += test_tuple_as_point();
	errors += test_tuple_as_vector();
	errors += test_add_tuples();
	errors += test_sub_points();
	errors += test_sub_vector_from_point();
	errors += test_sub_vectors();
    errors += test_sub_vector_from_zero_vector();
    errors += test_multiply_tuple_by_scalar();
    errors += test_multiply_tuple_by_fraction();
    errors += all_tuple_magnitude_tests();
	if (errors == 0)
		ft_printf("\n🎉 All tests fine!\n");
	else
		ft_printf("\n❌ %d tests failed.\n", errors);
	return (errors);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:54:54 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/15 09:40:46 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int    main(void)
{
    int errors;

    errors = 0;
    errors += tuple_tests();
    errors += vector_tests();
    errors += all_rgb_tests();
    errors += canvas_tests();
    errors += all_matrix_tests();
    errors += all_transformation_tests();
    errors += run_test_ray();
    errors += run_test_sphere();
    errors += run_test_intersections();
    if (errors == 0)
        ft_printf("\n🎉 All tests fine!\n");
    else
        ft_printf("\n❌ %d tests failed.\n", errors);
    return (0);
}
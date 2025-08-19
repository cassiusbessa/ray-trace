/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:54:54 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/19 07:52:07 by emorshhe         ###   ########.fr       */
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
    errors += run_test_hit();
    errors += run_ray_tests();
    errors += run_sphere_transform_tests();
    errors += run_normal_tests();
    errors += run_reflect_tests();
    errors += run_light_tests();
    errors += run_material_tests();
    errors += run_lighting_tests();
    if (errors == 0)
        ft_printf("\n🎉 All tests fine!\n");
    else
        ft_printf("\n❌ %d tests failed.\n", errors);
    return (0);
}
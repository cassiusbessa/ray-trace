/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:57:32 by cassius           #+#    #+#             */
/*   Updated: 2025/08/25 23:38:47 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"


static int test_lighting_eye_between_light_and_surface(void)
{
    int errors = 0;

    t_material m = new_material_default();
    t_tuple position = point(0, 0, 0);
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1); // normal do ponto de teste
    t_point_light light = new_point_light(point(0, 0, -10), new_rgb(1, 1, 1));

    // Passa 0 como in_shadow
    t_rgb result = lighting(m, light, position, eyev, normalv, 0);

    errors += test_check(equal_rgb(result, new_rgb(1.9, 1.9, 1.9)),
        "Lighting with eye between light and surface should be (1.9, 1.9, 1.9)");

    if (errors)
        test_failure("Lighting test (eye between light and surface) failed");
    else
        test_success("Lighting test (eye between light and surface) passed");

    return errors;
}

static int test_lighting_eye_offset_45(void)
{
    int errors = 0;

    t_material m = new_material_default();
    t_tuple position = point(0, 0, 0);
    t_tuple eyev = vector(0, sqrtf(2)/2, -sqrtf(2)/2);
    t_tuple normalv = vector(0, 0, -1); // normal do ponto de teste
    t_point_light light = new_point_light(point(0, 0, -10), new_rgb(1, 1, 1));

    // Passa 0 como in_shadow
    t_rgb result = lighting(m, light, position, eyev, normalv, 0);

    errors += test_check(equal_rgb(result, new_rgb(1.0, 1.0, 1.0)),
        "Lighting with eye offset 45° should be (1.0, 1.0, 1.0)");

    if (errors)
        test_failure("Lighting test (eye offset 45°) failed");
    else
        test_success("Lighting test (eye offset 45°) passed");

    return errors;
}

int run_lighting_tests(void)
{
    int errors = 0;

    errors += test_lighting_eye_between_light_and_surface();
    errors += test_lighting_eye_offset_45();

    if (errors)
        test_failure("Lighting tests failed");
    else
        test_success("All lighting tests passed");

    return errors;
}

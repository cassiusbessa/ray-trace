/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:26:16 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 21:44:56 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_new_point_light(void)
{
    t_tuple position = new_tuple(1, 2, 3, TRUE);
    t_rgb intensity = new_rgb(255, 255, 255);
    t_point_light light = new_point_light(position, intensity);
    int errors = 0;

    errors += test_check(equal_tuples(light.position, position), "Point light position should match");
    errors += test_check(equal_rgb(light.intensity, intensity), "Point light intensity should match");
    if (errors)
        test_failure("Point light tests failed");
    else
        test_success("Point light tests passed");
    return (errors);
}

int run_light_tests(void)
{
    int errors = 0;

    errors += test_new_point_light();
    if (errors)
        test_failure("Point light tests failed");
    else
        test_success("Point light tests passed");
    return (errors);
}
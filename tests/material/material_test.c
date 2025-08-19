/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:57:32 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 22:22:08 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_default_material_creation(void)
{
    int errors;
    t_material material;

    errors = 0;
    material = new_material_default();

    errors += test_check(equal_rgb(material.color, new_rgb(1, 1, 1)), "Default material color should be white");
    errors += test_check_double(material.ambient, 0.1f, "Default material ambient should be 0.1");
    errors += test_check_double(material.diffuse, 0.9f, "Default material diffuse should be 0.9");
    errors += test_check_double(material.specular, 0.9f, "Default material specular should be 0.9");
    errors += test_check_double(material.shininess, 200.0f, "Default material shininess should be 200.0");
    if (errors)
        test_failure("Default material creation failed");
    else
        test_success("Default material creation succeeded");
    return errors;
}

int run_material_tests(void)
{
    int errors = 0;

    errors += test_default_material_creation();
    if (errors)
        test_failure("Material tests failed");
    else
        test_success("All material tests passed");
    return(errors);
}
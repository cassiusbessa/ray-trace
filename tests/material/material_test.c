/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:57:32 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 07:46:40 by emorshhe         ###   ########.fr       */
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

static int test_sphere_assign_material(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0, 0, 0), 1);
    t_material m = new_material_default();

    // Alterando o material
    m.ambient = 1.0f;
    s.material = m;

    errors += test_check_double(s.material.ambient, 1.0f, "Sphere material should accept assigned ambient");

    if (errors)
        test_failure("Sphere material assignment test failed");
    else
        test_success("Sphere material assignment test passed");
    return errors;
}

int run_material_tests(void)
{
    int errors = 0;

    errors += test_default_material_creation();
    errors += test_sphere_assign_material();

    if (errors)
        test_failure("Sphere material tests failed");
    else
        test_success("All sphere material tests passed");
    return errors;
}
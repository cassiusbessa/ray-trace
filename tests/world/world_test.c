/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:12:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 21:06:01 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_world_creation(void)
{
    t_world world;
    int errors = 0;

    world = new_world();
    errors += test_check(world.objects->head == NULL, "World should have no objects initially");
    errors += test_check(world.objects->count == 0, "World should have no objects initially");
    errors += test_check(world.lights->head == NULL, "World should have no lights initially");
    errors += test_check(world.lights->count == 0, "World should have no lights initially");
    if (errors)
        test_failure("World creation failed");
    else
        test_success("World creation succeeded");
    return (errors);
}

static int test_world_default_creation(void)
{
    t_world world;
    int errors = 0;

    world = default_world();
    errors += test_check(world.objects != NULL, "World should have objects initially");
    errors += test_check(world.objects->count == 2, "World should have two objects initially");
    errors += test_check(world.objects->head != NULL, "World should have an object initially");
    errors += test_check(world.objects->head->next != NULL, "World should have an other object initially");
    errors += test_check(world.objects->head->next != world.objects->head, "World should have two different objects initially");
    errors += test_check(world.lights != NULL, "World should have a light initially");
    errors += test_check(world.lights->count == 1, "World should have a light initially");
    errors += test_check(world.lights->head != NULL, "World should have a light initially");
    if (errors)
        test_failure("World default creation failed");
    else
        test_success("World default creation succeeded");
    return (errors);
}

int run_world_tests(void)
{
    int errors = 0;

    errors += test_world_creation();
    errors += test_world_default_creation();

    if (errors)
        test_failure("World tests failed");
    else
        test_success("World tests passed");
    return (errors);
}
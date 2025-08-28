/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:12:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 22:52:04 by cassius          ###   ########.fr       */
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
    free_world(&world);
    if (errors)
        test_failure("World default creation failed");
    else
        test_success("World default creation succeeded");
    return (errors);
}

static int test_intersect_world_with_ray(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    t_intersection_list *xs = intersect_world(&w, &r);

    t_intersection_node *n = xs->head;

    // Reset para percorrer novamente e fazer os testes
    n = xs->head;
    errors += test_check(xs->count == 4, "xs.count should be 4");

    if (n)
    {
        errors += test_check(float_equal(n->t, 4.0f),  "xs[0].t = 4");
        n = n->next;
    }
    if (n)
    {
        errors += test_check(float_equal(n->t, 4.5f),  "xs[1].t = 4.5");
        n = n->next;
    }
    if (n)
    {
        errors += test_check(float_equal(n->t, 5.5f),  "xs[2].t = 5.5");
        n = n->next;
    }
    if (n)
    {
        errors += test_check(float_equal(n->t, 6.0f),  "xs[3].t = 6");
    }

    free_intersection_list(xs);
    free_world(&w);

    if (errors) test_failure("Intersect world with ray failed");
    else        test_success("Intersect world with ray succeeded");

    return errors;
}

static int  is_shadowed_point_world_test(void)
{
    int errors = 0;

    t_world w = default_world();
    t_tuple p = point(0, 10, 0);
    errors += test_check(!is_shadowed(&w, p), "Point (0, 10, 0) should not be in shadow");

    if (errors)
        test_failure("Is shadowed point world test failed");
    else
        test_success("Is shadowed point world test passed");

    return errors;
}

int run_world_tests(void)
{
    int errors = 0;

    errors += test_world_creation();
    errors += test_world_default_creation();
    errors += test_intersect_world_with_ray();
    errors += is_shadowed_point_world_test();
    if (errors)
        test_failure("World tests failed");
    else
        test_success("World tests passed");
    return (errors);
}
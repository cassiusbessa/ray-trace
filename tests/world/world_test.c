/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:12:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 20:32:37 by emorshhe         ###   ########.fr       */
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


static int test_prepare_computations_basic(void)
{
    int errors = 0;

    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    // shape ← sphere()
    t_sphere *s = (t_sphere *)malloc(sizeof(t_sphere));
    *s = new_sphere(point(0,0,0), 1.0f);
    t_object o; o.type = SPHERE; o.data = s;

    // i ← intersection(4, shape)
    t_simple_intersection i = make_simple_intersection(4.0f, &o);

    // comps ← prepare_computations(i, r)
    t_comps comps = prepare_computations(i, r);

    errors += test_check(float_equal(comps.t, i.t), "comps.t = i.t");
    errors += test_check(comps.object == i.object, "comps.object = i.object");
    errors += test_check(equal_tuples(comps.point, point(0,0,-1)), "comps.point = (0,0,-1)");
    errors += test_check(equal_tuples(comps.eyev,  vector(0,0,-1)), "comps.eyev = (0,0,-1)");
    errors += test_check(equal_tuples(comps.normalv, vector(0,0,-1)), "comps.normalv = (0,0,-1)");

    free(s);

    if (errors) test_failure("prepare_computations basic failed");
    else        test_success("prepare_computations basic succeeded");
    return errors;
}


static int test_prepare_computations_inside(void)
{
    int errors = 0;

    t_ray r = create_ray(point(0, 0, 0), vector(0, 0, 1)); // começa dentro
    t_sphere *s = (t_sphere *)malloc(sizeof(t_sphere));
    *s = new_sphere(point(0,0,0), 1.0f);
    t_object o; o.type = SPHERE; o.data = s;

    t_simple_intersection i = make_simple_intersection(1.0f, &o);
    t_comps comps = prepare_computations(i, r);

    errors += test_check(comps.inside == TRUE, "comps.inside = TRUE");
    errors += test_check(equal_tuples(comps.point, point(0,0,1)), "point = (0,0,1)");
    errors += test_check(equal_tuples(comps.normalv, vector(0,0,-1)), "normal inverted to (0,0,-1)");

    free(s);

    if (errors) test_failure("prepare_computations inside failed");
    else        test_success("prepare_computations inside succeeded");
    return errors;
}

int run_world_tests(void)
{
    int errors = 0;

    errors += test_world_creation();
    errors += test_world_default_creation();
    errors += test_intersect_world_with_ray();
    errors += test_prepare_computations_basic();
    errors += test_prepare_computations_inside();


    if (errors)
        test_failure("World tests failed");
    else
        test_success("World tests passed");
    return (errors);
}
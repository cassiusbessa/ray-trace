#include "../tests.h"

static int test_color_ray_misses(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 1, 0));

    t_rgb c = color_at(&w, r);


    errors += test_check(equal_rgb(c, new_rgb(0, 0, 0)),
                         "Color mismatch when ray misses");
    if (errors)
        test_failure("Ray misses test failed\n");


    free_world(&w);
    return errors;
}

static int test_color_ray_hits(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    t_rgb c = color_at(&w, r);

    errors += test_check(equal_rgb(c, new_rgb(0.38066f, 0.47583f, 0.2855f)),
                         "Color mismatch when ray hits");
    if (errors)
        test_failure("Ray hits test failed\n");

    free_world(&w);
    return errors;
}

static int test_color_intersection_behind(void)
{
    int errors = 0;
    t_world w = default_world();

    // Configura cores e materiais
    t_object *outer = &w.objects->head->object;
    ((t_sphere *)outer->data)->material.ambient = 1;
    t_object *inner = &w.objects->head->next->object;
    ((t_sphere *)inner->data)->material.ambient = 1;

    // Raio dentro da esfera externa, mirando na interna
    t_ray r = create_ray(point(0, 0, 0.75), vector(0, 0, -1));

    t_rgb c = color_at(&w, r);

    errors += test_check(equal_rgb(c, ((t_sphere *)inner->data)->material.color),
                         "Color mismatch when hit is behind");
    if (errors)
        test_failure("Color intersection behind test failed\n");

    free_world(&w);
    return errors;
}


int run_test_color_at(void)
{
    int errors = 0;

    errors += test_color_ray_misses();
    errors += test_color_ray_hits();
    errors += test_color_intersection_behind();

    if (errors)
        test_failure("Color at ray tests failed\n");
    else
        test_success("Color at ray tests passed\n");

    return errors;
}
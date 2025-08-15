#include "../tests.h"

static int test_ray_translation(void)
{
    int errors = 0;
    t_ray r = create_ray(point(1, 2, 3), vector(0, 1, 0));
    t_matrix m = translation_matrix(3, 4, 5);
    t_ray r2 = transform_ray(r, m);

    errors += test_check(equal_tuples(r2.origin, point(4, 6, 8)), "Ray translation: origin check");
    errors += test_check(equal_tuples(r2.direction, vector(0, 1, 0)), "Ray translation: direction check");

    return errors;
}

static int test_ray_scaling(void)
{
    int errors = 0;
    t_ray r = create_ray(point(1, 2, 3), vector(0, 1, 0));
    t_matrix m = scaling_matrix(2, 3, 4);
    t_ray r2 = transform_ray(r, m);

    errors += test_check(equal_tuples(r2.origin, point(2, 6, 12)), "Ray scaling: origin check");
    errors += test_check(equal_tuples(r2.direction, vector(0, 3, 0)), "Ray scaling: direction check");

    return errors;
}

int run_ray_tests(void)
{
    int errors;

    errors = 0;
    errors += test_ray_translation();
    errors += test_ray_scaling();

    if (errors)
        test_failure("Ray transformation tests failed");
    else
        test_success("Ray transformation tests passed");
    
    return errors;
}


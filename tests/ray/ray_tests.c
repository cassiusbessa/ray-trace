#include "../tests.h"

static int test_ray_creation_and_equality(void)
{
    int errors = 0;
    t_ray ray;
    t_tuple origin;
    t_tuple direction;

    origin = point(1, 2, 3);
    direction = vector(4, 5, 6);

    ray = create_ray(origin, direction);
    errors += test_check(equal_tuples(ray.origin, origin), "Ray origin should match the input point");
    errors += test_check(equal_tuples(ray.direction, direction), "Ray direction should match the input vector");

    t_ray ray2 = create_ray(point(1, 2, 3), vector(4, 5, 6));
    errors += test_check(equal_rays(ray, ray2), "Two rays with same origin and direction should be equal");

    t_ray ray3 = create_ray(point(1, 2, 3), vector(7, 8, 9));
    errors += test_check(!equal_rays(ray, ray3), "Rays with different directions should not be equal");

    return errors;
}

static int test_ray_position(void)
{
    int errors = 0;
    t_ray r = create_ray(point(2, 3, 4), vector(1, 0, 0));
    t_tuple p;

    p = ray_position(r, 0);
    errors += test_check(equal_tuples(p, point(2, 3, 4)), "position at t=0 should be the origin of the ray");

    p = ray_position(r, 1);
    errors += test_check(equal_tuples(p, point(3, 3, 4)), "position at t=1 should be one unit in the direction of the ray");

    p = ray_position(r, -1);
    errors += test_check(equal_tuples(p, point(1, 3, 4)), "position at t=-1 should be one unit in the opposite direction of the ray");

    p = ray_position(r, 2.5);
    errors += test_check(equal_tuples(p, point(4.5, 3, 4)), "position at t=2.5 should be correct");

    return errors;
}

int run_test_ray(void)
{
    int errors = 0;

    errors += test_ray_creation_and_equality();
    errors += test_ray_position();

    if (errors == 0)
        printf("\n🎉 Ray tests fine!\n");
    else
        printf("\n❌ Ray tests failed.\n");

    return errors;
}

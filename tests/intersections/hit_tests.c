#include "../tests.h"

static int test_hit_all_positive(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, 1.0f, 1.0f, &s);
    t_intersection i2 = new_intersection(1, 2.0f, 2.0f, &s);
    
    t_intersection list[2] = { i2, i1 };
    t_intersections xs = intersections_create(2, list);


    t_intersection i = hit(xs);

    errors += test_check(equal_intersections(i, i1), "Hit should return the smallest positive t");

    free(xs.list);
    return errors;
}

static int test_hit_some_negative(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, -1.0f, -1.0f, &s);
    t_intersection i2 = new_intersection(1, 1.0f, 1.0f, &s);

    t_intersection list[2] = { i2, i1 };
    t_intersections xs = intersections_create(2, list);

    t_intersection i = hit(xs);

    errors += test_check(equal_intersections(i, i2), "Hit should ignore negative t and return positive");

    free(xs.list);
    return errors;
}

static int test_hit_all_negative(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, -2.0f, -2.0f, &s);
    t_intersection i2 = new_intersection(1, -1.0f, -1.0f, &s);
    t_intersection list[2] = { i2, i1 };
    t_intersections xs = intersections_create(2, list);


    t_intersection i = hit(xs);

    errors += test_check(i.count == 0, "Hit should return no intersection when all t are negative");

    free(xs.list);
    return errors;
}

static int test_hit_lowest_nonnegative(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, 5.0f, 5.0f, &s);
    t_intersection i2 = new_intersection(1, 7.0f, 7.0f, &s);
    t_intersection i3 = new_intersection(1, -3.0f, -3.0f, &s);
    t_intersection i4 = new_intersection(1, 2.0f, 2.0f, &s);

    t_intersection list[4] = { i1, i2, i3, i4 };
    t_intersections xs = intersections_create(4, list);


    t_intersection i = hit(xs);

    errors += test_check(equal_intersections(i, i4), "Hit should return the lowest nonnegative t");

    free(xs.list);
    return errors;
}
int run_test_hit(void)
{
    int errors = 0;
    errors += test_hit_all_positive();
    errors += test_hit_some_negative();
    errors += test_hit_all_negative();
    errors += test_hit_lowest_nonnegative();

    if (errors)
        test_failure("Hit tests failed");
    else
        test_success("Hit tests passed");

    return errors;
}

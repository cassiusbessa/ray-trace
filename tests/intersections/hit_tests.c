#include "../tests.h"

static int test_hit_all_positive(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, 1.0f, 1.0f, &s);
    t_intersection i2 = new_intersection(1, 2.0f, 2.0f, &s);
    t_intersection_list *l = new_intersection_list();
    
    add_intersection_to_list(l, i1);
    add_intersection_to_list(l, i2);


    t_intersection_node *i = hit(*l);

    errors += test_check_double(i->t, 1.0f, "Hit should return the smallest positive t");

    free_intersection_list(l);
    return errors;
}

static int test_hit_some_negative(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, -1.0f, -1.0f, &s);
    t_intersection i2 = new_intersection(1, 1.0f, 1.0f, &s);
    t_intersection_list *l = new_intersection_list();

    add_intersection_to_list(l, i1);
    add_intersection_to_list(l, i2);

    t_intersection_node *i = hit(*l);

    errors += test_check_double(i->t, 1.0f, "Hit should return the smallest positive t");

    free_intersection_list(l);
    return errors;
}

static int test_hit_all_negative(void)
{
    int errors = 0;
    t_sphere s = new_sphere(point(0,0,0), 1);
    t_intersection i1 = new_intersection(1, -2.0f, -2.0f, &s);
    t_intersection i2 = new_intersection(1, -1.0f, -1.0f, &s);
    t_intersection_list *l = new_intersection_list();

    add_intersection_to_list(l, i1);
    add_intersection_to_list(l, i2);

    t_intersection_node *i = hit(*l);

    errors += test_check(i == NULL, "Hit should return no intersection when all t are negative");

    free_intersection_list(l);
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

    t_intersection_list *l = new_intersection_list();
    add_intersection_to_list(l, i1);
    add_intersection_to_list(l, i2);
    add_intersection_to_list(l, i3);
    add_intersection_to_list(l, i4);

    t_intersection_node *i = hit(*l);

    errors += test_check_double(i->t, 2.0f, "Hit should return the lowest nonnegative t");

    free_intersection_list(l);
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

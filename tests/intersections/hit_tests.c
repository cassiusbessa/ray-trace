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


static int test_hit_should_offset_point_case(void)
{
    int errors = 0;

    // Given
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    // criar uma esfera como t_object
    t_sphere sphere_data = new_sphere(point(0, 0, 0), 1.0f);
    t_object sphere_obj = new_object(SPHERE, &sphere_data);

    // aplicar a transformação translation(0, 0, 1)
    set_object_transform(&sphere_obj, translation_matrix(0, 0, 1));

    // criar a interseção (t=5)
    t_intersection_node i;
    i.t = 5;
    i.object = &sphere_obj;
    i.next = NULL;

    // When
    t_comps comps = prepare_computations(i, r);

    // Then
    errors += test_check(comps.over_point.z < -EPSILON / 2,
        "comps.over_point.z should be less than -EPSILON/2");
    errors += test_check(comps.point.z > comps.over_point.z,
        "comps.point.z should be greater than comps.over_point.z");

    return errors;
}

int run_test_hit(void)
{
    int errors = 0;
    errors += test_hit_all_positive();
    errors += test_hit_some_negative();
    errors += test_hit_all_negative();
    errors += test_hit_lowest_nonnegative();
    errors += test_hit_should_offset_point_case();

    if (errors)
        test_failure("Hit tests failed");
    else
        test_success("Hit tests passed");

    return errors;
}
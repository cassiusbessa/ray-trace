#include "../tests.h"


// ====================== TESTES ======================

// 1️⃣ Testa criação de interseção individual
static int test_intersection_encapsulates_t_and_object(void)
{
    int errors = 0;

    t_sphere s = new_sphere(point(0, 0, 0), 1.0f);

    t_intersection i = new_intersection(1, 3.5f, 0.0f, (void *)&s);

    errors += test_check_double(i.enter, 3.5f, "Intersection should store t value");
    errors += test_check(i.object == (void *)&s, "Intersection should store object pointer");
    errors += test_check(i.count == 1, "Intersection count should be 1");

    return errors;
}

// 2️⃣ Testa agregação de interseções
static int test_aggregating_intersections(void)
{
    int errors = 0;

    t_sphere s = new_sphere(point(0, 0, 0), 1.0f);

    t_intersection i1 = new_intersection(1, 1.0f, 0.0f, (void *)&s);
    t_intersection i2 = new_intersection(1, 2.0f, 0.0f, (void *)&s);

    t_intersections xs = intersections(i1, i2);

    errors += test_check(xs.count == 2, "Intersections count should be 2");
    errors += test_check_double(xs.list[0].enter, 1.0f, "First intersection t should be 1.0");
    errors += test_check_double(xs.list[1].enter, 2.0f, "Second intersection t should be 2.0");

    free(xs.list);
    return errors;
}

// 3️⃣ Testa se intersect_ray_sphere define corretamente o objeto
static int test_intersect_sets_object(void)
{
    int errors = 0;

    t_sphere s = new_sphere(point(0, 0, 0), 1.0f);
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    t_intersection i1 = intersect_ray_sphere(r, &s); // primeiro hit
    t_intersection i2 = intersect_ray_sphere(r, &s); // segundo hit ou duplicado para tangente

    t_intersections xs = intersections(i1, i2);

    errors += test_check(xs.count == 2, "Intersections count should be 2");
    errors += test_check(xs.list[0].object == (void *)&s, "First intersection object should be s");
    errors += test_check(xs.list[1].object == (void *)&s, "Second intersection object should be s");

    free(xs.list);
    return errors;
}

// ====================== RUNNER ======================

int run_test_intersections(void)
{
    int errors = 0;

    errors += test_intersection_encapsulates_t_and_object();
    errors += test_aggregating_intersections();
    errors += test_intersect_sets_object();

    if (errors == 0)
        test_success("All intersection tests passed!");
    else
        test_failure("Some intersection tests failed.");

    return errors;
}

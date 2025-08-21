#include "../tests.h"

static int test_sphere_default_transform(void)
{
    int errors = 0;

    t_sphere s_data = new_sphere(point(0, 0, 0), 1.0f);

    t_object s_obj;
    s_obj.type = SPHERE;
    s_obj.data = &s_data;  // ponteiro para variável local

    errors += test_check(
        equal_matrix(((t_sphere *)s_obj.data)->transform, identity_matrix(4)),
        "Default sphere transform should be identity"
    );

    return errors;
}

// Testa a configuração de uma transformação personalizada via objeto
static int test_sphere_set_transform(void)
{
    int errors = 0;

    t_sphere *s_data = malloc(sizeof(t_sphere));
    *s_data = new_sphere(point(0, 0, 0), 1.0f);

    t_object s_obj;
    s_obj.type = SPHERE;
    s_obj.data = s_data;

    t_matrix t = translation_matrix(2, 3, 4);
    set_object_transform(&s_obj, t);

    errors += test_check(
        equal_matrix(((t_sphere *)s_obj.data)->transform, t),
        "Sphere transform should be updated after set_object_transform"
    );

    free(s_data);
    return errors;
}

static int test_intersect_scaled_sphere(void)
{
    int errors = 0;
    t_object s_obj;
    t_sphere s_data = new_sphere(point(0, 0, 0), 1.0f);
    t_intersection_list *l;

    s_obj.type = SPHERE;
    s_obj.data = &s_data;
    set_object_transform(&s_obj, scaling_matrix(2, 2, 2));
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    l = intersect(r, &s_obj);
    errors += test_check(l->count == 2, "Scaled sphere should produce 2 intersections");
    errors += test_check(float_equal(l->head->t, 3.0f), "Intersection enter t = 3");
    errors += test_check(float_equal(l->tail->t, 7.0f), "Intersection exit t = 7");
    free_intersection_list(l);
    return errors;
}

static int test_intersect_translated_sphere(void)
{
    int errors = 0;
    t_object s_obj;
    t_sphere s_data = new_sphere(point(0, 0, 0), 1.0f);
    t_intersection_list *l;

    s_obj.type = SPHERE;
    s_obj.data = &s_data;
    set_object_transform(&s_obj, translation_matrix(5, 0, 0));
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    l = intersect(r, &s_obj);
    errors += test_check(l->count == 0, "Translated sphere should produce 0 intersections");
    free_intersection_list(l);
    return errors;
}

// Função para rodar todos os testes de sphere + transform + intersect
int run_sphere_transform_tests(void)
{
    int errors = 0;

    errors += test_sphere_default_transform();
    errors += test_sphere_set_transform();
    errors += test_intersect_scaled_sphere();
    errors += test_intersect_translated_sphere();

    if (errors)
        test_failure("Sphere transform tests failed");
    else
        test_success("Sphere transform tests passed");

    return errors;
}

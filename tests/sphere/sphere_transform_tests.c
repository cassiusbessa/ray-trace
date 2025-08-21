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

// Função para rodar todos os testes de sphere + transform + intersect
int run_sphere_transform_tests(void)
{
    int errors = 0;

    errors += test_sphere_default_transform();
    errors += test_sphere_set_transform();

    if (errors)
        test_failure("Sphere transform tests failed");
    else
        test_success("Sphere transform tests passed");

    return errors;
}

#include "../tests.h"

#include "../tests.h"

#define TRUE 1
#define FALSE 0

// ======================== SCALING ========================

static int test_scaling_matrix_point(void)
{
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    int errors;

    errors = 0;
    transform = scaling_matrix(2, 3, 4);
    p = point(-4, 6, 8);
    result = matrix_multiply_by_tuple(transform, p);

    errors += test_check_double(result.x, -8, "scaling x");
    errors += test_check_double(result.y, 18, "scaling y");
    errors += test_check_double(result.z, 32, "scaling z");

    free_matrix(transform);
    return errors;
}

static int test_scaling_matrix_vector(void)
{
    t_matrix transform;
    t_tuple v;
    t_tuple result;
    int errors;

    errors = 0;
    transform = scaling_matrix(2, 3, 4);
    v = vector(-4, 6, 8);
    result = matrix_multiply_by_tuple(transform, v);

    errors += test_check_double(result.x, -8, "scaling vector x");
    errors += test_check_double(result.y, 18, "scaling vector y");
    errors += test_check_double(result.z, 32, "scaling vector z");

    free_matrix(transform);
    return errors;
}

static int test_scaling_inverse_vector(void)
{
    t_matrix transform;
    t_matrix inv;
    t_tuple v;
    t_tuple result;
    int errors;
    int success; // necessário para invert_matrix

    errors = 0;
    transform = scaling_matrix(2, 3, 4);

    // Passa &success como segundo argumento
    inv = invert_matrix(transform, &success);
    if (!success)
    {
        printf("❌ Falha ao inverter a matriz de scaling!\n");
        free_matrix(transform);
        return 1;
    }

    v = vector(-4, 6, 8);
    result = matrix_multiply_by_tuple(inv, v);

    errors += test_check_double(result.x, -2, "scaling inverse x");
    errors += test_check_double(result.y, 2, "scaling inverse y");
    errors += test_check_double(result.z, 2, "scaling inverse z");

    free_matrix(transform);
    free_matrix(inv);

    return errors;
}

static int test_scaling_reflection(void)
{
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    int errors;

    errors = 0;
    transform = scaling_matrix(-1, 1, 1);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);

    errors += test_check_double(result.x, -2, "reflection x");
    errors += test_check_double(result.y, 3, "reflection y");
    errors += test_check_double(result.z, 4, "reflection z");

    free_matrix(transform);
    return errors;
}

// ======================== RUN TESTS ========================

int run_test_scaling(void)
{
    int errors = 0;

    errors += test_scaling_matrix_point();
    errors += test_scaling_matrix_vector();
    errors += test_scaling_inverse_vector();
    errors += test_scaling_reflection();

    if (errors == 0)
        test_success("Scaling tests passed!");
    else
        test_failure("Scaling tests failed.");

    return errors;
}

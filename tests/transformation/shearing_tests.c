#include "../tests.h"

static int test_shearing(void)
{
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    int errors;

    errors = 0;

    // Teste 1: xy = 1, outros 0
    transform = shearing_matrix(1, 0, 0, 0, 0, 0);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 2 + 1 * 3, "shearing x moves in proportion to y");
    errors += test_check_double(result.y, 3, "shearing y unchanged");
    errors += test_check_double(result.z, 4, "shearing z unchanged");
    free_matrix(transform);

    // Teste 2: xz = 1, outros 0
    transform = shearing_matrix(0, 1, 0, 0, 0, 0);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 2 + 1 * 4, "shearing x moves in proportion to z");
    errors += test_check_double(result.y, 3, "shearing y unchanged");
    errors += test_check_double(result.z, 4, "shearing z unchanged");
    free_matrix(transform);

    // Teste 3: yx = 1
    transform = shearing_matrix(0, 0, 1, 0, 0, 0);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 2, "shearing x unchanged");
    errors += test_check_double(result.y, 3 + 1 * 2, "shearing y moves in proportion to x");
    errors += test_check_double(result.z, 4, "shearing z unchanged");
    free_matrix(transform);

    // Teste 4: yz = 1
    transform = shearing_matrix(0, 0, 0, 1, 0, 0);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 2, "shearing x unchanged");
    errors += test_check_double(result.y, 3 + 1 * 4, "shearing y moves in proportion to z");
    errors += test_check_double(result.z, 4, "shearing z unchanged");
    free_matrix(transform);

    // Teste 5: zx = 1
    transform = shearing_matrix(0, 0, 0, 0, 1, 0);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 2, "shearing x unchanged");
    errors += test_check_double(result.y, 3, "shearing y unchanged");
    errors += test_check_double(result.z, 4 + 1 * 2, "shearing z moves in proportion to x");
    free_matrix(transform);

    // Teste 6: zy = 1
    transform = shearing_matrix(0, 0, 0, 0, 0, 1);
    p = point(2, 3, 4);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 2, "shearing x unchanged");
    errors += test_check_double(result.y, 3, "shearing y unchanged");
    errors += test_check_double(result.z, 4 + 1 * 3, "shearing z moves in proportion to y");
    free_matrix(transform);

    return errors;
}

int run_test_shearing(void)
{
    int errors = 0;

    errors += test_shearing();

    if (errors == 0)
        test_success("Shearing matrix tests passed!");
    else
        test_failure("Shearing matrix tests failed.");

    return errors;
}

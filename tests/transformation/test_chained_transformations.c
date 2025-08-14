#include "../tests.h"

static int test_chained_transformations(void)
{
    int errors = 0;
    t_tuple p, p2, p3, p4;
    t_matrix A, B, C, T;

    // Ponto original
    p = point(1, 0, 1);

    // Matrizes de transformação
    A = rotation_x_matrix(M_PI / 2);
    B = scaling_matrix(5, 5, 5);
    C = translation_matrix(10, 5, 7);

    // Aplicando transformações em sequência
    p2 = matrix_multiply_by_tuple(A, p);
    errors += test_check_double(p2.x, 1, "sequence rotation x p2.x");
    errors += test_check_double(p2.y, -1, "sequence rotation x p2.y");
    errors += test_check_double(p2.z, 0, "sequence rotation x p2.z");

    p3 = matrix_multiply_by_tuple(B, p2);
    errors += test_check_double(p3.x, 5, "sequence scaling p3.x");
    errors += test_check_double(p3.y, -5, "sequence scaling p3.y");
    errors += test_check_double(p3.z, 0, "sequence scaling p3.z");

    p4 = matrix_multiply_by_tuple(C, p3);
    errors += test_check_double(p4.x, 15, "sequence translation p4.x");
    errors += test_check_double(p4.y, 0, "sequence translation p4.y");
    errors += test_check_double(p4.z, 7, "sequence translation p4.z");

    // Concatenando transformações
    T = matrix_multiply_by_matrix(C, matrix_multiply_by_matrix(B, A));
    t_tuple p_final = matrix_multiply_by_tuple(T, p);
    errors += test_check_double(p_final.x, 15, "chained T*p x");
    errors += test_check_double(p_final.y, 0, "chained T*p y");
    errors += test_check_double(p_final.z, 7, "chained T*p z");

    // Liberando memória
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(T);

    return errors;
}

int run_test_chained_transformations(void)
{
    int errors = test_chained_transformations();

    if (errors == 0)
        test_success("Chained transformation tests passed!");
    else
        test_failure("Chained transformation tests failed.");

    return errors;
}

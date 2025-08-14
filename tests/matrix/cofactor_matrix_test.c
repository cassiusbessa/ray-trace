#include "../tests.h"

static t_matrix matrix_a(void)
{
    t_matrix    matrix;

    matrix = new_matrix(3, 3);
    matrix.data[0][0] = 3;
    matrix.data[0][1] = 5;
    matrix.data[0][2] = 0;
    matrix.data[1][0] = 2;
    matrix.data[1][1] = -1;
    matrix.data[1][2] = -7;
    matrix.data[2][0] = 6;
    matrix.data[2][1] = -1;
    matrix.data[2][2] = 5;
    return (matrix);
}

static int test_cofactor_matrix1(void)
{
    t_matrix    matrix;
    int         cofactor;
    int         expected_cofactor;
    int         errors;

    matrix = matrix_a();
    cofactor = cofactor_matrix(matrix, 0, 0);
    expected_cofactor = -12;
    errors = 0;
    errors += test_check_double(cofactor, expected_cofactor, "cofactor_matrix");
    if (cofactor != expected_cofactor)
    {
        printf("Error: cofactor_matrix() returned %d, expected %d\n", cofactor, expected_cofactor);
        errors++;
    }
    free_matrix(matrix);
    return (errors);
}

static int test_cofactor_matrix2(void)
{
    t_matrix    matrix;
    int         cofactor;
    int         expected_cofactor;
    int         errors;

    matrix = matrix_a();
    cofactor = cofactor_matrix(matrix, 1, 0);
    expected_cofactor = -25;
    errors = 0;
    errors += test_check_double(cofactor, expected_cofactor, "cofactor_matrix");
    if (cofactor != expected_cofactor)
    {
        printf("Error: cofactor_matrix() returned %d, expected %d\n", cofactor, expected_cofactor);
        errors++;
    }
    free_matrix(matrix);
    return (errors);
}

int test_cofactor_matrix(void)
{
    int errors;

    errors = 0;
    errors += test_cofactor_matrix1();
    errors += test_cofactor_matrix2();
    if (errors)
        printf("❌ cofactor_matrix_tests failed\n");
    else
        printf("✅ cofactor_matrix_tests passed\n");
    return (errors);
}

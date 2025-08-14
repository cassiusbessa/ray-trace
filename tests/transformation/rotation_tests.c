#include "../tests.h"

static int test_rotation_x_matrix(void)
{
    int errors = 0;
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    float half_quarter = M_PI / 4; // 45 graus
    float full_quarter = M_PI / 2; // 90 graus  

    // Rotação em torno do X
    transform = rotation_x_matrix(half_quarter);
    p = point(0, 1, 0);
    result = matrix_multiply_by_tuple(transform, p);

    errors += test_check_double(result.x, 0, "rotation x 45 degrees x");
    errors += test_check_double(result.y, sqrt(2) / 2, "rotation x 45 degrees y");
    errors += test_check_double(result.z, sqrt(2) / 2, "rotation x 45 degrees z");
    free_matrix(transform); 

    transform = rotation_x_matrix(full_quarter);
    p = point(0, 1, 0);
    result = matrix_multiply_by_tuple(transform, p);

    errors += test_check_double(result.x, 0, "rotation x 90 degrees x");
    errors += test_check_double(result.y, 0, "rotation x 90 degrees y");
    errors += test_check_double(result.z, 1, "rotation x 90 degrees z");

    free_matrix(transform);

    return(errors);
}

static int test_rotation_y_matrix(void)
{
    int errors = 0;
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    float half_quarter; // 45 graus
    float full_quarter; // 90 graus  

    half_quarter = M_PI / 4;

    transform = rotation_y_matrix(half_quarter);
    p = point(0, 0, 1);
    result = matrix_multiply_by_tuple(transform, p);

    errors += test_check_double(result.x, sqrt(2) / 2, "rotation y 45 degrees x");
    errors += test_check_double(result.y, 0, "rotation y 45 degrees y");
    errors += test_check_double(result.z, sqrt(2) / 2, "rotation y 45 degrees z");

    free_matrix(transform); 

    full_quarter = M_PI / 2;
    transform = rotation_y_matrix(full_quarter);

    p = point(0, 0, 1);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, 1, "rotation y 90 degrees x");
    errors += test_check_double(result.y, 0, "rotation y 90 degrees y");
    errors += test_check_double(result.z, 0, "rotation y 90 degrees z");

    free_matrix(transform);

    return(errors);
}

static int test_rotation_z_matrix(void)
{
    int errors = 0;
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    float half_quarter; // 45 graus
    float full_quarter; // 90 graus  

    half_quarter = M_PI / 4;

    transform = rotation_z_matrix(half_quarter);
    p = point(0, 1, 0);
    result = matrix_multiply_by_tuple(transform, p);

    errors += test_check_double(result.x, -sqrt(2) / 2, "rotation z 45 degrees x");
    errors += test_check_double(result.y, sqrt(2) / 2, "rotation z 45 degrees y");
    errors += test_check_double(result.z, 0, "rotation z 45 degrees z");

    free_matrix(transform); 

    full_quarter = M_PI / 2;
    transform = rotation_z_matrix(full_quarter);

    p = point(0, 1, 0);
    result = matrix_multiply_by_tuple(transform, p);
    errors += test_check_double(result.x, -1, "rotation z 90 degrees x");
    errors += test_check_double(result.y, 0, "rotation z 90 degrees y");
    errors += test_check_double(result.z, 0, "rotation z 90 degrees z");

    free_matrix(transform);

    return(errors);
}   

int run_test_rotation(void)
{
    int         errors;

    errors = 0;

    errors += test_rotation_x_matrix();
    errors += test_rotation_y_matrix();
    errors += test_rotation_z_matrix();

    if (errors == 0)
        test_success("Rotation matrix tests passed!");
    else
        test_failure("Rotation matrix tests failed.");

    
    return (errors);
}
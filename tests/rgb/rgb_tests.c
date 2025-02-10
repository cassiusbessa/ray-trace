#include "../tests.h"

static int test_add_rgb(void)
{
    t_rgb   *color1;
    t_rgb   *color2;
    t_rgb   *result;
    int     errors;

    errors = 0;
    color1 = new_rgb(0.5, 0.4, 1.7);
    color2 = new_rgb(0.5, 0.4, 1.7);
    result = add_rgb(color1, color2);
    errors += test_check_double(result->r, 1.0, "result->r should be 1.0");
    errors += test_check_double(result->g, 0.8, "result->g should be 0.8");
    errors += test_check_double(result->b, 3.4, "result->b should be 3.4");
    free(color1);
    free(color2);
    free(result);
    if (errors == 0)
        test_success("test_add_rgb pass!");
    return (errors);
}

static int  test_sub_rgb(void)
{
    t_rgb   *color1;
    t_rgb   *color2;
    t_rgb   *result;
    int     errors;

    errors = 0;
    color1 = new_rgb(0.5, 0.4, 1.7);
    color2 = new_rgb(0.5, 0.4, 1.7);
    result = sub_rgb(color1, color2);
    errors += test_check_double(result->r, 0.0, "result->r should be 0.0");
    errors += test_check_double(result->g, 0.0, "result->g should be 0.0");
    errors += test_check_double(result->b, 0.0, "result->b should be 0.0");
    free(color1);
    free(color2);
    free(result);
    if (errors == 0)
        test_success("test_sub_rgb pass!");
    return (errors);
}

static int  test_multiply_rgb_by_scalar(void)
{
    t_rgb   *color;
    t_rgb   *result;
    int     errors;

    errors = 0;
    color = new_rgb(0.5, 0.4, 1.7);
    result = multiply_rgb_by_scalar(color, 2);
    errors += test_check_double(result->r, 1.0, "result->r should be 1.0");
    errors += test_check_double(result->g, 0.8, "result->g should be 0.8");
    errors += test_check_double(result->b, 3.4, "result->b should be 3.4");
    free(color);
    free(result);
    if (errors == 0)
        test_success("test_multiply_rgb_by_scalar pass!");
    return (errors);
}

static int  test_multiply_rgb_by_rgb(void)
{
    t_rgb   *color1;
    t_rgb   *color2;
    t_rgb   *result;
    int     errors;

    errors = 0;
    color1 = new_rgb(0.5, 0.4, 1.7);
    color2 = new_rgb(0.5, 0.4, 1.7);
    result = multiply_rgb_by_rgb(color1, color2);
    errors += test_check_double(result->r, 0.25, "result->r should be 0.25");
    errors += test_check_double(result->g, 0.16, "result->g should be 0.16");
    errors += test_check_double(result->b, 2.89, "result->b should be 2.89");
    free(color1);
    free(color2);
    free(result);
    if (errors == 0)
        test_success("test_multiply_rgb_by_rgb pass!");
    return (errors);
}

int all_rgb_tests(void)
{
    int errors;

    errors = 0;
    errors += all_rgb_common_tests();
    errors += test_add_rgb();
    errors += test_sub_rgb();
    errors += test_multiply_rgb_by_scalar();
    errors += test_multiply_rgb_by_rgb();
    return (errors);
}
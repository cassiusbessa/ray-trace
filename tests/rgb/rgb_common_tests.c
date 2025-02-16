#include "../tests.h"

static int test_create_rgb(void)
{
    t_rgb	rgb;
    int		errors;

    errors = 0;
    rgb = new_rgb(0.5, 0.4, 1.7);
    errors += test_check_double(rgb.r, 0.5, "rgb.r should be 0.5");
    errors += test_check_double(rgb.g, 0.4, "rgb.g should be 0.4");
    errors += test_check_double(rgb.b, 1.7, "rgb.b should be 1.7");
    if (errors == 0)
        test_success("test_create_rgb pass!");
    else
        test_failure("test_create_rgb failed.");
    return (errors);
}

static int  test_equals_rgb(void)
{
    t_rgb   color1;
    t_rgb   color2;
    int     errors;

    errors = 0;
    color1 = new_rgb(0.5, 0.4, 1.7);
    color2 = new_rgb(0.5, 0.400, 1.7);
    errors += test_check(equal_rgb(color1, color2), "color1 should be equal to color2");
    if (errors == 0)
        test_success("test_equals_rgb pass!");
    else
        test_failure("test_equals_rgb failed.");
    return (errors);
}

static int  test_not_equals_rgb(void)
{
    t_rgb   color1;
    t_rgb   color2;
    int     errors;

    errors = 0;
    color1 = new_rgb(0.5, 0.4, 1.7);
    color2 = new_rgb(0.5, 0.401, 1.7);
    errors += test_check(!equal_rgb(color1, color2), "color1 should not be equal to color2");
    if (errors == 0)
        test_success("test_not_equals_rgb pass!");
    else
        test_failure("test_not_equals_rgb failed.");
    return (errors);
}

int all_rgb_common_tests(void)
{
    int errors;

    errors = 0;
    errors += test_create_rgb();
    errors += test_equals_rgb();
    errors += test_not_equals_rgb();
    return (errors);
}


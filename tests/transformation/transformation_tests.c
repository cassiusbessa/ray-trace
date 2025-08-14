#include "../tests.h"


int all_transformation_tests(void)
{
    int errors;

    errors = 0;
    errors += run_test_translation_point();
    errors += run_test_translation_vector();
    errors += run_test_scaling();
    errors += run_test_rotation();
    errors += run_test_shearing();
    errors += run_test_chained_transformations();
    if (errors == 0)
        ft_printf("\n🎉 All transformation tests fine!\n");
    else
        ft_printf("\n❌ %d transformation tests failed.\n", errors);
    return (errors);
}
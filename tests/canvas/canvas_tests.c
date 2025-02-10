#include "../tests.h"

static int  create_canvas_all_black(void)
{
    t_canvas    *canvas;
    t_rgb       *black;
    int         i;
    int         j;
    int         errors;

    errors = 0;
    black = new_rgb(0, 0, 0);
    canvas = new_canvas(10, 10);
    errors += test_check(canvas->height == 10, "canvas->height should be 10");
    errors += test_check(canvas->width == 10, "canvas->width should be 10");
    i = 0;
    while (i < canvas->height)
    {
        j = 0;
        while (j < canvas->width)
        {
            errors += test_check(equal_rgb(canvas->pixels[i][j], black), "canvas->pixels[i] should be black");
            j++;
        }
        i++;
    }
    free_canvas(canvas);
    free(black);
    if (errors == 0)
        test_success("create_canvas_all_black pass!");
    return (errors);
}

int canvas_tests(void)
{
    int errors;

    errors = 0;
    errors += create_canvas_all_black();
    return (errors);
}
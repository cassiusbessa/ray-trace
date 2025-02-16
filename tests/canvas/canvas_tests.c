#include "../tests.h"

static int  create_canvas_all_black(void)
{
    t_canvas    *canvas;
    t_rgb       black;
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
    if (errors == 0)
        test_success("create_canvas_all_black pass!");
    else
        test_failure("create_canvas_all_black failed.");
    return (errors);
}

static int  test_pixel_at_canvas(void)
{
    t_canvas    *canvas;
    t_rgb       red;
    t_rgb       *pixel;
    int         errors;

    errors = 0;
    red = new_rgb(1, 0, 0);
    canvas = new_canvas(10, 10);
    write_pixel(canvas, 2, 3, red);
    pixel = pixel_at(canvas, 2, 3);
    errors += test_check(equal_rgb(*pixel, red), "pixel_at(canvas, 2, 3) should be red");
    free_canvas(canvas);
    if (errors == 0)
        test_success("pixel_at_canvas pass!");
    else
        test_failure("pixel_at_canvas failed.");
    return (errors);
}

static int  test_write_pixel_to_canvas(void)
{
    t_canvas    *canvas;
    t_rgb       red;
    int         errors;

    errors = 0;
    red = new_rgb(1, 0, 0);
    canvas = new_canvas(10, 10);
    write_pixel(canvas, 2, 3, red);
    errors += test_check(equal_rgb(canvas->pixels[3][2], red), "canvas->pixels[3][2] should be red");
    free_canvas(canvas);
    if (errors == 0)
        test_success("write_pixel_to_canvas pass!");
    else
        test_failure("write_pixel_to_canvas failed.");
    return (errors);
}

int canvas_tests(void)
{
    int errors;

    errors = 0;
    errors += create_canvas_all_black();
    errors += test_pixel_at_canvas();
    errors += test_write_pixel_to_canvas();
    return (errors);
}
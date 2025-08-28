#include "../tests.h"

static int test_render_world_with_camera(void)
{
    int errors = 0;

    // Configura o mundo e a câmera
    t_world w = default_world();
    t_camera c = new_camera(11, 11, M_PI / 2);

    t_tuple from = point(0, 0, -5);
    t_tuple to = point(0, 0, 0);
    t_tuple up = vector(0, 1, 0);
    t_matrix view = view_transform(from, to, up);
    c.transform = view;

    // Renderiza a cena
    t_canvas *image = render(c, &w);

    // Verifica a cor do pixel central
    t_rgb expected_color = new_rgb(0.38066f, 0.47583f, 0.2855f);
    t_rgb actual_color = *pixel_at(image, 5, 5);

    errors += test_check(equal_rgb(expected_color, actual_color),
                         "Pixel at (5,5) should match expected color");

    if (errors)
        test_failure("Render world with camera test failed");
    else
        test_success("Render world with camera test passed");

    // Limpeza
    free_canvas(image);

    return errors;
}

int run_render_tests(void)
{
    int errors = 0;

    errors += test_render_world_with_camera();

    if (errors)
        test_failure("Render tests failed");
    else
        test_success("Render tests passed");

    return errors;
}

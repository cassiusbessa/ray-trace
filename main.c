#include "includes/miniRT.h"
#include <stdio.h>

int main(void)
{
    // --- Criar mundo ---
    t_world world = new_world();

    // --- Criar primeira esfera ---
    t_sphere s1 = new_sphere(point(-1.0, 0.0, 0.0), 1); // esfera à esquerda
    s1.material = new_material_default();
    s1.material.color = new_rgb(1, 0, 0); // vermelho
    s1.material.specular = 0;
    t_object sphere1 = new_object(SPHERE, (void *)&s1);
    add_object_to_world(&world, sphere1);

    // --- Criar segunda esfera ---
    t_sphere s2 = new_sphere(point(1.0, 0.0, 0.0), 1); // esfera à direita
    s2.material = new_material_default();
    s2.material.color = new_rgb(0, 0, 1); // azul
    s2.material.specular = 0;
    t_object sphere2 = new_object(SPHERE, (void *)&s2);
    add_object_to_world(&world, sphere2);

    // --- Criar fundo branco (uma esfera grande atrás das outras) ---
    t_sphere bg = new_sphere(point(0, 0, 5), 50); // esfera grande atrás
    bg.material = new_material_default();
    bg.material.color = new_rgb(1, 1, 1); // branco
    bg.material.specular = 0;
    t_object background = new_object(SPHERE, (void *)&bg);
    add_object_to_world(&world, background);

    // --- Adicionar luz ---
    t_point_light light = new_point_light(point(-10, 10, -10), new_rgb(1, 1, 1));
    add_light_to_world(&world, light);

    // --- Criar câmera ---
    t_camera cam = new_camera(400, 300, M_PI / 3);
    free_matrix(cam.transform);
    cam.transform = view_transform(point(0, 0, -10), point(0, 0, 0), vector(0, 1, 0));

    // --- Renderizar ---
    t_canvas *c = render(cam, &world);

    // --- Mostrar na tela ---
    open_mlx_screen(c);

    // --- Liberar memória ---
    free_camera(&cam);
    free_world(&world);
    free_canvas(c);

    return 0;
}


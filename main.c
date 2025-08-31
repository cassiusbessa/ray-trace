#include "includes/miniRT.h"
#include <stdio.h>

int main(void)
{
    // --- Criar mundo ---
    t_world world = new_world();

    // --- Criar o "chão" (uma esfera achatada) ---
    t_sphere *floor_sphere = malloc(sizeof(t_sphere));
    *floor_sphere = new_sphere(point(0, 0, 0), 1);
    floor_sphere->material = new_material_default();
    floor_sphere->material.color = new_rgb(1, 0.9, 0.9);
    floor_sphere->material.specular = 0;
    t_object floor = new_object(SPHERE, (void *)floor_sphere);
    set_object_transform(&floor, scaling_matrix(10, 0.01, 10));
    add_object_to_world(&world, floor);

    // --- Criar esfera do meio ---
    t_sphere *middle_sphere = malloc(sizeof(t_sphere));
    *middle_sphere = new_sphere(point(0, 0, 0), 1);
    middle_sphere->material = new_material_default();
    middle_sphere->material.color = new_rgb(0.1, 1, 0.5);
    middle_sphere->material.diffuse = 0.7;
    middle_sphere->material.specular = 0.3;
    t_object middle = new_object(SPHERE, (void *)middle_sphere);
    set_object_transform(&middle, translation_matrix(-0.5, 1, 0.5));
    add_object_to_world(&world, middle);

    // --- Criar esfera da direita ---
    t_sphere *right_sphere = malloc(sizeof(t_sphere));
    *right_sphere = new_sphere(point(0, 0, 0), 1);
    right_sphere->material = new_material_default();
    right_sphere->material.color = new_rgb(0.5, 1, 0.1);
    right_sphere->material.diffuse = 0.7;
    right_sphere->material.specular = 0.3;
    t_object right = new_object(SPHERE, (void *)right_sphere);
    set_object_transform(&right, chain_transformations((t_transform_params){
        .translation = {1.5, 0.5, -0.5},
        .scaling = {0.5, 0.5, 0.5}
    }));
    add_object_to_world(&world, right);

    // --- Criar esfera da esquerda ---
    t_sphere *left_sphere = malloc(sizeof(t_sphere));
    *left_sphere = new_sphere(point(0, 0, 0), 1);
    left_sphere->material = new_material_default();
    left_sphere->material.color = new_rgb(1, 0.8, 0.1);
    left_sphere->material.diffuse = 0.7;
    left_sphere->material.specular = 0.3;
    t_object left = new_object(SPHERE, (void *)left_sphere);
    set_object_transform(&left, chain_transformations((t_transform_params){
        .translation = {-1.5, 0.75, -0.75},
        .scaling = {0.75, 0.75, 0.75}
    }));
    add_object_to_world(&world, left);

    // --- Adicionar luz ---
    t_point_light light = new_point_light(point(-10, 10, -10), new_rgb(1, 1, 1));
    add_light_to_world(&world, light);

    // --- Criar câmera ---
    t_camera cam = new_camera(800, 600, M_PI / 3);
    free_matrix(cam.transform); // free the default one before assigning a new one
    cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

    // --- Renderizar ---
    printf("Iniciando renderização com a nova cena...\n");
    t_canvas *c = render(cam, &world);
    printf("Renderização concluída!\n");

    // --- Mostrar na tela ---
    open_mlx_screen(c);

    // --- Liberar memória ---
    free_camera(&cam);
    free_world(&world);
    free_canvas(c);

    return 0;
}

#include "miniRT.h"
#include <stdio.h>  // não esqueça de incluir para usar printf

// Cria a cena de teste com uma esfera vermelha e um plano cinza
t_object *create_test_scene(t_scene *scene)
{
    printf("create_test_scene: iniciando criação dos objetos\n");

    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere) {
        printf("create_test_scene: falha malloc esfera\n");
        return NULL;
    }
    sphere->center = vec3(0, 0, 0);
    sphere->radius = 1.0;
    sphere->color = make_color(1, 0, 0);

    t_object *obj_sphere = malloc(sizeof(t_object));
    if (!obj_sphere) {
        printf("create_test_scene: falha malloc obj_sphere\n");
        free(sphere);
        return NULL;
    }
    obj_sphere->type = SPHERE;
    obj_sphere->shape = sphere;
    obj_sphere->next = NULL;

    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane) {
        printf("create_test_scene: falha malloc plane\n");
        free(obj_sphere->shape);
        free(obj_sphere);
        return NULL;
    }
    plane->point = vec3(0, -1, 0);
    plane->normal = vec3(0, 1, 0);
    plane->color = make_color(0.5, 0.5, 0.5);

    t_object *obj_plane = malloc(sizeof(t_object));
    if (!obj_plane) {
        printf("create_test_scene: falha malloc obj_plane\n");
        free(plane);
        free(obj_sphere->shape);
        free(obj_sphere);
        return NULL;
    }
    obj_plane->type = PLANE;
    obj_plane->shape = plane;
    obj_plane->next = NULL;

    obj_sphere->next = obj_plane;
    scene->objects = obj_sphere;

    printf("create_test_scene: objetos criados com sucesso\n");

    // Imprime os objetos para verificar
    t_object *cur = scene->objects;
    while (cur) {
        printf("Objeto tipo %d em %p\n", cur->type, (void*)cur);
        cur = cur->next;
    }

    return obj_sphere;
}

// Inicializa a câmera e luzes
void init_test_scene(t_scene *scene)
{
    printf("init_test_scene: inicializando camera e luzes\n");

    // Câmera
    init_camera(&scene->camera, WIDTH, HEIGHT);
    scene->camera.origin = vec3(0, 1, -5);
    scene->camera.forward = vec3_normalize(vec3(0, 0, 1));
    scene->camera.right = vec3_normalize(vec3_cross(scene->camera.forward, vec3(0, 1, 0)));
    scene->camera.up = vec3_cross(scene->camera.right, scene->camera.forward);
    scene->camera.fov = 70;

    // Luz ambiente
    scene->ambient.intensity = 0.1;
    scene->ambient.color = make_color(1, 1, 1);

    // Luz pontual
    scene->point_light.position = vec3(5, 5, -3);
    scene->point_light.brightness = 1.0;
    scene->point_light.color = make_color(1, 1, 1);

    printf("init_test_scene: camera e luzes inicializadas\n");
}

// Fecha ao apertar ESC ou clicar no X
int close_window(int keycode, void *param)
{
    (void)param;
    printf("close_window: tecla %d pressionada\n", keycode);
    if (keycode == 65307) // ESC
        exit(0);
    return (0);
}

int handle_close(void *param)
{
    (void)param;
    printf("handle_close: janela fechada\n");
    exit(0);
    return (0);
}

int main(void)
{
    printf("main: iniciando programa\n");

    t_mlx mlx;
    t_scene scene;

    if (!mlx_init_all(&mlx, WIDTH, HEIGHT))
    {
        perror("mlx_init_all failed");
        return 1;
    }
    printf("main: MiniLibX inicializado\n");

    // Inicializa cena e câmera
    init_test_scene(&scene);

    // Cria objetos da cena
    if (!create_test_scene(&scene))
    {
        fprintf(stderr, "Erro ao criar cena de teste\n");
        return 1;
    }

    printf("main: cena criada, iniciando render_scene\n");

    // Renderiza
    render_scene(&scene, &mlx);

    printf("main: render_scene finalizado, configurando hooks\n");

    // Hooks para fechar janela
    mlx_hook(mlx.win_ptr, 2, 1L << 0, close_window, NULL);     // Tecla (ESC)
    mlx_hook(mlx.win_ptr, 17, 0, handle_close, NULL);          // X da janela

    printf("main: entrando no loop da MiniLibX\n");
    mlx_loop(mlx.mlx_ptr);

    printf("main: fim do programa\n");
    return 0;
}

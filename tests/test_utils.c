#include "miniRT.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- TESTES BÁSICOS --- */
void test_put_pixel_basic(void)
{
    t_mlx mlx;
    char buffer[100 * 100 * 4] = {0};

    mlx.bpp = 32;
    mlx.size_line = 100 * 4;
    mlx.img_data = buffer;
    mlx.width = 100;
    mlx.height = 100;

    put_pixel(&mlx, 0, 0, 0x11223344);
    assert(*(unsigned int *)buffer == 0x11223344);

    put_pixel(&mlx, 99, 99, 0xAABBCCDD);
    unsigned int *pixel = (unsigned int *)(buffer + (99 * mlx.size_line) + (99 * 4));
    assert(*pixel == 0xAABBCCDD);

    // Fora do limite → não deve crashar
    put_pixel(&mlx, -1, -1, 0x12345678);
}

void test_get_object_color(void)
{
    t_sphere sphere = {.color = make_color(0.5, 0.25, 0.75)};
    t_object obj = {.type = SPHERE, .shape = &sphere};

    t_color c = get_object_color(&obj);
    assert(c.r == 0.5f && c.g == 0.25f && c.b == 0.75f);

    c = get_object_color(NULL);
    assert(c.r == 0 && c.g == 0 && c.b == 0);
}

void test_apply_diffuse_light(void)
{
    t_point_light light;
    light.position = vec3(0, 0, 5);  // Luz do mesmo lado da normal
    light.brightness = 1.0f;
    light.color = make_color(1, 1, 1);

    t_vec3 point = vec3(0, 0, 0);
    t_vec3 normal = vec3(0, 0, 1);
    t_color obj_color = make_color(1, 0, 0);

    t_color result = apply_diffuse_light(&light, point, normal, obj_color, 1.0f);
    assert(result.r > 0.0f);
    assert(result.g == 0.0f);
    assert(result.b == 0.0f);
}

void test_calculate_specular(void)
{
    t_vec3 point = vec3(0, 0, 0);
    t_vec3 normal = vec3(0, 0, 1);
    t_vec3 light_pos = vec3(0, 0, 5);
    t_vec3 view_pos = vec3(0, 0, -1);
    t_color light_color = make_color(1, 1, 1);
    float brightness = 1.0f;

    t_color result = calculate_specular(point, normal, light_pos, view_pos, light_color, brightness);
    assert(result.r >= 0.0f && result.g >= 0.0f && result.b >= 0.0f);
}

/* --- SUA CENA DE TESTE --- */
t_object *create_test_scene(t_scene *scene)
{
    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere) return NULL;
    sphere->center = vec3(0, 0, 5);
    sphere->radius = 1.0f;
    sphere->color = make_color(1.0, 0.0, 0.0);

    t_object *obj = malloc(sizeof(t_object));
    if (!obj) { free(sphere); return NULL; }
    obj->type = SPHERE;
    obj->shape = sphere;
    obj->next = NULL;
    scene->objects = obj;

    // Usar campo correto point_light
    scene->point_light.position = vec3(2, 2, 0);
    scene->point_light.brightness = 1.0f;
    scene->point_light.color = make_color(1.0, 1.0, 1.0);
    scene->point_light.specular_color = make_color(1.0, 1.0, 1.0);

    return obj;
}

void init_test_scene(t_scene *scene)
{
    memset(scene, 0, sizeof(t_scene));
}

int close_window(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307) // ESC
        exit(0);
    return (0);
}

int handle_close(void *param)
{
    (void)param;
    exit(0);
    return (0);
}


/* --- MAIN --- */
int main(void)
{
    printf("main: iniciando programa\n");

    printf("main: executando testes básicos...\n");
    test_put_pixel_basic();
    test_get_object_color();
    test_apply_diffuse_light();
    test_calculate_specular();
    printf("✅ Todos os testes básicos passaram!\n");

    t_mlx mlx;
    t_scene scene;

    if (!mlx_init_all(&mlx, WIDTH, HEIGHT))
    {
        perror("mlx_init_all failed");
        return 1;
    }
    printf("main: MiniLibX inicializado\n");

    init_test_scene(&scene); 
    // Inicializa a câmera com a resolução da janela
    init_camera(&scene.camera, WIDTH, HEIGHT);

    if (!create_test_scene(&scene))
    {
        fprintf(stderr, "Erro ao criar cena de teste\n");
        return 1;
    }

    printf("main: cena criada, iniciando render_scene\n");
    printf("Camera resolution: %d x %d\n", scene.camera.width, scene.camera.height);
    render_scene(&scene, &mlx);

    mlx_hook(mlx.win_ptr, 2, 1L << 0, close_window, NULL);
    mlx_hook(mlx.win_ptr, 17, 0, handle_close, NULL);

    printf("main: entrando no loop da MiniLibX\n");
    mlx_loop(mlx.mlx_ptr);

    return 0;
}

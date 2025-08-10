#include "miniRT.h"

// Cria uma esfera vermelha simples e retorna ponteiro para lista de objetos (a cena)
static t_object *create_test_scene(void)
{
	t_object *sphere_obj;
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = vec3(0, 0, 5);
	sphere->radius = 1.0;
	sphere->color = make_color(1.0, 0.0, 0.0);

	sphere_obj = malloc(sizeof(t_object));
	if (!sphere_obj)
	{
		free(sphere);
		return (NULL);
	}
	sphere_obj->type = SPHERE;
	sphere_obj->shape = sphere;
	sphere_obj->next = NULL;

	return (sphere_obj);
}

// Evento para fechar janela (ESC ou fechar X)
int	close_window(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307) // ESC
		exit(0);
	return (0);
}

// Captura tecla para fechar janela
int	handle_key(int keycode, void *param)
{
	if (keycode == 65307) // ESC
		close_window(keycode, param);
	return (0);
}

int main(void)
{
    t_mlx mlx;
    t_camera cam;
    t_scene scene;  // NÃO ponteiro
    t_object *obj_list;

    if (!mlx_init_all(&mlx, WIDTH, HEIGHT))
    {
        perror("mlx_init_all");
        return (1);
    }

    init_camera(&cam, WIDTH, HEIGHT);
    scene.camera = cam;

    obj_list = create_test_scene(); // lista de objetos criada
    if (!obj_list)
    {
        fprintf(stderr, "Failed to create scene objects\n");
        return (1);
    }
    scene.objects = obj_list;

    // Inicializar luz ambiente e luz pontual aqui, por exemplo:
    scene.ambient.intensity = 0.1f;
    scene.ambient.color = make_color(1, 1, 1);
    scene.point_light.position = vec3(5, 5, 0);
    scene.point_light.brightness = 0.8f;
    scene.point_light.color = make_color(1, 1, 1);

    render_scene(&scene, &mlx);

    mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_key, NULL);
    mlx_hook(mlx.win_ptr, 17, 0, close_window, NULL);

    mlx_loop(mlx.mlx_ptr);

    return (0);
}

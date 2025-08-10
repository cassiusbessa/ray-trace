/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 17:18:38 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int close_window(void *param)
{
    (void)param;
    exit(0);
    return 0;
}

int handle_key(int keycode, void *param)
{
    t_scene *scene;

    if (keycode == 65307) // ESC
    {
        // Antes de sair, liberar recursos da cena
        scene = (t_scene *)param;
        free_point_lights(scene);
        free_objects(scene->objects); 
        exit(0);
    }
    return 0;
}

int main(int argc, char **argv)
{
    t_mlx mlx;
    t_scene scene;

    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s arquivo_cena.rt\n", argv[0]);
        return 1;
    }

    if (!mlx_init_all(&mlx, WIDTH, HEIGHT))
    {
        perror("mlx_init_all");
        return 1;
    }

    // Inicializa cena zerada
    ft_memset(&scene, 0, sizeof(t_scene));
    scene.point_lights = NULL;    // Importante iniciar como NULL
    scene.n_point_lights = 0;

    // Parse do arquivo passado por argumento
    if (parse_rt_file(argv[1], &scene) != 0)
    {
        fprintf(stderr, "Erro ao carregar cena do arquivo: %s\n", argv[1]);
        return 1;
    }

    // Inicializa a câmera usando os dados da cena (origin, look_at, fov, width, height)
    init_camera(&scene.camera,
                scene.camera.origin,
                scene.camera.forward,
                scene.camera.fov,
                WIDTH,
                HEIGHT);

    // Renderiza a cena
    render_scene(&scene, &mlx);

    // Passa o ponteiro da cena para handle_key para liberar recursos no exit
    mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_key, &scene);
    mlx_hook(mlx.win_ptr, 17, 0, close_window, NULL);

    mlx_loop(mlx.mlx_ptr);

    // Nunca vai chegar aqui (exit chama antes), mas só por segurança:
    free_point_lights(&scene);
    free_objects(scene.objects);

    return 0;
}


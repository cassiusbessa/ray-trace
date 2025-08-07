#include "miniRT.h"

// Dimensões da janela
#define WIDTH  HSIZE
#define HEIGHT VSIZE

int main(int argc, char **argv)
{
    t_world world;
    t_canvas canvas;
    t_mlx mlx;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <scene.rt>\n", argv[0]);
        return (1);
    }

    // 1. Parse do arquivo .rt para popular o mundo
    if (!parse_rt_file(argv[1], &world))
    {
        fprintf(stderr, "Failed to parse scene file.\n");
        return (1);
    }

    // 2. Criar canvas para renderização
    canvas = *new_canvas(WIDTH, HEIGHT);

    // 3. Renderizar a cena no canvas
    render(world, &canvas);

    // 4. Inicializar MLX e criar janela + imagem
    mlx = init_window(WIDTH, HEIGHT, "miniRT");

    // 5. Mostrar o canvas na janela MLX e iniciar o loop interativo
    run_mlx(&mlx, &canvas);

    // 6. Liberar recursos após o loop (se houver)
    free_canvas(&canvas);
    // free_world(&world); // caso implemente função para liberar a cena

    return (0);
}

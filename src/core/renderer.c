/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:16:39 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char *dst;
    int bytes_per_pixel;
    int offset;

	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
        return;
    bytes_per_pixel = mlx->bpp / 8;
    offset = (y * mlx->size_line) + (x * bytes_per_pixel);
    dst = mlx->img_data + offset;

    // Escreve o valor da cor no endereço de dst
    *(unsigned int *)dst = color;
}

int closest_hit(t_ray *ray, t_object *scene, t_intersection *out)
{
	t_object *cur = scene;
	t_intersection tmp;
	int hit_any = 0;
	double closest_t = INF;

	while (cur)
	{
		if (intersect_object(ray, cur, &tmp))
		{
			if (tmp.t > EPS && tmp.t < closest_t)
			{
				closest_t = tmp.t;
				*out = tmp;
				out->object = cur;
				hit_any = 1;
			}
		}
		cur = cur->next;
	}
	return (hit_any);
}

// Extrai a cor do objeto hitado
t_color get_object_color(t_object *obj)
{
    t_color color;

    color = make_color(0, 0, 0);
	
	if(!obj)
		return (color);
	if (obj->type == SPHERE)
		color = ((t_sphere *)obj->shape)->color;
	else if (obj->type == PLANE)
		color = ((t_plane *)obj->shape)->color;
	else if (obj->type == CYLINDER)
		color = ((t_cylinder *)obj->shape)->color;

    return (color);
}
void render_scene(t_scene *scene, t_mlx *mlx)
{
    int x;
    int y;
    t_ray ray;
    t_intersection hit;
    int color;
    t_color col;

    // Define uma região pequena para debug (exemplo: 10x10 no centro da imagem)
    int debug_min_x = scene->camera.width / 2 - 5;
    int debug_max_x = scene->camera.width / 2 + 5;
    int debug_min_y = scene->camera.height / 2 - 5;
    int debug_max_y = scene->camera.height / 2 + 5;

    // Limite máximo de mensagens de debug para evitar flood
    static int debug_print_count = 0;
    int debug_print_limit = 30;

    printf("Renderizando cena com resolução %d x %d\n", scene->camera.width, scene->camera.height);

    y = 0;
    while (y < scene->camera.height)
    {
        x = 0;
        while (x < scene->camera.width)
        {
            ray = camera_ray(&scene->camera, x, y);

            if (closest_hit(&ray, scene->objects, &hit))
            {
                if (debug_print_count < debug_print_limit &&
                    x >= debug_min_x && x < debug_max_x &&
                    y >= debug_min_y && y < debug_max_y)
                {
                    printf("[DEBUG] Hit em pixel (%d, %d): t=%.3f, objeto tipo=%d\n", x, y, hit.t, hit.object->type);
                    printf("        Ponto: (%.2f, %.2f, %.2f)\n", hit.point.x, hit.point.y, hit.point.z);

                    col = get_object_color(hit.object);
                    printf("        Cor base objeto: (%.2f, %.2f, %.2f)\n", col.r, col.g, col.b);

                    col = calculate_lighting(scene, hit.point, hit.normal, scene->camera.origin, col, hit.object);

                    printf("        Cor final após iluminação: (%.2f, %.2f, %.2f)\n", col.r, col.g, col.b);

                    debug_print_count++;
                }
                else
                {
                    // Se não está no debug, só calcula a cor normal
                    col = get_object_color(hit.object);
                    col = calculate_lighting(scene, hit.point, hit.normal, scene->camera.origin, col, hit.object);
                }

                color = color_to_int(col);
            }
            else
            {
                // Debug para alguns pixels que não acertam nada (espalhado, sem flood)
                if ((x % 100 == 0) && (y % 100 == 0) && debug_print_count < debug_print_limit)
                {
                    printf("[DEBUG] Pixel (%d, %d) não acertou nenhum objeto.\n", x, y);
                    debug_print_count++;
                }

                color = 0x000000; // Fundo preto
            }
            put_pixel(mlx, x, y, color);
            x++;
        }
        y++;
    }

    printf("Renderização concluída, enviando imagem para janela\n");
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

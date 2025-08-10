/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/09 17:59:20 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int parse_point_light_line(const char *line, t_point_light *light)
{
    char **tokens;

    printf("[DEBUG] parse_point_light_line: linha -> '%s'\n", line);

    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
    {
        printf("[ERROR] Luz pontual: número inválido de parâmetros\n");
        print_error("Luz pontual: número inválido de parâmetros", tokens);
    }

    if (ft_strncmp(tokens[0], "L", 2) != 0)
    {
        printf("[ERROR] Luz pontual: esperado identificador 'L', encontrado '%s'\n", tokens[0]);
        print_error("Luz pontual: esperado identificador 'L'", tokens);
    }

    light->position = parse_vec3(tokens[1]);
    printf("[DEBUG] Luz pontual: posição -> (%.2f, %.2f, %.2f)\n",
           light->position.x, light->position.y, light->position.z);

    light->brightness = ft_atof(tokens[2]);
    printf("[DEBUG] Luz pontual: brilho -> %.2f\n", light->brightness);
    if (light->brightness < 0 || light->brightness > 1)
    {
        printf("[ERROR] Luz pontual: brilho fora do intervalo 0-1: %.2f\n", light->brightness);
        print_error("Luz pontual: brilho deve estar entre 0 e 1", tokens);
    }

    light->color = parse_color(tokens[3]);
    printf("[DEBUG] Luz pontual: cor -> (R: %.2f, G: %.2f, B: %.2f)\n",
           light->color.r, light->color.g, light->color.b);

    light->specular_color = make_color(1.0f, 1.0f, 1.0f);
    printf("[DEBUG] Luz pontual: cor especular setada para branco (1.0, 1.0, 1.0)\n");

    ft_free_split(tokens);
    return 0;
}


int add_point_light(t_scene *scene, t_point_light *new_light)
{
    t_point_light *tmp;

    printf("[DEBUG] add_point_light: adicionando luz na cena\n");

    tmp = realloc(scene->point_lights, sizeof(t_point_light) * (scene->n_point_lights + 1));
    if(!tmp)
    {
        printf("[ERROR] Falha ao alocar memória para luz pontual\n");
        print_error("Falha ao alocar memória para luz pontual", NULL);
    }

    scene->point_lights = tmp;
    scene->point_lights[scene->n_point_lights] = *new_light;
    scene->n_point_lights++;

    printf("[DEBUG] add_point_light: luz adicionada com sucesso. Total agora: %d\n", scene->n_point_lights);
    return 0;
}

int parse_point_light(const char *line, t_scene *scene)
{
    t_point_light light;

    printf("[DEBUG] parse_point_light: linha -> '%s'\n", line);

    if (parse_point_light_line(line, &light) != 0)
    {
        printf("[ERROR] parse_point_light_line falhou\n");
        return -1;
    }

    int res = add_point_light(scene, &light);
    printf("[DEBUG] parse_point_light: luz adicionada, resultado = %d\n", res);
    return res;
}

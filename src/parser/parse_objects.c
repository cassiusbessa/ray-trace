/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 10:18:13 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
int parse_sphere(const char *line, t_scene *scene)
{
    char **tokens = ft_split(line, ' ');
    if (!tokens || count_tokens(tokens) < 4)
    {
        ft_free_split(tokens);
        return 0;
    }

    t_sphere *sphere = malloc(sizeof(t_sphere));
    if (!sphere)
    {
        ft_free_split(tokens);
        return 0;
    }

    sphere->center = parse_vec3(tokens[1]);
    sphere->radius = parse_float(tokens[2]);
    sphere->color  = clamp_color(parse_color(tokens[3]));

    printf("[DEBUG parse_sphere] center=(%.2f, %.2f, %.2f), radius=%.2f, color=(%.2f, %.2f, %.2f)\n",
           sphere->center.x, sphere->center.y, sphere->center.z,
           sphere->radius,
           sphere->color.r, sphere->color.g, sphere->color.b);

    t_object *obj = create_object(SPHERE, sphere, sphere->color, tokens, 4, 5, 6, 7);
    if (!obj)
    {
        free(sphere);
        ft_free_split(tokens);
        return 0;
    }

    add_object_to_scene(scene, obj);
    ft_free_split(tokens);
    return 1;
}

int parse_plane(const char *line, t_scene *scene)
{
    char **tokens = ft_split(line, ' ');
    if (!tokens || count_tokens(tokens) < 4)
    {
        ft_free_split(tokens);
        return 0;
    }

    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
    {
        ft_free_split(tokens);
        return 0;
    }

    plane->point  = parse_vec3(tokens[1]);
    plane->normal = vec3_normalize(parse_vec3(tokens[2]));
    plane->color  = clamp_color(parse_color(tokens[3]));

    printf("[DEBUG parse_plane] point=(%.2f, %.2f, %.2f), normal=(%.2f, %.2f, %.2f), color=(%.2f, %.2f, %.2f)\n",
           plane->point.x, plane->point.y, plane->point.z,
           plane->normal.x, plane->normal.y, plane->normal.z,
           plane->color.r, plane->color.g, plane->color.b);

    t_object *obj = create_object(PLANE, plane, plane->color, tokens, 4, 5, 6, 7);
    if (!obj)
    {
        free(plane);
        ft_free_split(tokens);
        return 0;
    }

    add_object_to_scene(scene, obj);
    ft_free_split(tokens);
    return 1;
}

int parse_cylinder(const char *line, t_scene *scene)
{
    char **tokens = ft_split(line, ' ');
    if (!tokens || count_tokens(tokens) < 6) // no mínimo até a cor
    {
        ft_free_split(tokens);
        return 0;
    }

    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
    {
        ft_free_split(tokens);
        return 0;
    }

    cylinder->center = parse_vec3(tokens[1]);
    cylinder->axis   = vec3_normalize(parse_vec3(tokens[2]));
    cylinder->radius = parse_float(tokens[3]);
    cylinder->height = parse_float(tokens[4]);
    cylinder->color  = clamp_color(parse_color(tokens[5]));

    printf("[DEBUG parse_cylinder] center=(%.2f, %.2f, %.2f), axis=(%.2f, %.2f, %.2f), radius=%.2f, height=%.2f, color=(%.2f, %.2f, %.2f)\n",
           cylinder->center.x, cylinder->center.y, cylinder->center.z,
           cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
           cylinder->radius, cylinder->height,
           cylinder->color.r, cylinder->color.g, cylinder->color.b);

    t_object *obj = create_object(CYLINDER, cylinder, cylinder->color, tokens, 6, 7, 8, 9);
    if (!obj)
    {
        free(cylinder);
        ft_free_split(tokens);
        return 0;
    }

    add_object_to_scene(scene, obj);
    ft_free_split(tokens);
    return 1;
}

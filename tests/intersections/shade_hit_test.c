/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:07:21 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 19:02:07 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"



// Teste do primeiro cenário: shading intersection normal (raio externo)
static int test_shade_intersection_outside(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    // Primeira esfera do mundo
    t_object shape = w.objects->head->object;

    // Cria interseção manual
    t_intersection_node i = {.t = 4.0, .object = &shape, .next = NULL};
    t_comps comps = prepare_computations(i, r);

    // Chama shade_hit
    t_rgb color = shade_hit(&w, comps);

    errors += test_check(equal_rgb(color, new_rgb(0.38066f, 0.47583f, 0.2855f)),
                         "Color mismatch in shade_hit (outside) test");
    if (errors)
        test_failure("Shade intersection (outside) test failed\n");

    return errors;
}

// Teste do segundo cenário: shading intersection from inside (raio interno)
static int test_shade_intersection_inside(void)
{
    int errors = 0;

    t_world w = default_world();

    // Limpa apenas a lista de luzes antiga
    if (w.lights)
    {
        t_point_light_node *curr = w.lights->head;
        while (curr)
        {
            t_point_light_node *next = curr->next;
            free(curr);
            curr = next;
        }
        w.lights->head = NULL;
    }

    // Adiciona a nova luz dentro do objeto
    t_point_light new_light = new_point_light(point(0, 0.25, 0), new_rgb(1, 1, 1));
    add_light_to_world(&w, new_light);

    // Raio partindo do centro da segunda esfera
    t_ray r = create_ray(point(0, 0, 0), vector(0, 0, 1));

    // Segunda esfera do mundo (head->next)
    t_object *shape = &w.objects->head->next->object;

    // Interseção manual
    t_intersection_node i = {.t = 0.5, .object = shape, .next = NULL};
    t_comps comps = prepare_computations(i, r);

    // Chama shade_hit
    t_rgb color = shade_hit(&w, comps);

    errors += test_check(equal_rgb(color, new_rgb(0.90498f, 0.90498f, 0.90498f)),
                         "Color mismatch in shade_hit (inside) test");

    if (errors)
        test_failure("Shade intersection (inside) test failed\n");

    // libera apenas a lista de luzes e objetos
    free_world(&w);

    return errors;
}


// Função principal de testes de shade_hit
int run_test_hit_shade(void)
{
    int errors = 0;

    errors += test_shade_intersection_outside();
    errors += test_shade_intersection_inside();

    if (errors)
        test_failure("Shade hit tests failed\n");
    else
        test_success("Shade hit tests passed\n");

    return errors;
}

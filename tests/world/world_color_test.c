/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_color_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:12:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 00:08:41 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

// ----------------------------
// Teste shade_hit - luz padrão
// ----------------------------
static int test_shade_hit_default_light(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    t_object shape = w.objects->head->object; // primeira esfera
    t_simple_intersection i = make_simple_intersection(4.0f, &shape);
    t_comps comps = prepare_computations(i, r);

    // Passando o endereço de w
    t_rgb c = shade_hit(&w, comps);

    errors += test_check(float_equal(c.r,   0.38066f), "shade_hit red component");
    errors += test_check(float_equal(c.g, 0.47583f), "shade_hit green component");
    errors += test_check(float_equal(c.b,  0.2855f), "shade_hit blue component");

    free_world(&w);

    if (errors) test_failure("shade_hit default light failed");
    else        test_success("shade_hit default light succeeded");

    return errors;
}

// ----------------------------
// Teste shade_hit - dentro da esfera
// ----------------------------
static int test_shade_hit_inside(void)
{
    int errors = 0;

    t_world w = default_world();  // <- agora é por valor

    // mover luz para dentro
    free(w.lights);
    w.lights = malloc(sizeof(t_point_light_list));
    w.lights->head = w.lights->tail = NULL;
    w.lights->count = 0;
    add_light_to_world(&w, new_point_light(point(0, 0.25f, 0), new_rgb(1, 1, 1)));

    t_ray r = create_ray(point(0, 0, 0), vector(0, 0, 1));
    t_object shape = w.objects->head->next->object; // segunda esfera
    t_simple_intersection i = make_simple_intersection(0.5f, &shape);
    t_comps comps = prepare_computations(i, r);

    t_rgb c = shade_hit(&w, comps);  // <- passar endereço

    errors += test_check(float_equal(c.r,   0.90498f), "shade_hit inside red component");
    errors += test_check(float_equal(c.g, 0.90498f), "shade_hit inside green component");
    errors += test_check(float_equal(c.b,  0.90498f), "shade_hit inside blue component");

    free_world(&w);

    if (errors) test_failure("shade_hit inside failed");
    else        test_success("shade_hit inside succeeded");

    return errors;
}


// ----------------------------
// Teste color_at - raio que não acerta nada
// ----------------------------

static int test_color_at_miss(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 1, 0)); // não acerta nada

    t_rgb c = color_at(w, r);

    errors += test_check(float_equal(c.r, 0.0f), "color_at miss red");
    errors += test_check(float_equal(c.g, 0.0f), "color_at miss green");
    errors += test_check(float_equal(c.b, 0.0f), "color_at miss blue");

    free_world(&w);

    if (errors) test_failure("color_at miss failed");
    else        test_success("color_at miss succeeded");

    return errors;
}

// ----------------------------
// Teste color_at - raio que acerta a esfera externa
// ----------------------------
static int test_color_at_hit(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));

    t_rgb c = color_at(w, r);

    errors += test_check(float_equal(c.r,   0.38066f), "color_at hit red");
    errors += test_check(float_equal(c.g, 0.47583f), "color_at hit green");
    errors += test_check(float_equal(c.b, 0.2855f),  "color_at hit blue");

    free_world(&w);

    if (errors) test_failure("color_at hit failed");
    else        test_success("color_at hit succeeded");

    return errors;
}

// ----------------------------
// Teste color_at - interseção atrás do raio
// ----------------------------
static int test_color_at_behind(void)
{
    int errors = 0;

    t_world w = default_world();

    t_object outer = w.objects->head->object;
    if (outer.type == SPHERE)
        ((t_sphere *)outer.data)->material.ambient = 1.0f;

    t_object inner = w.objects->head->next->object;
    if (inner.type == SPHERE)
        ((t_sphere *)inner.data)->material.ambient = 1.0f;

    t_ray r = create_ray(point(0, 0, 0.75f), vector(0, 0, -1));

    t_rgb c = color_at(w, r);

    errors += test_check(
        float_equal(c.r, ((t_sphere *)inner.data)->material.color.r) &&
        float_equal(c.g, ((t_sphere *)inner.data)->material.color.g) &&
        float_equal(c.b, ((t_sphere *)inner.data)->material.color.b),
        "color_at behind returns inner.material.color"
    );

    free_world(&w);

    if (errors) test_failure("color_at behind failed");
    else        test_success("color_at behind succeeded");

    return errors;
}

// ----------------------------
// Função principal para rodar os novos testes
// ----------------------------
int run_world_color_tests(void)
{
    int errors = 0;

    errors += test_shade_hit_default_light();
    errors += test_shade_hit_inside();
    errors += test_color_at_miss();
    errors += test_color_at_hit();
    errors += test_color_at_behind();

    if (errors)
        test_failure("World color tests failed");
    else
        test_success("World color tests passed");

    return errors;
}


/*

color_at(world, ray)
│
├─> intersect_world(world, ray)         // calcula todas as interseções do raio com os objetos do mundo
│    └─> para cada objeto:
│         └─> intersect(object, ray)   // retorna lista de interseções de um objeto
│
├─> hit(intersections)                  // seleciona a interseção com menor t positivo
│    └─> se não houver interseção → retorna cor preta (0,0,0)
│
└─> prepare_computations(intersection, ray)
     ├─> comps.t = intersection.t
     ├─> comps.object = intersection.object
     ├─> comps.point = position(ray, t)           // ponto da interseção
     ├─> comps.eyev = -ray.direction              // direção do olho/camera
     ├─> comps.normalv = normal_at(object, point) // normal na superfície
     └─> se dot(comps.normalv, comps.eyev) < 0:
            comps.inside = TRUE
            comps.normalv = -comps.normalv
        senão:
            comps.inside = FALSE
│
└─> shade_hit(world, comps)
     ├─> para cada light no mundo:
     │    └─> lighting(comps.object.material, light, comps.point, comps.eyev, comps.normalv)
     │
     └─> soma as cores de todas as luzes (ou retorna a única cor se tiver 1 luz)
│
└─> retorna a cor final

color_at
   |
   +--> intersect_world
   |       |
   |       +--> intersect(object_i, ray)
   |
   +--> hit(intersections)
   |
   +--> prepare_computations
   |       |
   |       +--> position, eyev, normalv, inside
   |
   +--> shade_hit
           |
           +--> lighting(material, light, point, eyev, normalv)
           |
           +--> cor final
*/
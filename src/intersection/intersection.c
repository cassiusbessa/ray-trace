/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:23:40 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 10:14:13 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection  new_intersection(int count, float enter, float exit, void *object)
{
    t_intersection  result;

    result.count = count;
    result.enter = enter;
    result.exit = exit;
    result.object = object;
    return (result);
}

static t_bool float_equal(float a, float b)
{
    return (fabsf(a - b) < EPSILON);
}

t_bool equal_intersections(t_intersection i1, t_intersection i2)
{
    return (i1.count == i2.count
        && float_equal(i1.enter, i2.enter)
        && float_equal(i1.exit, i2.exit));
}

t_intersections intersections(t_intersection i1, t_intersection i2)
{
    t_intersections xs;
    xs.list = malloc(2 * sizeof(t_intersection));
    xs.list[0] = i1;
    xs.list[1] = i2;
    xs.count = 2;
    return xs;
}

t_intersections intersections_n(int count, ...)
{
    va_list args;
    t_intersections xs;
    int i;

    xs.list = malloc(count * sizeof(t_intersection));
    if (!xs.list)
    {
        xs.count = 0;
        return xs;
    }

    xs.count = count;
    va_start(args, count);
    for (i = 0; i < count; i++)
        xs.list[i] = va_arg(args, t_intersection);
    va_end(args);

    return xs;
}


int intersect_object(t_ray *ray, t_object *obj, t_intersection *out)
{
    if (!obj)
        return 0;
    if (obj->type == SPHERE)
        return intersect_sphere(ray, obj, out);
    /*if (obj->type == PLANE)
        return intersect_plane(ray, obj, out);
    if (obj->type == CYLINDER)
        return intersect_cylinder(ray, obj, out);*/
    return 0;
}

/*
[ Criar raio ] 
    |
    v
[ Criar objeto ]
    |
    v
[ intersect_object(ray, obj, &hit) ]   <-- função genérica
    |
    |-- Se obj->type == SPHERE --> [ intersect_sphere(ray, obj, &hit) ]
    |                               |
    |                               v
    |                         [ intersect_ray_sphere(ray, t_sphere *) ]
    |                               |
    |                               v
    |                        [ ft_quadratic(a,b,c) ]
    |                               |
    |                               v
    |                         [ new_intersection(count, t1, t2, object) ]
    |                               |
    |                               v
    |                       retorna t_intersection para intersect_sphere
    |
    |-- Se obj->type == PLANE  --> [ intersect_plane(...) ]
    |
    |-- Se obj->type == CYLINDER --> [ intersect_cylinder(...) ]
    |
    v
[ retorna t_intersection preenchido ]
    |
    v
[ t_intersection contém ]
    - count (0,1,2)
    - enter (t1)
    - exit (t2)
    - object (ponteiro para t_object ou t_sphere)


[ intersect_object(ray, obj1, &hit1) ]
[ intersect_object(ray, obj2, &hit2) ]
          |
          v
[ intersections(hit1, hit2) ]  --> t_intersections
          |
          v
[ xs.list[0] = hit1, xs.list[1] = hit2 ]
[ xs.count = 2 ]


Descrição do fluxo de interseção de raios

Um raio (t_ray) é lançado na cena.

Cada objeto (t_object) é testado com a função genérica intersect_object.

intersect_object chama a função específica do tipo do objeto:

Esfera → intersect_sphere → intersect_ray_sphere

Plano → intersect_plane

Cilindro → intersect_cylinder

Cada função retorna um t_intersection, com:

count → número de interseções (0, 1 ou 2)

enter → primeira interseção ao longo do raio

exit → segunda interseção

object → ponteiro para o objeto atingido

Para múltiplos objetos, podemos agrupar os resultados em t_intersections.

A partir desses dados, é possível determinar qual objeto é visível, calcular cores, sombras e reflexões.
*/
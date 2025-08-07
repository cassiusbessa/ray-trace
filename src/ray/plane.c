/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/07 12:16:49 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_plane	plane(void)
{
	t_plane	p;

	p.transform = identity_matrix(4);
	p.normal = vector_tuple(0, 1, 0);  // Normal apontando pra cima (eixo Y)
	p.position = point_tuple(0, 0, 0);    // Um ponto qualquer no plano, geralmente a origem
	return (p);
}

void	set_transform_plane(t_plane *p, t_matrix t)
{
	p->transform = t;
}


t_intersection *intersect_plane(t_plane *plane, t_ray ray, int *count)
{
    float denom, t;
    t_intersection *xs;
    t_ray r2;

    // 1. Transformar o raio para o espaço local do plano
    r2 = transform_ray(ray, matrix_inverse(plane->transform));

    // 2. Calcular o denominador: direção do raio ⋅ normal do plano (no espaço local)
    denom = vector_dot(r2.direction, plane->normal);
    if (fabs(denom) < 1e-6)
    {
        *count = 0;
        return NULL;
    }

    // 3. Calcular t
    t = vector_dot(subtract_tuple(plane->position, r2.origin), plane->normal) / denom;

    if (t < 0)
    {
        *count = 0;
        return NULL;
    }

    // 4. Alocar interseção
    xs = malloc(sizeof(t_intersection));
    if (!xs)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    xs[0].t = t;
    xs[0].object = plane;
    *count = 1;
    return xs;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/31 21:52:01 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder	cylinder(void)
{
	t_cylinder	c;

	c.transform = identity_matrix(4);
	c.diameter = 1.0f;           // padrão 1
	c.height = 1.0f;             // padrão 1
	// eixo do cilindro no espaço local é eixo Y, então nem precisa guardar
	// mas se quiser, pode definir:
	// c.axis = vector(0, 1, 0);

	return (c);
}

void	set_transform_cylinder(t_cylinder *c, t_matrix t)
{
	c->transform = t;
}

t_intersection *intersect_cylinder(t_cylinder *cylinder, t_ray ray, int *count)
{
    // 1) Transformar o raio para o espaço local do cilindro
    t_ray r2 = transform_ray(ray, inverse(cylinder->transform));
    
    float radius = cylinder->diameter / 2.0f;
    float height = cylinder->height;

    // No espaço local, cilindro centrado em (0,0,0), eixo y = (0,1,0)
    // Eixo do cilindro
    t_tuple axis = vector(0, 1, 0); // eixo y local
    
    t_tuple oc = r2.origin; // raio já está no espaço local
    t_tuple d = r2.direction;

    float a, b, c, discriminant;
    float t0, t1;
    float y0, y1;
    t_intersection *xs = malloc(4 * sizeof(t_intersection)); // lateral + tampas
    int idx = 0;

    if (!xs)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Projeção da direção e origem no plano perpendicular ao eixo y
    t_tuple d_proj = sub(d, multiply(axis, dot(d, axis)));
    t_tuple oc_proj = sub(oc, multiply(axis, dot(oc, axis)));

    a = dot(d_proj, d_proj);
    b = 2 * dot(d_proj, oc_proj);
    c = dot(oc_proj, oc_proj) - radius * radius;

    discriminant = b * b - 4 * a * c;

    *count = 0;
    if (discriminant < 0)
    {
        free(xs);
        return NULL;
    }

    float sqrt_disc = sqrtf(discriminant);
    t0 = (-b - sqrt_disc) / (2 * a);
    t1 = (-b + sqrt_disc) / (2 * a);

    // Checar interseções laterais dentro da altura
    y0 = dot(add(oc, multiply(d, t0)), axis);
    if (y0 >= 0 && y0 <= height)
    {
        xs[idx].t = t0;
        xs[idx].object = cylinder;
        idx++;
    }
    y1 = dot(add(oc, multiply(d, t1)), axis);
    if (y1 >= 0 && y1 <= height)
    {
        xs[idx].t = t1;
        xs[idx].object = cylinder;
        idx++;
    }
    // Interseção com tampas
    // Base inferior (y = 0)
    float t_base;
    float denom = dot(d, axis);
    if (fabs(denom) > 1e-6)
    {
        t_base = (0 - dot(oc, axis)) / denom;
        t_tuple p = add(oc, multiply(d, t_base));
        t_tuple v = sub(p, multiply(axis, dot(p, axis))); // vetor da projeção no plano da tampa
        if (t_base >= 0 && dot(v, v) <= radius * radius)
        {
            xs[idx].t = t_base;
            xs[idx].object = cylinder;
            idx++;
        }
    }
    // Base superior (y = height)
    if (fabs(denom) > 1e-6)
    {
        t_base = (height - dot(oc, axis)) / denom;
        t_tuple p = add(oc, multiply(d, t_base));
        t_tuple v = sub(p, multiply(axis, dot(p, axis)));
        if (t_base >= 0 && dot(v, v) <= radius * radius)
        {
            xs[idx].t = t_base;
            xs[idx].object = cylinder;
            idx++;
        }
    }

    if (idx == 0)
    {
        free(xs);
        *count = 0;
        return NULL;
    }

    *count = idx;
    return xs;
}

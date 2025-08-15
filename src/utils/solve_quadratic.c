/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:02:46 by cassius           #+#    #+#             */
/*   Updated: 2025/08/15 12:26:12 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_bool float_equal(float a, float b)
{
    return (fabsf(a - b) < EPSILON);
}

static float	ft_discriminant(float a, float b, float c)
{
	return (b * b - 4.0f * a * c);
}

t_quad	ft_quadratic(float a, float b, float c)
{
	t_quad	result;
	float	delta;
	float	sqrt_delta;

	result.count = 0;
	result.x1 = 0.0f;
	result.x2 = 0.0f;
	if (a == 0.0f)
		return (result);
	delta = ft_discriminant(a, b, c);
	if (delta < 0.0f)
		return (result);
	if (delta == 0.0f)
	{
		result.count = 1;
		result.x1 = -b / (2.0f * a);
		result.x2 = result.x1;
		return (result);
	}
	sqrt_delta = sqrt(delta);
	result.count = 2;
	result.x1 = (-b - sqrt_delta) / (2.0f * a);
	result.x2 = (-b + sqrt_delta) / (2.0f * a);
	return (result);
}

//Livro considera que a quantidade de pontos sempre vai ser 2, mesmo que seja tangente
t_intersection	ft_quad_to_intersection(t_quad q, void *object)
{
	t_intersection	result;

    if (q.count == 0)
    {
        result = new_intersection(0, 0.0f, 0.0f, NULL);
        return (result);
    }
    result = new_intersection(2, q.x1, q.x2, object);
	return (result);
}
t_quad solve_quadratic_for_sphere(t_ray ray, t_sphere *sphere)
{
    (void)sphere; // evita warning de parâmetro não usado

    t_tuple sphere_to_ray;
    float a, b, c;

    sphere_to_ray = sub_tuples(ray.origin, point(0, 0, 0));
    a = vector_dot_product(ray.direction, ray.direction);
    b = 2.0f * vector_dot_product(ray.direction, sphere_to_ray);
    c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1.0f; // esfera unitária
    return ft_quadratic(a, b, c);
}

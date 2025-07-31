/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/30 18:47:37 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection	*intersect(t_sphere *s, t_ray r, int *count)
{
	t_ray		r2;
	t_tuple		sphere_to_ray;
	float		a, b, c, discriminant;
	t_intersection	*xs;

	r2 = transform_ray(r, inverse(s->transform));
	sphere_to_ray = sub(r2.origin, point(0, 0, 0));
	a = dot(r2.direction, r2.direction);
	b = 2 * dot(r2.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		*count = 0;
		return (NULL);
	}
	xs = malloc(2 * sizeof(t_intersection));
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].object = s;
	xs[1].object = s;
	*count = 2;
	return (xs);
}

t_intersection	*hit(t_intersection *xs, int count)
{
	int	i;
	t_intersection	*hit = NULL;

	for (i = 0; i < count; i++)
	{
		if (xs[i].t >= 0 && (!hit || xs[i].t < hit->t))
			hit = &xs[i];
	}
	return (hit);
}

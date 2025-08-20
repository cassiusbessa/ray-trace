/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 22:09:48 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_sphere	new_sphere(t_tuple center, float radius)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.transform = identity_matrix(4);
	sphere.material = new_material_default();
	return (sphere);
}

t_intersection	intersect_ray_sphere(t_ray ray, t_sphere *sphere)
{
	t_tuple			oc;
	t_quad			q;
	t_intersection	i;

	// Declarando variáveis
	float a, b, c;
	// Inicializando
	oc = sub_tuples(ray.origin, sphere->center);
	a = vector_dot_product(ray.direction, ray.direction);
	b = 2.0f * vector_dot_product(ray.direction, oc);
	c = vector_dot_product(oc, oc) - (sphere->radius * sphere->radius);
	q = ft_quadratic(a, b, c);
	i = ft_quad_to_intersection(q, (void *)sphere);
	return (i);
}

int	intersect_sphere(t_ray *ray, t_object *obj, t_intersection *out)
{
	if (!ray || !obj || !out)
		return (0);
	*out = intersect_ray_sphere(*ray, (t_sphere *)obj->data);
	return (out->count > 0);
}
/*
// Inicializa uma t_intersection
static t_intersection	init_intersection(void)
{
	t_intersection	i;
	t_intersections	xs;
	t_sphere		*sphere;
	t_ray			local_ray;
	t_quad			q;
	t_intersections	xs;

	i.count = 0;
	i.enter = 0.0f;
	i.exit = 0.0f;
	i.object = NULL;
	return (i);
}*/
/*
// Inicializa um t_intersections
static t_intersections	init_intersections(void)
{
	xs.count = 0;
	xs.list = NULL;
	return (xs);
}*/
t_intersections	intersect_sphere_all(t_ray *ray, t_object *obj)
{
	t_sphere	*sphere;
	t_intersections	xs;
	t_ray			local_ray;
	t_quad			q;

	sphere = (t_sphere *)obj->data;
	xs.count = 0;
	xs.list = NULL;
	if (!ray || !sphere)
		return (xs);
	local_ray = transform_ray(*ray, invert_matrix(sphere->transform));
	q = solve_quadratic_for_sphere(local_ray, sphere);
	xs.list = malloc(2 * sizeof(t_intersection));
	if (!xs.list)
		return (xs);
	xs.count = 2;
	xs.list[0] = new_intersection(0, q.x1, 0, obj);
	xs.list[1] = new_intersection(0, q.x2, 0, obj);
	return (xs);
}

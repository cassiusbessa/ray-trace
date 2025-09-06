/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 23:52:50 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_ray	get_local_ray_sphere(t_ray ray, t_object *obj, int *success)
{
	t_matrix	inv;
	t_ray		local_ray;

	inv = invert_matrix(obj->transform, success);
	if (!*success)
		return (ray);
	local_ray = transform_ray(ray, inv, success);
	free_matrix(inv);
	return (local_ray);
}

static t_sphere_calc	compute_sphere_params(t_ray local_ray)
{
	t_sphere_calc	calc;
	t_tuple			sphere_to_ray;

	sphere_to_ray = local_ray.origin;
	calc.a = vector_dot_product(local_ray.direction, local_ray.direction);
	calc.b = 2.0f * vector_dot_product(local_ray.direction, sphere_to_ray);
	calc.c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1.0f;
	return (calc);
}

static void	add_sphere_intersections(float discriminant, t_sphere_calc calc,
		t_intersection_list *list, t_object *obj)
{
	float	sqrt_disc;
	float	t1;
	float	t2;

	if (discriminant < 0.0f)
		return ;
	sqrt_disc = sqrtf(discriminant);
	t1 = (-calc.b - sqrt_disc) / (2 * calc.a);
	t2 = (-calc.b + sqrt_disc) / (2 * calc.a);
	add_node_ordered(t1, list, obj);
	add_node_ordered(t2, list, obj);
}

t_intersection_list	*intersect_ray_sphere(t_ray ray, t_object *obj)
{
	t_ray				local_ray;
	t_intersection_list	*list;
	t_sphere_calc		calc;
	float				discriminant;
	int					success;

	success = 0;
	local_ray = get_local_ray_sphere(ray, obj, &success);
	if (!success)
		return (new_intersection_list());
	calc = compute_sphere_params(local_ray);
	discriminant = calc.b * calc.b - 4 * calc.a * calc.c;
	list = new_intersection_list();
	if (!list)
		return (NULL);
	add_sphere_intersections(discriminant, calc, list, obj);
	return (list);
}

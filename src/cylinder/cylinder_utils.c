/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:09:44 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:28:52 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_cylinder_material(t_object *obj, t_rgb color)
{
	obj->material = new_material_default();
	obj->material.color = color;
	obj->material.specular = 1.0f;
	obj->material.shininess = 300.0f;
	obj->material.diffuse = 0.7f;
}

t_matrix	compute_cylinder_transform(t_tuple center, t_tuple orientation,
		float radius, float half_height)
{
	t_matrix	scale;
	t_matrix	rotate;
	t_matrix	translate;
	t_matrix	tmp;
	t_matrix	transform;

	scale = scaling_matrix(radius, half_height, radius);
	rotate = orientation_matrix(orientation);
	translate = translation_matrix(center.x, center.y, center.z);
	tmp = matrix_multiply_by_matrix(rotate, scale);
	transform = matrix_multiply_by_matrix(translate, tmp);
	free_matrix(scale);
	free_matrix(rotate);
	free_matrix(translate);
	free_matrix(tmp);
	return (transform);
}

t_bool	transform_ray_to_local(t_ray ray, t_object *obj, t_ray *local_ray)
{
	int			success;
	t_matrix	inv;

	inv = invert_matrix(obj->transform, &success);
	if (!success)
		return (FALSE);
	*local_ray = transform_ray(ray, inv, &success);
	free_matrix(inv);
	return (success);
}

void	intersect_cylinder_sides(t_ray ray, t_object *obj,
		t_intersection_list *list)
{
	t_cylinder	*cyl;
	t_quad		q;
	int			i;
	float		t;
	float		y;

	cyl = (t_cylinder *)obj->data;
	q = solve_quadratic_for_cylinder(ray, cyl->radius);
	i = 0;
	while (i < q.count)
	{
		if (i == 0)
			t = q.x1;
		else
			t = q.x2;
		y = ray.origin.y + t * ray.direction.y;
		if (y >= -cyl->height / 2.0f && y <= cyl->height / 2.0f)
			add_node_ordered(t, list, obj);
		i++;
	}
}

void	intersect_cylinder_caps(t_ray ray, t_object *obj,
		t_intersection_list *list)
{
	t_cylinder	*cyl;
	float		t_top;
	float		t_bottom;

	cyl = (t_cylinder *)obj->data;
	if (!cyl->closed || fabs(ray.direction.y) < EPSILON)
		return ;
	t_top = (cyl->height / 2.0f - ray.origin.y) / ray.direction.y;
	if (((ray.origin.x + t_top * ray.direction.x) * (ray.origin.x + t_top
				* ray.direction.x) + (ray.origin.z + t_top * ray.direction.z)
			* (ray.origin.z + t_top * ray.direction.z)) <= cyl->radius
		* cyl->radius)
		add_node_ordered(t_top, list, obj);
	t_bottom = (-cyl->height / 2.0f - ray.origin.y) / ray.direction.y;
	if (((ray.origin.x + t_bottom * ray.direction.x) * (ray.origin.x + t_bottom
				* ray.direction.x) + (ray.origin.z + t_bottom * ray.direction.z)
			* (ray.origin.z + t_bottom * ray.direction.z)) <= cyl->radius
		* cyl->radius)
		add_node_ordered(t_bottom, list, obj);
}

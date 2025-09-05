/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:14:44 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 17:35:31 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_cylinder	new_cylinder(void)
{
	t_cylinder	cyl;

	cyl.radius = 1.0f;
	cyl.height = 2.0f;
	cyl.closed = 0;
	return (cyl);
}

t_cylinder	*init_cylinder(float diameter, float height, t_bool closed)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	*cylinder = new_cylinder();
	cylinder->radius = diameter / 2.0f;
	cylinder->height = height;
	cylinder->closed = closed;
	return (cylinder);
}

t_object	new_cylinder_object(t_tuple center, t_tuple orientation,
		float diameter, float height, t_rgb color, t_bool closed)
{
	t_cylinder	*cylinder;
	t_object	obj;
	t_matrix	transform;

	cylinder = init_cylinder(diameter, height, closed);
	if (!cylinder)
		return ((t_object){0});
	obj = new_object(CYLINDER, cylinder);
	set_cylinder_material(&obj, color);
	transform = compute_cylinder_transform(center, orientation,
			cylinder->radius, height / 2.0f);
	set_object_transform(&obj, transform);
	return (obj);
}

t_intersection_list	*intersect_ray_cylinder(t_ray ray, t_object *obj)
{
	t_ray local_ray;
	t_intersection_list *list = new_intersection_list();
	if (!list)
		return (NULL);

	if (!transform_ray_to_local(ray, obj, &local_ray))
		return (list);

	intersect_cylinder_sides(local_ray, obj, list);
	intersect_cylinder_caps(local_ray, obj, list);

	return (list);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/03 18:28:00 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_object_transform(t_object *obj, t_matrix m)
{
	t_matrix	t;
	if (!obj)
		return ;
	
	// Compose the new transformation with the current one
	t = matrix_multiply_by_matrix(m, obj->transform);
	
	// Free the current transform matrix
	free_matrix(obj->transform);
	
	// Set the composed transform
	obj->transform = t;
	
	// Free the input matrix since we're done with it
	free_matrix(m);
}

t_object	new_object(t_object_type type, void *data)
{
	t_object obj;

	obj.type = type;
	obj.data = data;
	obj.transform = identity_matrix(4); // Initialize with identity matrix
	obj.material = new_material_default(); // Initialize with default material
	return (obj);
}

void	free_object(t_object *obj)
{
	if (!obj)
		return ;
	
	// Free the transform matrix
	free_matrix(obj->transform);
	
	// Free the specific object data
	if (obj->type == SPHERE)
	{
		free_sphere((t_sphere *)obj->data);
	}
	else if (obj->type == CYLINDER)
	{
		free(obj->data);
	}
	
}


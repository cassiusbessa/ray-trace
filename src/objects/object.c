/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/03 09:58:54 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_object_transform(t_object *obj, t_matrix m)
{
	if (!obj)
		return ;
	
	// Free the current transform matrix
	free_matrix(obj->transform);
	
	// Set the new transform
	obj->transform = m;
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
		free_sphere((t_sphere *)obj->data);
}

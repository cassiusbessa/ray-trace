/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 19:01:05 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_object_transform(t_object *obj, t_matrix m)
{
	t_matrix	t;

	if (!obj)
		return ;
	t = matrix_multiply_by_matrix(m, obj->transform);
	free_matrix(obj->transform);
	obj->transform = t;
	free_matrix(m);
}

t_object	new_object(t_object_type type, void *data)
{
	t_object	obj;

	obj.type = type;
	obj.data = data;
	obj.transform = identity_matrix(4);
	obj.material = new_material_default();
	return (obj);
}

void	free_object(t_object *obj)
{
	if (!obj)
		return ;
	free_matrix(obj->transform);
	if (obj->type == SPHERE)
		free_sphere((t_sphere *)obj->data);
	else if (obj->type == CYLINDER)
		free(obj->data);
}

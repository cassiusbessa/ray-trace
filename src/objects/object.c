/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/27 23:18:10 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_object_transform(t_object *obj, t_matrix m)
{
	if (!obj || !obj->data)
		return ;
	if (obj->type == SPHERE)
		((t_sphere *)obj->data)->transform = matrix_multiply_by_matrix(((t_sphere *)obj->data)->transform, m);
	// else if (obj->type == PLANE) ...
}

t_object	new_object(t_object_type type, void *data)
{
	t_object obj;

	obj.type = type;
	obj.data = data;
	return (obj);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:46:50 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 20:18:46 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// static t_tuple normal_at_sphere(t_sphere s, t_tuple p)
// {
//     t_tuple normal;

//     normal = sub_tuples(p, s.center);
//     normal.w = 0;
//     return (normalize_vector(normal));
// }

t_tuple	normal_at(t_object o, t_tuple world_point)
{
	t_tuple	 object_point;
	t_tuple	 object_normal;
	t_tuple	 world_normal;
	t_matrix inv;
	t_matrix invT;

	if (o.type == SPHERE)
	{
		t_sphere *s = (t_sphere *)o.data;

		// Ponto do mundo -> espaço do objeto
		inv = invert_matrix(s->transform);
		object_point = matrix_multiply_by_tuple(inv, world_point);

		// Normal no espaço do objeto (para esfera centrada na origem)
		object_normal = sub_tuples(object_point, point(0, 0, 0));

		// Normal do objeto -> mundo (usa transpose(inverse(M)))
		invT = transpose_matrix(inv);
		world_normal = matrix_multiply_by_tuple(invT, object_normal);

		// É vetor
		world_normal.w = 0;

		// Normaliza
		world_normal = normalize_vector(world_normal);

		// Libera se suas matrizes usam heap
		free_matrix(invT);
		free_matrix(inv);
	}
	else
		world_normal = vector(0, 0, 0);

	return (world_normal);
}



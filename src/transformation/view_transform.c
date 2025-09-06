/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/09/05 20:14:52 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_basis	compute_orthonormal_basis(t_tuple from, t_tuple to,
		t_tuple up)
{
	t_basis	basis;
	t_tuple	upn;

	basis.forward = normalize_vector(sub_tuples(to, from));
	upn = normalize_vector(up);
	basis.left = vector_cross_product(basis.forward, upn);
	if (magnitude_of_vector(basis.left) < 1e-6)
	{
		if (fabs(upn.y) > 0.99f)
			upn = vector(0, 0, 1);
		else
			upn = vector(0, 1, 0);
		basis.left = vector_cross_product(basis.forward, upn);
	}
	basis.left = normalize_vector(basis.left);
	basis.true_up = vector_cross_product(basis.left, basis.forward);
	return (basis);
}

static t_matrix	build_view_matrix(t_tuple forward, t_tuple left,
		t_tuple true_up)
{
	t_matrix	orientation;

	orientation = new_matrix(4, 4);
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[0][3] = 0.0f;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[1][3] = 0.0f;
	orientation.data[2][0] = -forward.x;
	orientation.data[2][1] = -forward.y;
	orientation.data[2][2] = -forward.z;
	orientation.data[2][3] = 0.0f;
	orientation.data[3][0] = 0.0f;
	orientation.data[3][1] = 0.0f;
	orientation.data[3][2] = 0.0f;
	orientation.data[3][3] = 1.0f;
	return (orientation);
}

static t_matrix	view_orientation(t_tuple from, t_tuple to, t_tuple up)
{
	t_basis		basis;
	t_matrix	orientation;

	basis = compute_orthonormal_basis(from, to, up);
	orientation = build_view_matrix(basis.forward, basis.left, basis.true_up);
	return (orientation);
}

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_matrix	orientation;
	t_matrix	translation;
	t_matrix	result;

	orientation = view_orientation(from, to, up);
	translation = translation_matrix(-from.x, -from.y, -from.z);
	result = matrix_multiply_by_matrix(orientation, translation);
	free_matrix(orientation);
	free_matrix(translation);
	return (result);
}

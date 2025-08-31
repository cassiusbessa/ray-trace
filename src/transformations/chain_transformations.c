/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnascime <fnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:00:00 by cassius           #+#    #+#             */
/*   Updated: 2025/08/29 20:01:42 by fnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix	chain_transformations(t_transform_params params)
{
	t_matrix	translation;
	t_matrix	rotation_x;
	t_matrix	rotation_y;
	t_matrix	rotation_z;
	t_matrix	scaling;
	t_matrix	temp1;
	t_matrix	temp2;
	t_matrix	temp3;
	t_matrix	final_transform;

	translation = translation_matrix(params.translation[0], \
									params.translation[1], \
									params.translation[2]);
	rotation_x = rotation_x_matrix(params.rotation[0]);
	rotation_y = rotation_y_matrix(params.rotation[1]);
	rotation_z = rotation_z_matrix(params.rotation[2]);
	scaling = scaling_matrix(params.scaling[0], \
							params.scaling[1], \
							params.scaling[2]);
	temp1 = matrix_multiply_by_matrix(translation, rotation_x);
	temp2 = matrix_multiply_by_matrix(temp1, rotation_y);
	free_matrix(temp1);
	temp3 = matrix_multiply_by_matrix(temp2, rotation_z);
	free_matrix(temp2);
	final_transform = matrix_multiply_by_matrix(temp3, scaling);
	free_matrix(temp3);
	free_matrix(translation);
	free_matrix(rotation_x);
	free_matrix(rotation_y);
	free_matrix(rotation_z);
	free_matrix(scaling);
	return (final_transform);
}

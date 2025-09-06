/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:00:00 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 20:30:10 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	free_transform_matrices(t_transform_matrices *mats)
{
	free_matrix(mats->translation);
	free_matrix(mats->rotation_x);
	free_matrix(mats->rotation_y);
	free_matrix(mats->rotation_z);
	free_matrix(mats->scaling);
}

static void	init_basic_matrices(t_transform_params params,
		t_transform_matrices *mats)
{
	mats->translation = translation_matrix(params.translation[0],
			params.translation[1], params.translation[2]);
	mats->rotation_x = rotation_x_matrix(params.rotation[0]);
	mats->rotation_y = rotation_y_matrix(params.rotation[1]);
	mats->rotation_z = rotation_z_matrix(params.rotation[2]);
	mats->scaling = scaling_matrix(params.scaling[0], params.scaling[1],
			params.scaling[2]);
	mats->temp1 = new_matrix(0, 0);
	mats->temp2 = new_matrix(0, 0);
	mats->temp3 = new_matrix(0, 0);
	mats->final_transform = new_matrix(0, 0);
}

t_matrix	chain_transformations(t_transform_params params)
{
	t_transform_matrices	mats;

	init_basic_matrices(params, &mats);
	mats.temp1 = matrix_multiply_by_matrix(mats.translation, mats.rotation_x);
	mats.temp2 = matrix_multiply_by_matrix(mats.temp1, mats.rotation_y);
	free_matrix(mats.temp1);
	mats.temp3 = matrix_multiply_by_matrix(mats.temp2, mats.rotation_z);
	free_matrix(mats.temp2);
	mats.final_transform = matrix_multiply_by_matrix(mats.temp3, mats.scaling);
	free_matrix(mats.temp3);
	free_transform_matrices(&mats);
	return (mats.final_transform);
}

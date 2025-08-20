/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:55:38 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 22:46:14 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_material	new_material_default(void)
{
	t_material	material;

	material.color = new_rgb(1, 1, 1);
	material.ambient = 0.1f;
	material.diffuse = 0.9f;
	material.specular = 0.9f;
	material.shininess = 200.0f;
	return (material);
}

t_bool	equal_materials(t_material m1, t_material m2)
{
	return (equal_rgb(m1.color, m2.color) && float_equal(m1.ambient, m2.ambient)
		&& float_equal(m1.diffuse, m2.diffuse) && float_equal(m1.specular,
			m2.specular) && float_equal(m1.shininess, m2.shininess));
}
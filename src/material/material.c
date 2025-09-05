/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:55:38 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 17:55:45 by emorshhe         ###   ########.fr       */
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

t_bool equal_materials(t_material m1, t_material m2)
{
    if (!equal_rgb(m1.color, m2.color))
        return FALSE;
    if (!float_equal(m1.ambient, m2.ambient))
        return FALSE;
    if (!float_equal(m1.diffuse, m2.diffuse))
        return FALSE;
    if (!float_equal(m1.specular, m2.specular))
        return FALSE;
    if (!float_equal(m1.shininess, m2.shininess))
        return FALSE;

    return TRUE;
}

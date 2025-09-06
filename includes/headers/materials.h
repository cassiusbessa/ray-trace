/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:40:44 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:42:06 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "colors.h"

typedef struct s_material
{
	t_rgb	color;
	float	ambient;
	float	diffuse;
	float	specular;
	float	shininess;
}			t_material;

// Material operations
t_material	new_material_default(void);
t_bool		equal_materials(t_material m1, t_material m2);

#endif

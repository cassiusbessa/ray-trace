/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:21:33 by cassius           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/05 23:27:28 by emorshhe         ###   ########.fr       */
=======
/*   Updated: 2025/09/05 23:39:09 by cassius          ###   ########.fr       */
>>>>>>> 2f79df98099aec4e9e1b7476b3b26a77dc1e95d8
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_sphere	new_sphere(t_tuple center, float radius)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	return (sphere);
}

void	free_sphere(t_sphere *s)
{
	if (!s)
		return ;
	free(s);
}

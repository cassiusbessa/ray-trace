/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:11:53 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 08:39:20 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_rgb diffuse_component(t_material m, t_point_light light, double light_dot_normal)
{
	t_rgb   effective_color;
	t_rgb   diffuse;

	effective_color = multiply_rgb_by_rgb(m.color, light.intensity);
    diffuse = multiply_rgb_by_scalar(effective_color, m.diffuse * light_dot_normal);

	return (diffuse);
}


static t_rgb specular_component(t_material m, t_point_light light, t_tuple lightv, t_tuple eyev)
{
	t_tuple reflectv;
	double reflect_dot_eye;
	double factor;
	t_rgb specular;

	reflectv = reflect(multiply_tuple_by_scalar(lightv, -1), vector(0, 0, -1));
	reflect_dot_eye = fmax(vector_dot_product(reflectv, eyev), 0);

	if (reflect_dot_eye <= 0)
		specular = new_rgb(0, 0, 0);
	else
	{
		factor = pow(reflect_dot_eye, m.shininess);
		specular = multiply_rgb_by_scalar(light.intensity, m.specular * factor);
	}
	return (specular);
}

static t_rgb calc_diff_spec(t_material m, t_point_light light, t_tuple lightv, t_tuple eyev)
{
	t_rgb   diffuse;
	t_rgb   specular;
	t_rgb   result;
	double  light_dot_normal;

	light_dot_normal = vector_dot_product(lightv, vector(0, 0, -1));
	if (light_dot_normal < 0)
    	result = new_rgb(0, 0, 0);
	else
	{
		diffuse = diffuse_component(m, light, light_dot_normal);
		specular = specular_component(m, light, lightv, eyev);
		result = add_rgb(diffuse, specular);
	}

    return (result);
}

t_rgb lighting(t_material m, t_point_light light, t_tuple position, t_tuple eyev)
{
    t_rgb ambient, diff_spec, result;
    t_tuple lightv;

    // direção da luz
    lightv = normalize_vector(sub_tuples(light.position, position));

    // componente ambiente
    ambient = multiply_rgb_by_scalar(multiply_rgb_by_rgb(m.color, light.intensity), m.ambient);

    // componente difusa + especular
    diff_spec = calc_diff_spec(m, light, lightv, eyev);

    // soma final
    result = add_rgb(ambient, diff_spec);

    return result;
}






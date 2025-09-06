/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:11:53 by cassius           #+#    #+#             */
/*   Updated: 2025/09/05 17:55:47 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_rgb	diffuse_component(t_material m, t_point_light light,
		t_lighting_vectors vectors)
{
	double	light_dot_normal;
	t_rgb	effective_color;
	t_rgb	diffuse;

	if (vectors.lightv.x == 0 && vectors.lightv.y == 0 && vectors.lightv.z == 0)
		return (new_rgb(0, 0, 0));
	light_dot_normal = vector_dot_product(vectors.normalv, vectors.lightv);
	if (light_dot_normal < 0.0 || isnan(light_dot_normal))
		light_dot_normal = 0.0;
	effective_color = multiply_rgb_by_rgb(m.color, light.intensity);
	diffuse = multiply_rgb_by_scalar(effective_color, m.diffuse
			* light_dot_normal);
	return (diffuse);
}

t_rgb	specular_component(t_material m, t_point_light light,
		t_lighting_vectors vectors)
{
	t_rgb	specular;
	double	light_dot_normal;
	t_tuple	reflectv;
	double	reflect_dot_eye;
	double	factor;

	specular = new_rgb(0, 0, 0);
	if (vectors.lightv.x == 0 && vectors.lightv.y == 0 && vectors.lightv.z == 0)
		return (specular);
	light_dot_normal = vector_dot_product(vectors.normalv, vectors.lightv);
	if (light_dot_normal <= 0)
		return (specular);
	reflectv = reflect(multiply_tuple_by_scalar(vectors.lightv, -1),
			vectors.normalv);
	reflect_dot_eye = vector_dot_product(reflectv, vectors.eyev);
	if (reflect_dot_eye <= 0 || isnan(reflect_dot_eye))
		return (specular);
	factor = pow(reflect_dot_eye, m.shininess);
	specular = multiply_rgb_by_scalar(light.intensity, m.specular * factor);
	return (specular);
}

t_rgb	calc_diff_spec(t_material m, t_point_light light,
		t_lighting_vectors vectors)
{
	t_rgb	diffuse;
	t_rgb	specular;
	t_rgb	result;

	diffuse = diffuse_component(m, light, vectors);
	specular = specular_component(m, light, vectors);
	result = add_rgb(diffuse, specular);
	return (result);
}

t_rgb	lighting(t_material m, t_point_light light, t_lighting_params params)
{
	t_lighting_vectors	vectors;
	t_rgb				ambient;
	t_rgb				diff_spec;
	t_rgb				result;

	vectors.lightv = normalize_vector(sub_tuples(light.position,
				params.position));
	vectors.eyev = params.eyev;
	vectors.normalv = params.normalv;
	ambient = multiply_rgb_by_scalar(multiply_rgb_by_rgb(m.color,
				light.intensity), m.ambient);
	if (params.in_shadow)
		return (ambient);
	diff_spec = calc_diff_spec(m, light, vectors);
	result = add_rgb(ambient, diff_spec);
	return (result);
}

t_rgb	lighting_no_ambient(t_material m, t_point_light light,
		t_lighting_params params)
{
	t_lighting_vectors	vectors;
	t_rgb				diff_spec;

	if (params.in_shadow)
		return (new_rgb(0, 0, 0));
	vectors.lightv = normalize_vector(sub_tuples(light.position,
				params.position));
	vectors.eyev = params.eyev;
	vectors.normalv = params.normalv;
	diff_spec = calc_diff_spec(m, light, vectors);
	return (diff_spec);
}

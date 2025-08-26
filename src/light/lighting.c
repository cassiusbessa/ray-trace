/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:11:53 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 20:51:19 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// ----------------------------
// Diffuse component
// ----------------------------
t_rgb diffuse_component(t_material m, t_point_light light,
    t_tuple lightv, t_tuple normalv)
{
    if (lightv.x == 0 && lightv.y == 0 && lightv.z == 0)
        return new_rgb(0, 0, 0);

    double light_dot_normal = vector_dot_product(normalv, lightv);
    if (light_dot_normal < 0.0 || isnan(light_dot_normal))
        light_dot_normal = 0.0;

    t_rgb effective_color = multiply_rgb_by_rgb(m.color, light.intensity);
    t_rgb diffuse = multiply_rgb_by_scalar(effective_color, m.diffuse * light_dot_normal);

    return diffuse;
}

// ----------------------------
// Specular component
// ----------------------------
t_rgb specular_component(t_material m, t_point_light light,
     t_tuple lightv, t_tuple eyev, t_tuple normalv)
{
    t_rgb specular = new_rgb(0, 0, 0);

    if (lightv.x == 0 && lightv.y == 0 && lightv.z == 0)
        return specular;

    double light_dot_normal = vector_dot_product(normalv, lightv);
    if (light_dot_normal <= 0)
        return specular;

    t_tuple reflectv = reflect(multiply_tuple_by_scalar(lightv, -1), normalv);
    double reflect_dot_eye = vector_dot_product(reflectv, eyev);

    if (reflect_dot_eye <= 0 || isnan(reflect_dot_eye))
        return specular;

    double factor = pow(reflect_dot_eye, m.shininess);
    specular = multiply_rgb_by_scalar(light.intensity, m.specular * factor);

    return specular;
}
// ----------------------------
// Calc diffuse + specular
// ----------------------------
t_rgb calc_diff_spec(t_material m, t_point_light light,
 t_tuple lightv, t_tuple eyev, t_tuple normalv)
{
	t_rgb diffuse = diffuse_component(m, light, lightv, normalv);
	t_rgb specular = specular_component(m, light, lightv, eyev, normalv);
	t_rgb result = add_rgb(diffuse, specular);

	return result;
}










t_rgb lighting(t_material m, t_point_light light, t_tuple position,
    t_tuple eyev, t_tuple normalv, int in_shadow)
{
    t_tuple lightv = normalize_vector(sub_tuples(light.position, position));

    // componente ambiente
    t_rgb ambient = multiply_rgb_by_scalar(
        multiply_rgb_by_rgb(m.color, light.intensity), m.ambient);

    if (in_shadow)
        return ambient;

    // componentes difusa + especular
    t_rgb diff_spec = calc_diff_spec(m, light, lightv, eyev, normalv);

    // soma final
    t_rgb result = add_rgb(ambient, diff_spec);
    return result;
}

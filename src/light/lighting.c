/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:11:53 by cassius           #+#    #+#             */
/*   Updated: 2025/08/25 23:35:46 by emorshhe         ###   ########.fr       */
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

    printf("[DEBUG] diffuse_component: effective_color=(%.3f,%.3f,%.3f) diffuse=(%.3f,%.3f,%.3f) light_dot_normal=%.3f\n",
        effective_color.r, effective_color.g, effective_color.b,
        diffuse.r, diffuse.g, diffuse.b, light_dot_normal);

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

    printf("[DEBUG] specular_component: reflect_dot_eye=%.3f specular=(%.3f,%.3f,%.3f)\n",
        reflect_dot_eye, specular.r, specular.g, specular.b);

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

	printf("[DEBUG] calc_diff_spec: result=(%.3f,%.3f,%.3f)\n",
		result.r, result.g, result.b);

	return result;
}










t_rgb lighting(t_material m, t_point_light light, t_tuple position,
    t_tuple eyev, t_tuple normalv, int in_shadow)
{
    t_tuple lightv = normalize_vector(sub_tuples(light.position, position));

    // componente ambiente
    t_rgb ambient = multiply_rgb_by_scalar(
        multiply_rgb_by_rgb(m.color, light.intensity), m.ambient);

    if (in_shadow) {
        printf("[DEBUG lighting] in_shadow=1, return ambient only: (%.3f,%.3f,%.3f)\n",
            ambient.r, ambient.g, ambient.b);
        return ambient;
    }

    // componentes difusa + especular
    t_rgb diff_spec = calc_diff_spec(m, light, lightv, eyev, normalv);

    // soma final
    t_rgb result = add_rgb(ambient, diff_spec);

    printf("[DEBUG lighting] ambient=(%.3f,%.3f,%.3f), diff_spec=(%.3f,%.3f,%.3f), "
           "result=(%.3f,%.3f,%.3f)\n",
        ambient.r, ambient.g, ambient.b,
        diff_spec.r, diff_spec.g, diff_spec.b,
        result.r, result.g, result.b);

    return result;
}

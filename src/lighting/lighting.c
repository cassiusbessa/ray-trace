/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/07 12:59:47 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple reflect(t_tuple in, t_tuple normal)
{
	double		dot_prod;
	t_tuple		scaled_normal;
	t_tuple		result;

	dot_prod = vector_dot(in, normal);
	scaled_normal = multiply_tuple(normal, 2 * dot_prod);
	result = subtract_tuple(in, scaled_normal);
	return (result);
}

t_color calculate_diffuse(t_material material, t_color effective_color, float light_dot_normal)
{
    t_color result;

    if (light_dot_normal < 0)
        result = create_color(0, 0, 0);
    else
        result = multiply_color_scalar(effective_color, material.diffuse * light_dot_normal);

    return result;
}

t_color calculate_specular(t_material material, t_light light, t_tuple reflectv, t_tuple eyev)
{
    float reflect_dot_eye; 
    t_color result;

    reflect_dot_eye = vector_dot(reflectv, eyev);

    if (reflect_dot_eye <= 0)
        result = create_color(0, 0, 0);
    else
        result = multiply_color_scalar(light.intensity,
            material.specular * powf(reflect_dot_eye, material.shininess));

    return (result);
}


t_color lighting_diffuse_specular(t_material_light_params mlp, t_lighting_context ctx)
{
    t_tuple lightv;
    float light_dot_normal;
    t_color effective_color;
    t_color diffuse;
    t_color result;
    t_tuple reflectv;
    t_color specular;

    lightv = normalize_vector(subtract_tuple(mlp.light.position, ctx.position));
    light_dot_normal = vector_dot(lightv, ctx.normalv);
    effective_color = multiply_color(mlp.material.color, mlp.light.intensity);
    diffuse = calculate_diffuse(mlp.material, effective_color, light_dot_normal);
    if (light_dot_normal < 0)
        result = diffuse;
    else
    {
        reflectv = reflect(negate_tuple(lightv), ctx.normalv);
        specular = calculate_specular(mlp.material, mlp.light, reflectv, ctx.eyev);
        result = add_color(diffuse, specular);
    }
    return (result);
}

t_color lighting(t_material_light_params mlp, t_lighting_context ctx)
{
    t_color effective_color;
    t_color ambient;
    t_color result;
    t_color diff_spec;
    
    effective_color = multiply_color(mlp.material.color, mlp.light.intensity);
    ambient = multiply_color_scalar(effective_color, mlp.material.ambient);
    if (ctx.in_shadow)
        result = ambient;
    else
    {
        diff_spec = lighting_diffuse_specular(mlp, ctx);
        result = add_color(ambient, diff_spec);
    }
    return (result);
}


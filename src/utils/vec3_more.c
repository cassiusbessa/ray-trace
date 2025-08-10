/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/08/10 09:40:36 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* src/utils/vec3_more.c */
double	vec3_length(t_vec3 v)
{
    double result;
    double length;

    result = vec3_dot(v, v);
    length = sqrt(result);

    return (length);
}

t_vec3	vec3_normalize(t_vec3 v)
{
    t_vec3 normalize;
    double len;

    len = vec3_length(v);
    if(len < EPS)
        return (vec3(0, 0, 0));
    normalize = vec3_scale(v, 1.0/len);
    return (normalize);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return (result);
}

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n)
{
    // v é vetor incidente (direção da luz para o ponto)
    // n é a normal (deve estar normalizada)
    double dot;
    t_vec3 result;

    dot = vec3_dot(v, n);
    result =  vec3_sub(vec3_scale(n, 2 * dot), v);
    return (result);
}

// Retorna 1 se há refração, 0 se reflexão total interna (sem refração)
int vec3_refract(t_vec3 incident, t_vec3 normal, float eta, t_vec3 *refracted)
{
    float cosi = fmax(-1.0f, fmin(1.0f, vec3_dot(incident, normal)));
    float etai = 1.0f;
    float etat = eta;
    t_vec3 n = normal;

    if (cosi < 0) {
        cosi = -cosi;
    } else {
        // Estamos dentro do objeto, inverter índices e normal
        float temp = etai;
        etai = etat;
        etat = temp;
        n = vec3_scale(normal, -1);
    }

    float eta_ratio = etai / etat;
    float k = 1.0f - eta_ratio * eta_ratio * (1.0f - cosi * cosi);

    if (k < 0)
        return 0; // reflexão total interna

    *refracted = vec3_add(
        vec3_scale(incident, eta_ratio),
        vec3_scale(n, eta_ratio * cosi - sqrtf(k))
    );
    *refracted = vec3_normalize(*refracted);
    return 1;
}

t_color vec3_scale_color(t_color c, float s)
{
    t_color result;
    result.r = c.r * s;
    result.g = c.g * s;
    result.b = c.b * s;
    return result;
}

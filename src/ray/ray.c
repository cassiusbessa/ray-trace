/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 20:23:13 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Cria um novo raio a partir de uma origem e direção
t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

// Calcula a posição de um ponto ao longo do raio para um parâmetro t
t_tuple	ray_position(t_ray r, float t)
{
	t_tuple	result;

	result = add_tuples(r.origin, multiply_tuple_by_scalar(r.direction, t));
	return (result);
}

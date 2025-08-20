/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:54:58 by cassius           #+#    #+#             */
/*   Updated: 2025/08/18 20:59:21 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_tuple	reflect(t_tuple v, t_tuple n)
{
	float dot_product;

	dot_product = vector_dot_product(v, n);
	return (vector(v.x - 2 * dot_product * n.x, v.y - 2 * dot_product * n.y, v.z
			- 2 * dot_product * n.z));
}
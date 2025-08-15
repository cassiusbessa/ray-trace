/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:02:46 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 22:17:09 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quadratic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:05:00 by yourlogin         #+#    #+#             */
/*   Updated: 2025/08/14 22:05:00 by yourlogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static float	ft_discriminant(float a, float b, float c)
{
	return (b * b - 4.0f * a * c);
}

t_quad	ft_quadratic(float a, float b, float c)
{
	t_quad	result;
	float	delta;
	float	sqrt_delta;

	result.count = 0;
	result.x1 = 0.0f;
	result.x2 = 0.0f;
	if (a == 0.0f)
		return (result);
	delta = ft_discriminant(a, b, c);
	if (delta < 0.0f)
		return (result);
	if (delta == 0.0f)
	{
		result.count = 1;
		result.x1 = -b / (2.0f * a);
		result.x2 = result.x1;
		return (result);
	}
	sqrt_delta = sqrt(delta);
	result.count = 2;
	result.x1 = (-b - sqrt_delta) / (2.0f * a);
	result.x2 = (-b + sqrt_delta) / (2.0f * a);
	return (result);
}

//Livro considera que a quantidade de pontos sempre vai ser 2, mesmo que seja tangente
t_intersection	ft_quad_to_intersection(t_quad q)
{
	t_intersection	result;

    if (q.count == 0)
    {
        result = new_intersection(0, 0.0, 0.0);
        return (result);
    }
    result = new_intersection(2, q.x1, q.x2);
	return (result);
}
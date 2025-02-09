/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:34:47 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 22:41:43 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	magnitude_of_vector(t_touple *t)
{
    if (t->w == TRUE)
    {
        printf("❌ ERROR: The tuple is a point, not a vector.\n");
        return (-1);
    }
	return (sqrt(pow(t->x, 2) + pow(t->y, 2) + pow(t->z, 2)));
}

t_touple    *normalize_vector(t_touple *t)
{
    t_touple    *normalized;
    float       magnitude;

    magnitude = magnitude_of_vector(t);
    normalized = malloc(sizeof(t_touple));
    if (!normalized)
        return (NULL);
    normalized->x = t->x / magnitude;
    normalized->y = t->y / magnitude;
    normalized->z = t->z / magnitude;
    normalized->w = 0;
    return (normalized);
}
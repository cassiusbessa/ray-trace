/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:41:18 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:42:21 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATIC_H
# define QUADRATIC_H

# include "intersections.h"

typedef struct s_quad
{
	int			count;
	float		x1;
	float		x2;
}				t_quad;

// Quadratic solver
t_quad			ft_quadratic(float a, float b, float c);
t_intersection	ft_quad_to_intersection(t_quad q, void *object);
t_bool			float_equal(float a, float b);
t_quad			solve_quadratic_for_cylinder(t_ray ray, float radius);

#endif

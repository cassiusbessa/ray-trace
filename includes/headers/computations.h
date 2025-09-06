/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:40:20 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:41:56 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTATIONS_H
# define COMPUTATIONS_H

# include "rays.h"
# include "world.h"

typedef struct s_comps
{
	float		t;
	t_object	*object;
	t_tuple		point;
	t_tuple		over_point;
	t_tuple		eyev;
	t_tuple		normalv;
	t_bool		inside;
}				t_comps;

// Computation operations
t_comps			prepare_computations(t_intersection_node i, t_ray r);
t_rgb			shade_hit(t_world *world, t_comps comps);
t_rgb			color_at(t_world *world, t_ray ray);
float			compute_dynamic_epsilon(t_object *obj, t_tuple point);
void			set_inside(t_tuple *normalv, t_tuple eyev, t_bool *inside);

#endif

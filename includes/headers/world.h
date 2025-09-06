/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:41:47 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:42:29 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "intersections.h"
# include "lights.h"
# include "objects.h"

typedef struct s_ambient
{
	float				ratio;
	t_rgb				color;
}						t_ambient;

typedef struct s_world
{
	t_point_light_list	*lights;
	t_object_list		*objects;
	t_ambient			ambient;
}						t_world;

// World operations
t_world					new_world(void);
t_world					new_world_with_ambient(t_ambient ambient);
void					add_object_to_world(t_world *world, t_object object);
void					add_light_to_world(t_world *world, t_point_light light);
t_world					default_world(void);
void					free_world(t_world *world);
t_intersection_list		*intersect_world(t_world *world, t_ray *ray);
t_bool					is_shadowed(t_world *world, t_tuple point);

#endif

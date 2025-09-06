/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:41:12 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:44:17 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "tuples.h"

typedef struct s_plane
{
	t_tuple	point;
	t_tuple	normal;
}					t_plane;

t_plane				*new_plane(t_tuple point, t_tuple normal);
t_tuple				normal_at_plane(t_object *obj, t_tuple world_point);
t_intersection_list	*intersect_ray_plane(t_ray ray, t_object *obj);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 22:15:09 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../utils/libft/libft.h"
# include <math.h>
# include <stdio.h>

# define EPSILON 0.0001

typedef int	t_bool;

# define TRUE 1
# define FALSE 0

typedef struct s_touple
{
	float	x;
	float	y;
	float	z;
	int		w;
}			t_touple;

t_touple	*new_touple(float x, float y, float z, t_bool is_point);
void		print_touple(t_touple *t);
t_touple	*add_touple(t_touple *t1, t_touple *t2);
t_touple	*sub_touple(t_touple *t1, t_touple *t2);
t_touple	*multiply_tuple_by_scalar(t_touple *t, float scalar);
float		magnitude_of_vector(t_touple *t);

#endif
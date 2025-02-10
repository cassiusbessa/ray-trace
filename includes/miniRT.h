/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/10 01:39:22 by cassius          ###   ########.fr       */
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

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}			t_tuple;

t_tuple	*new_tuple(float x, float y, float z, t_bool is_point);
void		print_tuple(t_tuple *t);
t_tuple	*add_tuples(t_tuple *t1, t_tuple *t2);
t_tuple	*sub_tuples(t_tuple *t1, t_tuple *t2);
t_tuple	*multiply_tuple_by_scalar(t_tuple *t, float scalar);
float		magnitude_of_vector(t_tuple *t);
t_tuple    *normalize_vector(t_tuple *t);
float    vector_dot_product(t_tuple *t1, t_tuple *t2);
t_tuple    *vector_cross_product(t_tuple *t1, t_tuple *t2);




#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:23:24 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 20:10:04 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../utils/libft/libft.h"
# include <stdio.h>
# include <math.h>

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

#endif
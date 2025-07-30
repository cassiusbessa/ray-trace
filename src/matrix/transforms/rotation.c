/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/30 09:05:38 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix rotation_x(float r)
{
	t_matrix m = identity_matrix(4);
	m.data[1][1] = cos(r);
	m.data[1][2] = -sin(r);
	m.data[2][1] = sin(r);
	m.data[2][2] = cos(r);
	return m;
}

t_matrix rotation_y(float r)
{
	t_matrix m = identity_matrix(4);
	m.data[0][0] = cos(r);
	m.data[0][2] = sin(r);
	m.data[2][0] = -sin(r);
	m.data[2][2] = cos(r);
	return m;
}

t_matrix rotation_z(float r)
{
	t_matrix m = identity_matrix(4);
	m.data[0][0] = cos(r);
	m.data[0][1] = -sin(r);
	m.data[1][0] = sin(r);
	m.data[1][1] = cos(r);
	return m;
}
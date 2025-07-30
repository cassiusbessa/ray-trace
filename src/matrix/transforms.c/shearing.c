/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:31:06 by mc-m-el-          #+#    #+#             */
/*   Updated: 2025/07/30 09:04:48 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_matrix m = identity_matrix(4);
	m.data[0][1] = xy;
	m.data[0][2] = xz;
	m.data[1][0] = yx;
	m.data[1][2] = yz;
	m.data[2][0] = zx;
	m.data[2][1] = zy;
	return m;
}
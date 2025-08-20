/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactor_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:41:07 by cassius           #+#    #+#             */
/*   Updated: 2025/08/14 13:09:27 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double	cofactor_matrix(t_matrix matrix, int row, int col)
{
	double	minor;
	double	cofactor;

	minor = minor_matrix(matrix, row, col); // calcula o menor
	if ((row + col) % 2 == 0)
		cofactor = minor;
	else
		cofactor = -minor;
	return (cofactor);
}

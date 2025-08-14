/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:53:57 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 19:59:45 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

double minor_matrix(t_matrix matrix, int row, int col)
{
    t_matrix sub;
    double det;

    // Cria a submatriz removendo a linha 'row' e a coluna 'col'
    sub = submatrix(matrix, row, col);

    // Calcula o determinante da submatriz
    det = determinant_matrix(sub);

    // Libera a memória da submatriz
    free_matrix(sub);

    // Retorna o determinante como double
    return det;
}

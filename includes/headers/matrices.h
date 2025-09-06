/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:40:48 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/06 00:42:09 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# include "tuples.h"

typedef struct s_matrix
{
	int			size;
	float		**data;
}				t_matrix;

// Matrix creation and basic operations
t_matrix		new_matrix(int rows, int cols);
t_matrix		identity_matrix(int size);
void			print_matrix(t_matrix matrix);
void			free_matrix(t_matrix matrix);
t_bool			equal_matrix(t_matrix m1, t_matrix m2);

// Matrix multiplication
t_matrix		matrix_multiply_by_matrix(t_matrix a, t_matrix b);
t_tuple			matrix_multiply_by_tuple(t_matrix m, t_tuple t);

// Matrix transformations
t_matrix		transpose_matrix(t_matrix matrix);
t_matrix		invert_matrix(t_matrix matrix, int *success);

// Matrix determinants and submatrices
int				matrix_determinant_2x2(t_matrix matrix);
t_matrix		submatrix(t_matrix matrix, int row, int col);
double			minor_matrix(t_matrix matrix, int row, int col);
double			cofactor_matrix(t_matrix matrix, int row, int col);
double			determinant_matrix(t_matrix a);

t_matrix		orientation_matrix(t_tuple orientation);

typedef struct s_transform_matrices
{
	t_matrix	translation;
	t_matrix	rotation_x;
	t_matrix	rotation_y;
	t_matrix	rotation_z;
	t_matrix	scaling;
	t_matrix	temp1;
	t_matrix	temp2;
	t_matrix	temp3;
	t_matrix	final_transform;
}				t_transform_matrices;

#endif

#ifndef MATRICES_H
# define MATRICES_H

# include "tuples.h"

typedef struct s_matrix
{
	int		size;
	float	**data;
}	t_matrix;

// Matrix creation and basic operations
t_matrix	new_matrix(int rows, int cols);
t_matrix	identity_matrix(int size);
void		print_matrix(t_matrix matrix);
void		free_matrix(t_matrix matrix);
t_bool		equal_matrix(t_matrix m1, t_matrix m2);

// Matrix multiplication
t_matrix	matrix_multiply_by_matrix(t_matrix a, t_matrix b);
t_tuple		matrix_multiply_by_tuple(t_matrix m, t_tuple t);

// Matrix transformations
t_matrix	transpose_matrix(t_matrix matrix);
t_matrix	invert_matrix(t_matrix matrix, int *success);

// Matrix determinants and submatrices
int			matrix_determinant_2x2(t_matrix matrix);
t_matrix	submatrix(t_matrix matrix, int row, int col);
double		minor_matrix(t_matrix matrix, int row, int col);
double		cofactor_matrix(t_matrix matrix, int row, int col);
double		determinant_matrix(t_matrix a);

#endif

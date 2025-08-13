#include "../../includes/miniRT.h"

int minor_matrix(t_matrix matrix, int row, int col)
{
    int minor;
    t_matrix sub;

    sub = submatrix(matrix, row, col);
    minor = matrix_determinant_2x2(sub);
    free_matrix(sub);
    return (minor);
}
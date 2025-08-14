#include "../../includes/miniRT.h"

int minor_matrix(t_matrix matrix, int row, int col)
{
    int minor;
    t_matrix sub;

    sub = submatrix(matrix, row, col);
    minor = determinant_matrix(sub);
    free_matrix(sub);
    return (minor);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invertible_matrix_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:21:33 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/26 01:15:54 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

// Matriz invertível (det != 0)
static t_matrix matrix_a(void)
{
    t_matrix matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = 6;   matrix.data[0][1] = 4;   matrix.data[0][2] = 4;   matrix.data[0][3] = 4;
    matrix.data[1][0] = 5;   matrix.data[1][1] = 5;   matrix.data[1][2] = 7;   matrix.data[1][3] = 6;
    matrix.data[2][0] = 4;   matrix.data[2][1] = -9;  matrix.data[2][2] = 3;   matrix.data[2][3] = -7;
    matrix.data[3][0] = 9;   matrix.data[3][1] = 1;   matrix.data[3][2] = 7;   matrix.data[3][3] = -6;
    return (matrix);
}

// Matriz não-invertível (det = 0)
static t_matrix matrix_b(void)
{
    t_matrix matrix;

    matrix = new_matrix(4, 4);
    matrix.data[0][0] = -4;  matrix.data[0][1] = 2;   matrix.data[0][2] = -2;  matrix.data[0][3] = -3;
    matrix.data[1][0] = 9;   matrix.data[1][1] = 6;   matrix.data[1][2] = 2;   matrix.data[1][3] = 6;
    matrix.data[2][0] = 0;   matrix.data[2][1] = -5;  matrix.data[2][2] = 1;   matrix.data[2][3] = -5;
    matrix.data[3][0] = 0;   matrix.data[3][1] = 0;   matrix.data[3][2] = 0;   matrix.data[3][3] = 0;
    return (matrix);
}

// Matriz de entrada A
static t_matrix matrix_a1(void)
{
    t_matrix m = new_matrix(4, 4);
    m.data[0][0] = 8;  m.data[0][1] = -5; m.data[0][2] = 9;  m.data[0][3] = 2;
    m.data[1][0] = 7;  m.data[1][1] = 5;  m.data[1][2] = 6;  m.data[1][3] = 1;
    m.data[2][0] = -6; m.data[2][1] = 0;  m.data[2][2] = 9;  m.data[2][3] = 6;
    m.data[3][0] = -3; m.data[3][1] = 0;  m.data[3][2] = -9; m.data[3][3] = -4;
    return m;
}

// Matriz inversa esperada
static t_matrix matrix_a1_inverse(void)
{
    t_matrix m = new_matrix(4, 4);
    m.data[0][0] = -0.15385; m.data[0][1] = -0.15385; m.data[0][2] = -0.28205; m.data[0][3] = -0.53846;
    m.data[1][0] = -0.07692; m.data[1][1] = 0.12308;  m.data[1][2] = 0.02564;  m.data[1][3] = 0.03077;
    m.data[2][0] = 0.35897;  m.data[2][1] = 0.35897;  m.data[2][2] = 0.43590;  m.data[2][3] = 0.92308;
    m.data[3][0] = -0.69231; m.data[3][1] = -0.69231; m.data[3][2] = -0.76923; m.data[3][3] = -1.92308;
    return m;
}

// Matriz de entrada A
static t_matrix matrix_a2(void)
{
    t_matrix m = new_matrix(4, 4);
    m.data[0][0] = 9;  m.data[0][1] = 3;  m.data[0][2] = 0;  m.data[0][3] = 9;
    m.data[1][0] = -5; m.data[1][1] = -2; m.data[1][2] = -6; m.data[1][3] = -3;
    m.data[2][0] = -4; m.data[2][1] = 9;  m.data[2][2] = 6;  m.data[2][3] = 4;
    m.data[3][0] = -7; m.data[3][1] = 6;  m.data[3][2] = 6;  m.data[3][3] = 2;
    return m;
}

// Matriz inversa esperada
static t_matrix matrix_a2_inverse(void)
{
    t_matrix m = new_matrix(4, 4);
    m.data[0][0] = -0.04074; m.data[0][1] = -0.07778; m.data[0][2] = 0.14444;  m.data[0][3] = -0.22222;
    m.data[1][0] = -0.07778; m.data[1][1] = 0.03333;  m.data[1][2] = 0.36667;  m.data[1][3] = -0.33333;
    m.data[2][0] = -0.02901; m.data[2][1] = -0.14630; m.data[2][2] = -0.10926; m.data[2][3] = 0.12963;
    m.data[3][0] = 0.17778;  m.data[3][1] = 0.06667;  m.data[3][2] = -0.26667; m.data[3][3] = 0.33333;
    return m;
}
static int test_matrix_inversion(t_matrix (*mat_func)(void), t_matrix (*inv_func)(void), const char *msg)
{
    t_matrix original;
    t_matrix expected;
    t_matrix inv;
    int result;
    int success;

    // Obtém a matriz original
    original = mat_func();

    // Obtém a matriz inversa esperada
    expected = inv_func();

    // Calcula a inversa usando a função
    inv = invert_matrix(original, &success);

    if (!success)
    {
        printf("Falha ao inverter a matriz no teste: %s\n", msg);
        free_matrix(original);
        free_matrix(expected);
        return 1; // erro
    }

    // Compara
    result = test_check(equal_matrix(inv, expected), msg);

    // Libera memória
    free_matrix(original);
    free_matrix(expected);
    free_matrix(inv);

    return result;
}



int invertible_matrix_tests(void)
{
    int errors = 0;
    int success;

    // Testa matrizes invertíveis com inversa conhecida
    errors += test_matrix_inversion(matrix_a1, matrix_a1_inverse, "matrix_a1 inverse test");
    errors += test_matrix_inversion(matrix_a2, matrix_a2_inverse, "matrix_a2 inverse test");

    // Testa matriz invertível sem inversa conhecida (apenas verifica se é invertível)
    t_matrix m_a = matrix_a();
    t_matrix inv_a = invert_matrix(m_a, &success);
    if (!success)
    {
        printf("❌ matrix_a deveria ser invertível!\n");
        errors++;
    }
    free_matrix(m_a);
    if (success)
        free_matrix(inv_a);

    // Testa matriz não-invertível
    t_matrix m_b = matrix_b();
    t_matrix inv_b = invert_matrix(m_b, &success);
    if (success)
    {
        printf("❌ matrix_b não deveria ser invertível!\n");
        errors++;
        free_matrix(inv_b);
    }
    free_matrix(m_b);

    if (errors == 0)
        printf("✅ All invertible matrix tests passed.\n");
    else
        printf("❌ Some invertible matrix tests failed.\n");

    return errors;
}

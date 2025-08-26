/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_vector_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:05:12 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/26 01:18:42 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

#define TRUE 1
#define FALSE 0
static int test_translation_matrix_vector(void)
{
    t_matrix transform;
    t_tuple v;
    t_tuple result;
    int errors;

    errors = 0;
    transform = translation_matrix(5, -3, 2);
    v = vector(-3, 4, 5);  // vetor, não ponto
    result = matrix_multiply_by_tuple(transform, v);

    // Vetores não mudam com translação
    errors += test_check_double(result.x, -3, "vector x");
    errors += test_check_double(result.y, 4, "vector y");
    errors += test_check_double(result.z, 5, "vector z");

    free_matrix(transform);

    return errors;
}
static int test_translation_inverse_vector(void)
{
    t_matrix transform;
    t_matrix inv;
    t_tuple v;
    t_tuple result;
    int errors;
    int success; // <--- necessário para a função invert_matrix

    errors = 0;
    transform = translation_matrix(5, -3, 2);

    // Passa &success como segundo argumento
    inv = invert_matrix(transform, &success);

    if (!success)
    {
        printf("❌ Falha ao inverter a matriz de translação (vetor)!\n");
        free_matrix(transform);
        return 1; // erro
    }

    v = vector(-3, 4, 5);
    result = matrix_multiply_by_tuple(inv, v);

    // Vetores não mudam mesmo com a inversa
    errors += test_check_double(result.x, -3, "vector x inverse");
    errors += test_check_double(result.y, 4, "vector y inverse");
    errors += test_check_double(result.z, 5, "vector z inverse");

    free_matrix(transform);
    free_matrix(inv);

    return errors;
}


int run_test_translation_vector(void)
{
    int errors = 0;

    errors += test_translation_matrix_vector();
    errors += test_translation_inverse_vector();

    if (errors == 0)
        test_success("Translation vector tests passed!");
    else
        test_failure("Translation vector tests failed.");

    return errors;
}

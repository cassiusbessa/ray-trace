/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_point_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:05:12 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/26 01:17:56 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_translation_matrix(void)
{
    t_matrix transform;
    t_tuple p;
    t_tuple result;
    int errors;
    
    errors = 0;
    transform = translation_matrix(5, -3, 2);
    p = point(-3, 4, 5);
    result = matrix_multiply_by_tuple(transform, p);
    
    errors += test_check_double(result.x, 2, "translation x");
    errors += test_check_double(result.y, 1, "translation y");
    errors += test_check_double(result.z, 7, "translation z");

    free_matrix(transform);

    return errors;
}
static int test_translation_inverse(void)
{
    t_matrix transform;
    t_matrix inv;
    t_tuple p;
    t_tuple result;
    int errors;
    int success; // <--- necessário para a função invert_matrix

    errors = 0;
    transform = translation_matrix(5, -3, 2);

    // Passa &success como segundo argumento
    inv = invert_matrix(transform, &success);

    if (!success)
    {
        printf("❌ Falha ao inverter a matriz de translação!\n");
        free_matrix(transform);
        return 1; // considera como erro
    }

    p = point(-3, 4, 5);
    result = matrix_multiply_by_tuple(inv, p);

    errors += test_check_double(result.x, -8, "translation x");
    errors += test_check_double(result.y, 7, "translation y");
    errors += test_check_double(result.z, 3, "translation z");

    free_matrix(transform);
    free_matrix(inv);

    return errors;
}



int run_test_translation_point(void)
{
    int         errors;

    errors = 0;
    errors += test_translation_matrix();
    errors += test_translation_inverse();
    if (errors == 0)
        test_success("Translation point tests passed!");
    else
        test_failure("Translation point tests failed.");
    
    return (errors);
}
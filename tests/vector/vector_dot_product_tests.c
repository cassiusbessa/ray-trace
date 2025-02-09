/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_dot_product_tests.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:42:22 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/09 00:03:22 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int	test_dot_product_1_2_3_2_3_4(void)
{
    t_touple	*vector1;
    t_touple	*vector2;
    float		dot;
    int			errors;

    errors = 0;
    vector1 = new_touple(1, 2, 3, FALSE);
    vector2 = new_touple(2, 3, 4, FALSE);
    dot = vector_dot_product(vector1, vector2);
    errors += test_check_double(dot, 20, "dot should be 20");
    free(vector1);
    free(vector2);
    if (errors == 0)
        test_success("test_dot_product_1_2_3_2_3_4 pass!");
    return (errors);
}

int all_vector_dot_product_tests(void)
{
    int errors;

    errors = 0;
    errors += test_dot_product_1_2_3_2_3_4();
    if (errors == 0)
        ft_printf("\n🎉 All vector dot product tests fine!\n");
    else
        ft_printf("\n❌ %d vector dot product tests failed.\n", errors);
    return (errors);
}
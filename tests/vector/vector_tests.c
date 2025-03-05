/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:23:01 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 23:56:46 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int vector_tests(void)
{
    int    errors;

    errors = 0;
    errors += all_vector_magnitude_tests();
    errors += all_vector_normalize_tests();
    errors += all_vector_dot_product_tests();
    errors += all_vector_cross_product_tests();
    if (errors == 0)
        ft_printf("\n🎉 All vector tests fine!\n");
    else
        ft_printf("\n❌ %d vector tests failed.\n", errors);
    return (errors);
}
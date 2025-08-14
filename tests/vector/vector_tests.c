/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:23:01 by caqueiro          #+#    #+#             */
/*   Updated: 2025/08/14 15:21:57 by emorshhe         ###   ########.fr       */
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
        ft_printf("🎉 All vector tests fine!\n\n");
    else
        ft_printf("\n❌ %d vector tests failed.\n\n", errors);
    return (errors);
}
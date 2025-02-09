/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:23:01 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 23:28:17 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int vector_tests(void)
{
    int    errors;

    errors = 0;
    errors += all_vector_magnitude_tests();
    if (errors == 0)
        ft_printf("\n🎉 All vector tests fine!\n");
    else
        ft_printf("\n❌ %d vector tests failed.\n", errors);
    return (errors);
}
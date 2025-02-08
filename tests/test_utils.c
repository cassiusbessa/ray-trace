/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:47 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 20:01:48 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	test_check(int condition, const char *message)
{
	if (!condition)
	{
		printf("❌ ERRO: %s\n", message);
		return (1);
	}
	return (0);
}

void	test_success(const char *message)
{
	printf("✅ %s\n", message);
}

int	test_check_double(double a, double b, const char *msg)
{
	if (fabs(a - b) < EPSILON)
	{
		return (0);
	}
	else
	{
		ft_printf("❌ ERRO: %s (esperado: %.4f, obtido: %.4f)\n", msg, b, a);
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:28:54 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 20:01:57 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include <stdio.h>
#include "../includes/miniRT.h"


int		test_check(int condition, const char *message);
void	test_success(const char *message);
int     test_check_double(double a, double b, const char *msg);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:28:54 by caqueiro          #+#    #+#             */
/*   Updated: 2025/02/08 21:51:14 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "../includes/miniRT.h"
# include <stdio.h>

int		test_check(int condition, const char *message);
void	test_success(const char *message);
int		test_check_double(double a, double b, const char *msg);
int		test_tuple_as_point(void);
int		test_tuple_as_vector(void);
int		test_add_tuples(void);
int		test_sub_points(void);
int		test_sub_vector_from_point(void);
int		test_sub_vectors(void);
int		test_sub_vector_from_zero_vector(void);
int		test_multiply_tuple_by_scalar(void);
int		test_multiply_tuple_by_fraction(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:00:07 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 21:48:34 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

// static int test_prepare_computations(void)
// {
//     int errors = 0;

//     t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
//     t_sphere shape = new_sphere(point(0, 0, 0), 1.0);
//     t_intersection_node i = {.t = 4.0, .object = &shape, .next = NULL};
//     t_comps comps = prepare_computations(i, r);

//     return errors;
// }
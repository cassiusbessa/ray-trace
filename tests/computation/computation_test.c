// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   computation_test.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/08/26 21:00:07 by cassius           #+#    #+#             */
// /*   Updated: 2025/08/26 21:20:27 by cassius          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../tests.h"

// static int test_prepare_computations(void)
// {
//     int errors = 0;

//     t_ray r = create_ray(point(0, 0, -5), vector(0, 0, 1));
//     t_sphere shape = new_sphere(point(0, 0, 0), 1.0);
//     t_intersection_node i = {.t = 4.0, .object = &shape, .next = NULL};
//     t_comps comps = prepare_computations(i, r);

//     errors += test_check(float_equal(comps.t, i.t), "prepare_computations t");
//     errors += test_check(comps.object == i.object, "prepare_computations object");
//     errors += test_check(point_equal(comps.point, position(r, i.t)), "prepare_computations point");
//     errors += test_check(vector_equal(comps.eyev, -r.direction), "prepare_computations eyev");
//     errors += test_check(vector_equal(comps.normalv, normal_at(shape, comps.point)), "prepare_computations normalv");
//     errors += test_check(comps.inside == (dot(comps.normalv, comps.eyev) < 0), "prepare_computations inside");

//     return errors;
// }
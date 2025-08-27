/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:07:21 by cassius           #+#    #+#             */
/*   Updated: 2025/08/26 23:38:50 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_shade_intersection(void)
{
    int errors = 0;

    t_world w = default_world();
    t_ray   r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    t_object shape = w.objects->head->object;
    t_intersection_node i = {.t = 4.0, .object = &shape, .next = NULL};
    t_comps comps = prepare_computations(i, r);
    t_rgb color = shade_hit(&w, comps);
    print_rgb(color);

    errors += test_check(equal_rgb(color, new_rgb(0.38066f, 0.47583f, 0.2855f)), "Color mismatch in shade_hit test");
    if (errors)
        test_failure("Shade intersection test failed\n");
    else
        test_success("Shade intersection test passed\n");
    return errors;
}

int run_test_hit_shade(void)
{
    int errors = 0;

    errors += test_shade_intersection();

    if (errors)
        test_failure("Shade hit test failed\n");
    else
        test_success("Shade hit test passed\n");

    return errors;
}
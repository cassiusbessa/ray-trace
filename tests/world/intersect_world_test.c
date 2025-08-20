/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:09:53 by cassius           #+#    #+#             */
/*   Updated: 2025/08/19 21:16:07 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

static int test_intersect_world(void)
{
    t_world w;
    int errors = 0;
    t_ray r;

    w = default_world();
    r = create_ray(point(0, 0, -5), vector(0, 0, 1));
    

}
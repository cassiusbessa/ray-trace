/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:45:48 by cassius           #+#    #+#             */
/*   Updated: 2025/08/27 20:49:49 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_camera    new_camera(int hsize, int vsize, float field_of_view)
{
    t_camera cam;

    cam.hsize = hsize;
    cam.vsize = vsize;
    cam.field_of_view = field_of_view;
    cam.transform = identity_matrix(4);
    return (cam);
}
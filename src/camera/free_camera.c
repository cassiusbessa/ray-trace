/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:21:32 by emorshhe          #+#    #+#             */
/*   Updated: 2025/09/05 16:22:01 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_camera(t_camera *camera)
{
	if (camera)
	{
		free_matrix(camera->transform);
	}
}

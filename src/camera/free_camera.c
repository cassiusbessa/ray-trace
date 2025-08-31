#include "../../includes/miniRT.h"

void	free_camera(t_camera *camera)
{
	if (camera)
	{
		free_matrix(camera->transform);
	}
}

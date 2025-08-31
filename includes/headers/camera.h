#ifndef CAMERA_H
# define CAMERA_H

# include "computations.h"
# include "canvas.h"

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	float		field_of_view;
	t_matrix	transform;
	float		pixel_size;
	float		half_width;
	float		half_height;
}	t_camera;

// Camera operations
t_camera	new_camera(int hsize, int vsize, float field_of_view);
void		free_camera(t_camera *camera);
t_ray		ray_for_pixel(t_camera cam, int px, int py);
t_canvas	*render(t_camera cam, t_world *w);

#endif

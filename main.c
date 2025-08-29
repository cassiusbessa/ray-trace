#include "includes/miniRT.h"
#include <stdio.h>


int main(void)
{
    t_world world = new_world();
    t_sphere    s = new_sphere(point(0, 0, 0), 1);
    s.material = new_material_default();
    s.material.color = new_rgb(1, 0.9, 0.9);
    s.material.specular = 0;
    t_object floor = new_object(SPHERE, (void *)&s);
    t_matrix sm = scaling_matrix(10, 0.01, 10);
    set_object_transform(&floor, sm);
    free_matrix(sm);
    add_object_to_world(&world, floor);
    t_camera cam = new_camera(100, 50, M_PI / 3);
    free_matrix(cam.transform);
    cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
    
    t_canvas *c = render(cam, &world);
    free_camera(&cam);
    free_world(&world);
    free_canvas(c);
    return 0;
    }
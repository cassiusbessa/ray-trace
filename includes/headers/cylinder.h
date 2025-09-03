#ifndef CYLINDER_H
#define CYLINDER_H

#include <stdlib.h>
#include "tuples.h"        // t_tuple
#include "colors.h"        // t_rgb
#include "matrices.h"      // t_matrix
#include "objects.h"       // t_object, t_object_type, set_object_transform

typedef struct s_cylinder
{
    float radius;
    float height;
    int closed; // 1 se tiver tampas, 0 se aberto
} t_cylinder;

t_cylinder new_cylinder(void);
t_object new_cylinder_object(t_tuple center, t_tuple orientation, float diameter, float height, t_rgb color, t_bool closed);
t_tuple normal_at_cylinder(t_object *obj, t_tuple world_point);
t_intersection_list *intersect_ray_cylinder(t_ray ray, t_object *obj);
t_tuple normal_at(t_object *obj, t_tuple world_point);

#endif

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

typedef struct s_cylinder_params
{
    t_tuple center;
    t_tuple orientation;
    float   diameter;
    float   height;
    t_rgb   color;
    t_bool  closed;
} t_cylinder_params;

t_cylinder new_cylinder(void);
t_object new_cylinder_object(t_cylinder_params params);
t_tuple normal_at_cylinder(t_object *obj, t_tuple world_point);
t_intersection_list *intersect_ray_cylinder(t_ray ray, t_object *obj);
t_tuple normal_at(t_object *obj, t_tuple world_point);
t_cylinder      *init_cylinder(float diameter, float height, t_bool closed);
void            set_cylinder_material(t_object *obj, t_rgb color);
t_matrix        compute_cylinder_transform(t_tuple center, t_tuple orientation, float radius, float half_height);
t_bool          transform_ray_to_local(t_ray ray, t_object *obj, t_ray *local_ray);
void            intersect_cylinder_sides(t_ray ray, t_object *obj, t_intersection_list *list);
void            intersect_cylinder_caps(t_ray ray, t_object *obj, t_intersection_list *list);


#endif

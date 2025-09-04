#ifndef PLANE_H
# define PLANE_H

# include "tuples.h"

typedef struct s_plane
{
    t_tuple point;   // Um ponto no plano
    t_tuple normal;  // Vetor normal normalizado
}   t_plane;

t_plane *new_plane(t_tuple point, t_tuple normal);
t_tuple normal_at_plane(t_object *obj, t_tuple world_point);
t_intersection_list *intersect_ray_plane(t_ray ray, t_object *obj);

#endif

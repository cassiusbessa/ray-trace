#include "../../includes/miniRT.h"



t_plane *new_plane(t_tuple point, t_tuple normal)
{
    t_plane *plane = malloc(sizeof(t_plane));
    if (!plane)
        return NULL;

    plane->point = point;
    plane->normal = safe_normalize_vector(normal);

    return plane;
}

t_intersection_list *intersect_ray_plane(t_ray ray, t_object *obj)
{
    t_plane *plane = (t_plane *)obj->data;
    double denom = vector_dot_product(plane->normal, ray.direction);

    // Raio paralelo ao plano
    if (fabs(denom) < EPSILON)
        return NULL;

    // Calcula t da interseção
    double t = vector_dot_product(plane->normal, sub_tuples(plane->point, ray.origin)) / denom;

    // Interseção atrás da origem do raio
    if (t < 0)
        return NULL;

    // Cria lista de interseções com um único ponto
    t_intersection_list *list = new_intersection_list();
    if (!list)
        return NULL;

    t_intersection inter = new_intersection(1, t, 0, obj);
    add_intersection_to_list(list, inter);

    return list;
}


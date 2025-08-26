#include "includes/miniRT.h"
#include <stdio.h>


int main(void)
{
    t_world world = new_world();

    // Primeira esfera
    t_sphere *s1 = malloc(sizeof(t_sphere));
    *s1 = new_sphere(point(0,0,0), 1.0f);
    s1->material = new_material_default();

    t_object obj1;
    obj1.type = SPHERE;
    obj1.data = s1;
    add_object_to_world(&world, obj1);

    // Segunda esfera (escalada)
    t_sphere *s2 = malloc(sizeof(t_sphere));
    *s2 = new_sphere(point(0,0,0), 1.0f);
    s2->transform = scaling_matrix(0.5f, 0.5f, 0.5f);

    t_object obj2;
    obj2.type = SPHERE;
    obj2.data = s2;
    set_object_transform(&obj2, s2->transform);
    add_object_to_world(&world, obj2);

    // Raio
    t_ray r = create_ray(point(0,0,-5), vector(0,0,1));

    // Interseções por objeto
    for (t_object_node *node = world.objects->head; node; node = node->next)
    {
        t_intersection_list *xs = intersect_ray_sphere(r, &node->object);

        printf("Objeto %p:\n", node->object.data);
        t_intersection_node *curr = xs->head;
        int i = 1;
        while (curr)
        {
            printf("  Interseção %d: t = %.2f\n", i, curr->t);
            curr = curr->next;
            i++;
        }

        free_intersection_list(xs);
    }

    // Hit global
    t_intersection_list *all_xs = new_intersection_list();
    for (t_object_node *node = world.objects->head; node; node = node->next)
    {
        t_intersection_list *obj_xs = intersect_ray_sphere(r, &node->object);
        join_lists(all_xs, obj_xs, TRUE);
    }

    t_intersection_node *h = hit(*all_xs);
    if (h)
        printf("Hit mais próxima: t = %.2f\n", h->t);

    free_intersection_list(all_xs);

    free(s1);
    free(s2);
    free_world(&world);

    return 0;
}
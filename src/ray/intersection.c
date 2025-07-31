/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:32:26 by caqueiro          #+#    #+#             */
/*   Updated: 2025/07/31 17:20:57 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection	*intersect(t_sphere *s, t_ray r, int *count)
{
	t_ray		r2;
	t_tuple		sphere_to_ray;
	float		a, b, c, discriminant;
	t_intersection	*xs;

	r2 = transform_ray(r, inverse(s->transform));
	sphere_to_ray = sub(r2.origin, point(0, 0, 0));
	a = dot(r2.direction, r2.direction);
	b = 2 * dot(r2.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		*count = 0;
		return (NULL);
	}
	xs = malloc(2 * sizeof(t_intersection));
	xs[0].t = (-b - sqrt(discriminant)) / (2 * a);
	xs[1].t = (-b + sqrt(discriminant)) / (2 * a);
	xs[0].object = s;
	xs[1].object = s;
	*count = 2;
	return (xs);
}

t_intersection	*hit(t_intersection *xs, int count)
{
	int	i;
	t_intersection	*hit = NULL;

	for (i = 0; i < count; i++)
	{
		if (xs[i].t >= 0 && (!hit || xs[i].t < hit->t))
			hit = &xs[i];
	}
	return (hit);
}

int compare_intersections(const void *a, const void *b)
{
    t_intersection *ia;
    t_intersection *ib;

    ia = (t_intersection *)a;
    ib = (t_intersection *)b;
    if (ia->t < ib->t)
        return (-1);
    else if (ia->t > ib->t)
        return (1);
    return (0);
}
static t_intersection *resize_intersections(t_intersection *arr, int *capacity)
{
    *capacity *= 2;
    t_intersection *new_arr;

    new_arr= realloc(arr, sizeof(t_intersection) * (*capacity));
    if (!new_arr)
    {
        fprintf(stderr, "Failed to realloc memory for intersections\n");
        exit(1);
    }
    return (new_arr);
}

static int append_intersections(t_intersection **dst, int *total_count, int *capacity, t_intersection *src, int src_count)
{
    int i;
    
    i = 0;
    while (i < src_count)
    {
        if (*total_count >= *capacity)
            *dst = resize_intersections(*dst, capacity);
        (*dst)[(*total_count)++] = src[i];
        i++;
    }
    return (*total_count);
}

t_intersection *intersect_world(t_world *world, t_ray ray, int *count)
{
    t_intersection *intersections;
    int total_intersections;
    int capacity;
    int i;
    int local_count;
    t_intersection *local_intersections;

    total_intersections = 0;
    capacity = 10;
    intersections = malloc(sizeof(t_intersection) * capacity);
    if (!intersections)
    {
        fprintf(stderr, "Failed to allocate memory for intersections\n");
        exit(1);
    }
    i = 0;
    while (i < world->object_count)
    {
        local_count = 0;
        local_intersections = intersect(&world->objects[i], ray, &local_count);
        append_intersections(&intersections, &total_intersections, &capacity, local_intersections, local_count);
        free(local_intersections);
        i++;
    }
    *count = total_intersections;
    qsort(intersections, total_intersections, sizeof(t_intersection), compare_intersections);
    return (intersections);
}

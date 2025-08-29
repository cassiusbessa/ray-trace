#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "objects.h"
# include "rays.h"

typedef struct s_intersection
{
	float	count;
	float	enter;
	float	exit;
	void	*object;
}	t_intersection;

typedef struct s_intersections
{
	t_intersection	*list;
	int				count;
}	t_intersections;

typedef struct s_intersection_node
{
	float					t;
	struct s_intersection_node	*next;
	t_object				*object;
}	t_intersection_node;

typedef struct s_intersection_list
{
	t_intersection_node	*head;
	t_intersection_node	*tail;
	int					count;
}	t_intersection_list;

// Intersection operations
t_intersection_list	*new_intersection_list(void);
void				free_intersection_list(t_intersection_list *list);
void				add_intersection_to_list(t_intersection_list *list, t_intersection i);
void				join_lists(t_intersection_list *dest, t_intersection_list *src, t_bool free_src);
t_intersection		new_intersection(int count, float enter, float exit, void *object);
t_bool				equal_intersections(t_intersection i1, t_intersection i2);
t_intersection_node	*hit(t_intersection_list l);
t_intersection_list	*intersect(t_ray ray, t_object *object);

// Helper functions for intersection lists
void				add(t_intersection_node *n, t_intersection_list *list);
void				add_node_ordered(float t, t_intersection_list *list, t_object *o);
t_intersection_node	*get_node(int i, t_intersection_list *list);

#endif

#ifndef OBJECTS_H
# define OBJECTS_H

# include "types.h"

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	void			*data; // ponteiro para t_sphere, t_plane, etc.
}	t_object;

// Object operations
t_object	new_object(t_object_type type, void *data);
void		free_object(t_object *obj);
void		set_object_transform(t_object *obj, t_matrix m);

// Object lists for world
typedef struct s_object_node
{
	struct s_object_node	*prev;
	t_object				object;
	struct s_object_node	*next;
}	t_object_node;

typedef struct s_object_list
{
	t_object_node	*head;
	t_object_node	*tail;
	int				count;
}	t_object_list;

#endif

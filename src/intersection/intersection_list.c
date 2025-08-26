/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorshhe <emorshhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:14:44 by cassius           #+#    #+#             */
/*   Updated: 2025/08/25 20:41:40 by emorshhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_intersection_list	*new_intersection_list(void)
{
    t_intersection_list	*list;

    list = malloc(sizeof(t_intersection_list));
    if (!list)
        return (NULL);
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return (list);
}

void	free_intersection_list(t_intersection_list *list)
{
	t_intersection_node	*current;
	t_intersection_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
}

void add(t_intersection_node *n, t_intersection_list *list)
{
    t_intersection_node *current;
    t_intersection_node *prev;

    current = list->head;
    prev = NULL;
    while (current && current->t < n->t)
    {
        prev = current;
        current = current->next;
    }
    if (!prev)
    {
        n->next = list->head;
        list->head = n;
    }
    else
    {
        n->next = current;
        prev->next = n;
    }
    if (!n->next)
        list->tail = n;
    list->count++;
}

void add_node_ordered(float t, t_intersection_list *list, t_object *o)
{
    t_intersection_node *n;

    if (!list)
        return;
    n = malloc(sizeof(t_intersection_node));
    if (!n)
        return;
    n->t = t;
    n->object = o;
    n->next = NULL;
    if (!list->head)
    {
        list->head = n;
        list->tail = n;
        list->count = 1;
        return;
    }
    add(n, list);
}


void add_intersection_to_list(t_intersection_list *list, t_intersection i)
{
    if (i.count == 1)
        add_node_ordered(i.enter, list, i.object);
    else if (i.count == 2)
    {
        add_node_ordered(i.enter, list, i.object);
        add_node_ordered(i.exit, list, i.object);
    }
}

void join_lists(t_intersection_list *dest, t_intersection_list *src, t_bool free_src)
{
    t_intersection_node *current;

    if (!dest || !src)
        return;
    current = src->head;
    while (current)
    {
        add_node_ordered(current->t, dest, current->object);
        current = current->next;
    }
    if (free_src)
        free_intersection_list(src);
}



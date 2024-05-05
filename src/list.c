#include "list.h"

#include <stdlib.h>
#include <stddef.h>

list_t *list_new()
{
    list_t *p_list = (list_t *)malloc(sizeof(list_t));
    p_list->p_start = NULL;
    p_list->p_end = NULL;
    p_list->length = 0;
    return p_list;
}

struct list_node *list_node_alloc(void *data, size_t data_size)
{
    struct list_node *p_node = (struct list_node *)malloc(sizeof(struct list_node));
    size_t i;
    p_node->p_next = NULL;
    p_node->p_prev = NULL;
    p_node->data = malloc(data_size);
    for (i = 0; i < data_size; i++)
        *((char *)(p_node->data) + i) = *((char *)(data) + i);
    return p_node;
}

void list_push_start(list_t *list, void *data, size_t data_size)
{
    struct list_node *p_node = list_node_alloc(data, data_size);
    if (list->p_start != NULL)
    {
        list->p_start->p_prev = p_node;
        p_node->p_next = list->p_start;
    }
    if (list->p_end == NULL)
        list->p_end = p_node;
    list->length++;
    list->p_start = p_node;
}

void list_push_end(list_t *list, void *data, size_t data_size)
{
    struct list_node *p_node = list_node_alloc(data, data_size);
    if (list->p_end != NULL)
    {
        list->p_end->p_next = p_node;
        p_node->p_prev = list->p_end;
    }
    if (list->p_start == NULL)
        list->p_start = p_node;
    list->length++;
    list->p_end = p_node;
}

struct list_node *list_node_at(list_t *list, size_t index)
{
    struct list_node *p_node = list->p_start;
    while (p_node != NULL && index--)
        p_node = p_node->p_next;
    return p_node;
}

void *list_at(list_t *list, size_t index)
{
    struct list_node *p_node = list_node_at(list, index);
    return p_node == NULL ? NULL : p_node->data;
}

void list_node_free(struct list_node *p_node)
{
    free(p_node->data);
    free(p_node);
}

void list_remove(list_t *list, size_t index)
{
    struct list_node *p_node_to_delete, *p_node;

    if (list->length == 0)
        return;
    if (index >= list->length)
        return;
    if (index == 0)
    {
        p_node_to_delete = list->p_start;
        list->p_start = p_node_to_delete->p_next;
        if (list->p_start != NULL)
            list->p_start->p_prev = NULL;
        list->p_start->p_prev = NULL;
        if (list->p_end == p_node_to_delete)
            list->p_end = NULL;
    }
    else
    {
        p_node = list_node_at(list, index - 1);
        p_node_to_delete = p_node->p_next;
        p_node->p_next = p_node_to_delete->p_next;
        if (p_node->p_next != NULL)
            p_node->p_next->p_prev = p_node;
        if (list->p_end == p_node_to_delete)
            list->p_end = p_node;
    }

    list->length--;
    list_node_free(p_node_to_delete);
}

void list_free(list_t *list)
{
    struct list_node *p_node_to_delete, *next_node = list->p_start;
    while (next_node != NULL)
    {
        p_node_to_delete = next_node;
        next_node = next_node->p_next;
        list_node_free(p_node_to_delete);
    }
    free(list);
}
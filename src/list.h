#ifndef LIST_H
#define LIST_H

#include <stddef.h>

struct list_node
{
    void *data;
    struct list_node *p_next;
    struct list_node *p_prev;
};

typedef struct
{
    struct list_node *p_start;
    struct list_node *p_end;
    size_t length;
} list_t;

list_t *list_new();
void list_push_start(list_t *list, void *data, size_t data_size);
void list_push_end(list_t *list, void *data, size_t data_size);
struct list_node *list_node_at(list_t *list, size_t index);
void *list_at(list_t *list, size_t index);
void list_remove(list_t *list, size_t index);
void list_free(list_t *list);

#endif
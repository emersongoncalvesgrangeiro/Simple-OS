#ifndef LIST_H
#define LIST_H

typedef struct list_node {
    void *data;
    struct list_node *next;
} list_node_t;

typedef struct {
    list_node_t *head;
} list_t;

void list_init(list_t *list);
void list_push(list_t *list, void *data);
void *list_pop(list_t *list);

#endif

#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue {
    void **data;
    int head;
    int tail;
    int size;
} queue_t;

void queue_init(queue_t *q, int size);
void queue_push(queue_t *q, void *item);
void *queue_pop(queue_t *q);

#endif

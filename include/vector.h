#ifndef VECTOR_H
#define VECTOR_H

typedef struct{
    void **data;
    int size;
    int capacity;
} vector_t;

void vector_init(vector_t *vec);

void vector_push(vector_t *vec, void *item);

void *vector_get(vector_t *vec, int index);

#endif

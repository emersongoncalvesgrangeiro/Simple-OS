#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct{
    int value;
} semaphore_t;

void semaphore_init(semaphore_t *s, int value);

void semaphore_wait(semaphore_t *s);

void semaphore_post(semaphore_t *s);

#endif

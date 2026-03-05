#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>

typedef struct thread {
    uint64_t rsp;
    uint64_t stack;
    int id;
} thread_t;

void threads_init();
void thread_create(void (*func)());
void thread_yield();

#endif

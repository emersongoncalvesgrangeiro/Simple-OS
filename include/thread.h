#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>

typedef enum{
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_BLOCKED,
    THREAD_TERMINATED

} thread_state_t;

typedef struct thread{
    uint64_t rsp;
    uint64_t rip;
    thread_state_t state;
    struct thread *next;
} thread_t;

thread_t *thread_create(void (*entry)(void));

void thread_exit();

#endif

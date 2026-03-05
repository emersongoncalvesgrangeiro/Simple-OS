#include <thread.h>
#include <stdlib.h>

thread_t *thread_create(void (*entry)(void)) {
    (void)entry;
    return NULL;
}

void thread_exit(void) { }

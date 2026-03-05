#include <thread.h>
#include <stdlib.h>
#include <panic.h>

thread_t *thread_create(void (*entry)(void)) {
    (void)entry;
    return NULL;
}

void thread_exit(void) { }

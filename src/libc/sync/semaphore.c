#include <semaphore.h>
#include <spinlock.h>   // precisará de spinlock para proteger

void semaphore_init(semaphore_t *s, int value) {
    s->value = value;
}

void semaphore_wait(semaphore_t *s) {
    while (__sync_fetch_and_sub(&s->value, 1) <= 0) {
        __sync_fetch_and_add(&s->value, 1);
        // idealmente bloquearia a thread
    }
}

void semaphore_post(semaphore_t *s) {
    __sync_fetch_and_add(&s->value, 1);
}

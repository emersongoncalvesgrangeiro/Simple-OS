#include <mutex.h>

void mutex_init(mutex_t *m) {
    m->locked = 0;
}

void mutex_lock(mutex_t *m) {
    while (__sync_lock_test_and_set(&m->locked, 1)) {
        while (m->locked) __asm__("pause");
    }
}

void mutex_unlock(mutex_t *m) {
    __sync_lock_release(&m->locked);
}

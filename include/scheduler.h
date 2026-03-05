#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "thread.h"

void scheduler_init();

void scheduler_add(thread_t *thread);

void scheduler_run();

void scheduler_yield();

#endif

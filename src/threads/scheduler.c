#include <panic.h>
#include <scheduler.h>

void scheduler_init(void) { }
void scheduler_add(thread_t *thread) { (void)thread; }
void scheduler_run(void) { panic("scheduler_run not implemented"); }
void scheduler_yield(void) { }

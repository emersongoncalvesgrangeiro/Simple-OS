#include <stdlib.h>
#include <heap.h>

void free(void *ptr) {
    heap_free(ptr);
}

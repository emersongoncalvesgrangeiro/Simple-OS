#include <stdlib.h>
#include <heap.h>

void *malloc(size_t size) {
    return heap_alloc(size);
}

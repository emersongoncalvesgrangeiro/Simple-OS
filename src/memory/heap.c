#include <stdint.h>
#include <heap.h>

static uint8_t *heap_start;
static uint8_t *heap_end;
static uint8_t *heap_current;

void heap_init(void *start, size_t size) {
    heap_start = start;
    heap_end = heap_start + size;
    heap_current = heap_start;
}

void *heap_alloc(size_t size) {
    if (heap_current + size >= heap_end) {
        return NULL;
    }

    void *ptr = heap_current;
    heap_current += size;
    return ptr;
}

void heap_free(void *ptr) {
    (void)ptr;
    // Bump allocator não suporta free
}

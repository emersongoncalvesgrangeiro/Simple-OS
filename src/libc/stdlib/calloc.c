#include <stdlib.h>
#include <string.h>

void *calloc(size_t n, size_t size) {
    size_t total = n * size;
    void *ptr = malloc(total);
    if (ptr) memset(ptr, 0, total);
    return ptr;
}

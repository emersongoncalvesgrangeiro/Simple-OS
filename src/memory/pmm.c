#include <panic.h>
#include <pmm.h>
#include <limine.h>
#include <stddef.h>

void pmm_init(struct limine_memmap_response *memmap) {
    (void)memmap;
}

void *pmm_alloc_page(void) {
    return NULL;
}

void pmm_free_page(void *page) {
    (void)page;
}

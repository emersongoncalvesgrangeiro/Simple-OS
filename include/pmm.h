#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include <limine.h>

void pmm_init(struct limine_memmap_response *memmap);
void *pmm_alloc_page(void);
void pmm_free_page(void *page);

#endif

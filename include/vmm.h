#ifndef VMM_H
#define VMM_H

#include <stdint.h>

void vmm_init();

void vmm_map(
    uint64_t virt,
    uint64_t phys,
    uint64_t flags
);

#endif

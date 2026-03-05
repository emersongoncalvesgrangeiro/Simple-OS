#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <types.h>

typedef struct {
    uint32_t *address;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
} framebuffer_t;

extern framebuffer_t fb;   // <-- ADICIONADO

void framebuffer_init(void *addr, uint32_t width, uint32_t height, uint32_t pitch);
void framebuffer_putpixel(uint32_t x, uint32_t y, uint32_t color);
void framebuffer_clear(uint32_t color);

#endif

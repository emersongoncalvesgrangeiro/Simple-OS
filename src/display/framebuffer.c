#include <framebuffer.h>

framebuffer_t fb;   // definição global

void framebuffer_init(void *addr, uint32_t width, uint32_t height, uint32_t pitch) {
    fb.address = addr;
    fb.width = width;
    fb.height = height;
    fb.pitch = pitch / 4;
}

void framebuffer_putpixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= fb.width || y >= fb.height) return;
    uint32_t *pixel = (uint32_t*)((uint8_t*)fb.address + y * fb.pitch * 4 + x * 4);
    *pixel = color;
}

void framebuffer_clear(uint32_t color) {
    for (uint32_t y = 0; y < fb.height; y++)
        for (uint32_t x = 0; x < fb.width; x++)
            framebuffer_putpixel(x, y, color);
}

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_init();
void putpixel(uint32_t x, uint32_t y, uint32_t color);
void clear(uint32_t color);

#endif

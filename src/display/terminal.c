#include <terminal.h>
#include <framebuffer.h>

static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;
static uint32_t term_width, term_height;
static const uint32_t CHAR_WIDTH = 8;
static const uint32_t CHAR_HEIGHT = 16;

static void draw_char(char c, uint32_t x, uint32_t y) {
    (void)c;
    for (uint32_t cy = 0; cy < CHAR_HEIGHT; cy++) {
        for (uint32_t cx = 0; cx < CHAR_WIDTH; cx++) {
            framebuffer_putpixel(x + cx, y + cy, 0xFFFFFF);
        }
    }
}

void terminal_init(void) {
    term_width = fb.width / CHAR_WIDTH;
    term_height = fb.height / CHAR_HEIGHT;
    framebuffer_clear(0x000000);
}

void terminal_putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else {
        uint32_t x = cursor_x * CHAR_WIDTH;
        uint32_t y = cursor_y * CHAR_HEIGHT;
        draw_char(c, x, y);
        cursor_x++;
    }

    if (cursor_x >= term_width) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= term_height) {
        framebuffer_clear(0x000000);
        cursor_x = 0;
        cursor_y = 0;
    }
}

void terminal_write(const char *str) {
    while (*str) terminal_putchar(*str++);
}

void terminal_clear(void) {
    framebuffer_clear(0x000000);
    cursor_x = 0;
    cursor_y = 0;
}

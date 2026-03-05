#include <stdio.h>
#include <terminal.h>

int puts(const char *str) {
    terminal_write(str);
    terminal_putchar('\n');
    return 0;
}

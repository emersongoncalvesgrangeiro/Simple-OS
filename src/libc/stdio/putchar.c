#include <stdio.h>
#include <terminal.h>

int putchar(int c) {
    terminal_putchar((char)c);
    return c;
}

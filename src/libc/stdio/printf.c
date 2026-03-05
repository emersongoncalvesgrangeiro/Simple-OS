#include <stdio.h>
#include <terminal.h>
#include <stdarg.h>

static void print_number(int n) {
    char buf[32];
    int i = 0;

    if (n == 0) {
        putchar('0');
        return;
    }

    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }

    while (i--) {
        putchar(buf[i]);
    }
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;

            if (*fmt == 'd') {
                int n = va_arg(args, int);
                print_number(n);
            } else if (*fmt == 's') {
                char *s = va_arg(args, char*);
                terminal_write(s);
            } else if (*fmt == 'c') {
                char c = va_arg(args, int);
                putchar(c);
            }
        } else {
            putchar(*fmt);
        }

        fmt++;
    }

    va_end(args);

    return 0;
}

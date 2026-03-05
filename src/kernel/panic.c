#include <panic.h>
#include <stdio.h>

void panic(const char *msg) {
    printf("KERNEL PANIC: %s\n", msg);
    while (1) {
        __asm__("cli; hlt");
    }
}

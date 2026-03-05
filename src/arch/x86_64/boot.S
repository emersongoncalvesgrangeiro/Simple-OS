.section .text
.global _start
_start:
    cli
    mov $stack_top, %rsp
    call kernel_main
halt:
    hlt
    jmp halt

.section .bss
.align 16
stack_bottom:
    .space 16384
stack_top:

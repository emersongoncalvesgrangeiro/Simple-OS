global _start
extern kernel_main

section .text
bits 64
_start:
    cli                     ; desativa interrupções
    mov rsp, stack_top      ; configura pilha
    call kernel_main        ; chama o kernel (não retorna)
.halt:
    hlt
    jmp .halt

section .bss
align 16
stack_bottom:
    resb 16384              ; 16 KB de pilha
stack_top:

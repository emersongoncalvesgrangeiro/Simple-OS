OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

PHDRS{
    text    PT_LOAD    FLAGS(0x05);
    rodata  PT_LOAD    FLAGS(0x04);
    data    PT_LOAD    FLAGS(0x06);
}

SECTIONS{
    . = 0xffffffff80000000;

    .text : {
        *(.text .text.*)
    } :text

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    .requests : {
        KEEP(*(.requests_start_marker))
        KEEP(*(.requests))
        KEEP(*(.requests_end_marker))
    } :rodata

    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data
}

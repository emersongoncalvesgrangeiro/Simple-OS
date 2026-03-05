OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

PHDRS
{
    text    PT_LOAD    FLAGS(0x05); /* Read + Execute */
    rodata  PT_LOAD    FLAGS(0x04); /* Read Only */
    data    PT_LOAD    FLAGS(0x06); /* Read + Write */
}

SECTIONS
{
    /* Endereço padrão para kernels de 64 bits no Limine */
    . = 0xffffffff80000000;

    .text : {
        *(.text .text.*)
    } :text

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data
}


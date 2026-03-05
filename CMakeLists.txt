cmake_minimum_required(VERSION 3.16)
project(MeuOS C ASM)

set(CMAKE_C_STANDARD 11)

set(KERNEL_FLAGS
    -ffreestanding
    -fno-stack-protector
    -fno-stack-check
    -fno-pie
    -fno-pic
    -m64
    -march=x86-64
    -mno-80387
    -mno-mmx
    -mno-sse
    -mno-sse2
    -mno-red-zone
)

add_compile_options(${KERNEL_FLAGS} -g)

set(KERNEL_BINARY kernel.elf)
set(ISO_IMAGE meulos.iso)

include_directories(src)

file(GLOB_RECURSE SOURCES
    src/*.c
    src/*.asm
)

add_executable(${KERNEL_BINARY} ${SOURCES})

target_link_options(${KERNEL_BINARY} PRIVATE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/src/linker.ld
    -nostdlib
    -static
    -z max-page-size=0x1000
)

add_custom_target(iso
    DEPENDS ${KERNEL_BINARY}
    COMMAND ${CMAKE_COMMAND} -E make_directory iso_root
    COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_BINARY} iso_root/
    COMMAND ${CMAKE_COMMAND} -E copy limine.conf iso_root/
    COMMAND cp limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/
    COMMAND xorriso -as mkisofs
        -b limine-bios-cd.bin
        -no-emul-boot
        -boot-load-size 4
        -boot-info-table
        --efi-boot limine-uefi-cd.bin
        -efi-boot-part
        --protective-msdos-label
        iso_root
        -o ${ISO_IMAGE}
    COMMAND ./limine/limine bios-install ${ISO_IMAGE}
)

add_custom_target(run
    DEPENDS iso
    COMMAND qemu-system-x86_64
        -cdrom ${ISO_IMAGE}
        -m 512M
        -bios /usr/share/OVMF/OVMF_CODE.fd
)

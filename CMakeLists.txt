cmake_minimum_required(VERSION 3.16)
project(SimpleOS C ASM)

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
    -mcmodel=kernel
)

add_compile_options(${KERNEL_FLAGS} -g)

set(KERNEL_BINARY kernel.elf)
set(ISO_IMAGE SimpleOS.iso)

# Coleta todos os .c
file(GLOB_RECURSE C_SOURCES
    src/display/*.c
    src/drivers/*.c
    src/kernel/*.c
    src/libc/*/*.c
    src/memory/*.c
    src/threads/*.c
)

# Coleta todos os .S (assembly)
file(GLOB_RECURSE ASM_SOURCES
    src/arch/x86_64/*.S
)

add_executable(${KERNEL_BINARY} ${C_SOURCES} ${ASM_SOURCES})

# Diretórios de inclusão
target_include_directories(${KERNEL_BINARY} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/limine
)

target_link_options(${KERNEL_BINARY} PRIVATE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
    -nostdlib
    -static
    -z max-page-size=0x1000
)

# Cria a ISO com offset de partição 63
add_custom_target(iso
    DEPENDS ${KERNEL_BINARY}
    COMMAND ${CMAKE_COMMAND} -E make_directory iso_root/boot/limine
    COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_BINARY} iso_root/boot/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/limine.conf iso_root/boot/
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/bin/limine-bios.sys
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/bin/limine-bios-cd.bin
        ${CMAKE_CURRENT_SOURCE_DIR}/limine/bin/limine-uefi-cd.bin
        iso_root/boot/limine/
    COMMAND xorriso -as mkisofs
        -b boot/limine/limine-bios-cd.bin
        -no-emul-boot
        -boot-load-size 4
        -boot-info-table
        -eltorito-alt-boot
        -e boot/limine/limine-uefi-cd.bin
        -no-emul-boot
        -partition_offset 63          # <-- offset 63 (padrão BIOS)
        --protective-msdos-label
        iso_root
        -o ${ISO_IMAGE}
    COMMAND chmod +x ${CMAKE_CURRENT_SOURCE_DIR}/limine/bin/limine
    # Instala o stage 2 (agora deve funcionar)
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/limine/bin/limine bios-install ${ISO_IMAGE}
)

add_custom_target(run
    DEPENDS iso
    COMMAND qemu-system-x86_64
        -cdrom ${ISO_IMAGE}
        -m 512M
)

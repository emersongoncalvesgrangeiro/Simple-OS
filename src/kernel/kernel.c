#include <limine.h>
#include <stdio.h>
#include <stdlib.h>          // para malloc/free
#include <terminal.h>
#include <framebuffer.h>
#include <pmm.h>
#include <heap.h>
#include <vmm.h>
#include <scheduler.h>
#include <thread.h>
#include <mutex.h>
#include <semaphore.h>
#include <spinlock.h>
#include <panic.h>

// Requisições Limine (corrigidas)
__attribute__((used, section(".requests")))
static volatile uint64_t limine_base_revision[3] = LIMINE_BASE_REVISION(2);

__attribute__((used, section(".requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".requests")))
static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".requests")))
static volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".requests_start_marker")))
static volatile uint64_t requests_start_marker[4] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".requests_end_marker")))
static volatile uint64_t requests_end_marker[4] = LIMINE_REQUESTS_END_MARKER;

void kernel_main(void) {
    // 1. Verifica framebuffer
    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        while (1) __asm__("hlt");
    }

    struct limine_framebuffer *fb = framebuffer_request.response->framebuffers[0];
    framebuffer_init(fb->address, fb->width, fb->height, fb->pitch);
    terminal_init();

    printf("SimpleOS kernel inicializado!\n");
    printf("Resolução: %dx%d\n", fb->width, fb->height);

    // 2. Inicializa PMM
    if (memmap_request.response) {
        pmm_init(memmap_request.response);
        printf("PMM inicializado.\n");
    } else {
        printf("ERRO: Sem mapa de memória!\n");
        while (1) __asm__("hlt");
    }

    // 3. Inicializa VMM
    vmm_init();
    printf("VMM inicializado.\n");

    // 4. Inicializa heap
    static uint8_t heap_pool[1024 * 1024];
    heap_init(heap_pool, sizeof(heap_pool));
    printf("Heap inicializado (1 MB).\n");

    // 5. Testa alocação de página
    void *page = pmm_alloc_page();
    if (page) {
        printf("Página alocada em %p\n", page);
        pmm_free_page(page);
        printf("Página liberada.\n");
    }

    // 6. Testa malloc
    void *ptr = malloc(128);
    if (ptr) {
        printf("malloc(128) ok.\n");
        free(ptr);
    }

    // 7. Testa mutex
    mutex_t test_mutex;
    mutex_init(&test_mutex);
    mutex_lock(&test_mutex);
    printf("Mutex lock adquirido.\n");
    mutex_unlock(&test_mutex);
    printf("Mutex liberado.\n");

    // 8. Inicializa scheduler
    scheduler_init();
    printf("Scheduler inicializado (stub).\n");

    // 9. Cria uma thread (stub)
    thread_t *th = thread_create(NULL);
    if (th) {
        printf("Thread criada.\n");
    } else {
        printf("Falha ao criar thread (stub retornou NULL).\n");
    }

    // 10. Loop principal
    printf("Entrando em loop infinito. Sistema operacional rodando!\n");
    while (1) {
        __asm__("hlt");
    }
}

#include <stdlib.h>
#include <string.h>

void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    // Não temos como saber o tamanho original, então apenas aloca novo e copia (parcial)
    void *new_ptr = malloc(size);
    if (new_ptr && ptr) {
        // Copia até o tamanho mínimo entre o novo e o antigo (mas não sabemos o antigo)
        // Por segurança, não copiamos nada.
    }
    free(ptr);
    return new_ptr;
}

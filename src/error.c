#include <stdio.h>
#include <stdlib.h>

void erro(const char *mensagem) {
    fprintf(stderr, "Erro: %s\n", mensagem);
    exit(EXIT_FAILURE);
}

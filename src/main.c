#include <stdio.h>
#include <stdlib.h>
#include "../header/index.h"
#include "tokenizer.h"
#include "parser.h"
#include "runtine.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: cfast <arquivo.fast>\n");
        return 1;
    }

    // Abrir o arquivo
    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ler o conteúdo do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    
    char *input = malloc(tamanho + 1);
    fread(input, 1, tamanho, arquivo);
    input[tamanho] = '\0';
    fclose(arquivo);

    // Fazer o parsing do código
    Node *programa = parse(input);
    if (!programa) {
        fprintf(stderr, "Erro no parsing do código\n");
        free(input);
        return 1;
    }

    // Executar o programa
    executar(programa);

    // Liberar memória
    free_node(programa);
    free(input);
    return 0;
}

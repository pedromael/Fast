#include <stdio.h>
#include <stdlib.h>
#include "../header/index.h"

// Função para executar um nó
void executar(Node *node) {
    if (node == NULL) return;

    // Se for um nó de exibição
    if (strcmp(node->token.nome, "MOSTRAR") == 0) {
        if (node->direita && node->direita->token.valor) {
            printf("%s\n", node->direita->token.valor);
        }
        return;
    }

    // Caso seja uma operação de soma ou multiplicação
    if (strcmp(node->token.nome, "SOMA") == 0 || strcmp(node->token.nome, "MULTIPLICACAO") == 0) {
        int left_value = atoi(node->esquerda->token.valor);
        int right_value = atoi(node->direita->token.valor);
        int resultado;

        if (strcmp(node->token.nome, "SOMA") == 0) {
            resultado = left_value + right_value;
            printf("%d\n", resultado);
        } else if (strcmp(node->token.nome, "MULTIPLICACAO") == 0) {
            resultado = left_value * right_value;
            printf("%d\n", resultado);
        }
    }
}

// Função para liberar a memória da árvore
void free_node(Node *node) {
    if (node == NULL) return;
    free_node(node->esquerda);
    free_node(node->direita);
    free(node);
}

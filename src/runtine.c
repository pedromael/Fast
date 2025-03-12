#include "../header/index.h"

// Função para executar um nó
void executar(Node *node) {
    if (node == NULL) return;

    // Se for um nó de exibição
    if (strcmp(node->token.nome, "MOSTRAR") == 0) {
        if (node->direita && node->direita->token.valor) {
            printf("%s\n", node->direita->token.valor);
        } else {
            fprintf(stderr, "Erro: MOSTRAR sem valor válido\n");
        }
        return;
    }

    // Caso seja uma operação de soma ou multiplicação
    if (strcmp(node->token.nome, "SOMA") == 0 || strcmp(node->token.nome, "MULTIPLICACAO") == 0) {
        if (!node->esquerda || !node->direita) {
            fprintf(stderr, "Erro: Operação matemática sem operandos\n");
            return;
        }

        int left_value = node->esquerda->token.valor ? atoi(node->esquerda->token.valor) : 0;
        int right_value = node->direita->token.valor ? atoi(node->direita->token.valor) : 0;
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

    if (node->token.nome) free(node->token.nome);
    if (node->token.valor) free(node->token.valor);
    
    free(node);
}

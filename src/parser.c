#include <stdio.h>
#include <stdlib.h>
#include "../header/index.h"
#include "../header/tokenizer.h"

static int pos = 0;
static Token **tokens = NULL;
static int num_tokens = 0;

// Função para criar um novo nó
Node* novo_no(Token token) {
    Node *node = malloc(sizeof(Node));
    node->token = token;
    node->esquerda = NULL;
    node->direita = NULL;
    return node;
}

// Função para parser de expressões
Node* parse_expression() {
    if (pos >= num_tokens) return NULL;

    Node *left = novo_no(*tokens[pos++]);
    
    while (pos < num_tokens && (strcmp(tokens[pos]->nome, "SOMA") == 0 || strcmp(tokens[pos]->nome, "MULTIPLICACAO") == 0)) {
        Token operador = *tokens[pos++];
        Node *right = novo_no(*tokens[pos++]);
        
        Node *new_node = novo_no(operador);
        new_node->esquerda = left;
        new_node->direita = right;
        left = new_node;
    }

    return left;
}

// Função principal de parsing
Node* parse(const char *input) {
    printf("code parser\n");
    tokens = tokenizar(input, &num_tokens);
    printf("Tokens: %d\n", num_tokens);
    pos = 0;
    return parse_expression();
}

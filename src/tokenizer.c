#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/index.h"

// Função para criar um novo token
Token* novo_token(const char *nome, const char *valor) {
    Token *token = malloc(sizeof(Token));
    token->nome = strdup(nome);
    token->valor = strdup(valor);
    return token;
}

// Função para liberar memória de um token
void liberar_token(Token *token) {
    free(token->nome);
    free(token->valor);
    free(token);
}

// Função de tokenização simples
Token** tokenizar(const char *input, int *num_tokens) {
    Token **tokens = malloc(sizeof(Token*) * 100); // Capacidade inicial
    *num_tokens = 0;

    const char *delimiters = " \n";
    char *input_copy = strdup(input);
    char *token_str = strtok(input_copy, delimiters);

    while (token_str != NULL) {
        if (strcmp(token_str, "mostrar") == 0) {
            tokens[*num_tokens++] = novo_token("MOSTRAR", NULL);
        } else if (strcmp(token_str, "+") == 0) {
            tokens[*num_tokens++] = novo_token("SOMA", NULL);
        } else if (strcmp(token_str, "*") == 0) {
            tokens[*num_tokens++] = novo_token("MULTIPLICACAO", NULL);
        } else {
            tokens[*num_tokens++] = novo_token("VALOR", token_str);
        }

        token_str = strtok(NULL, delimiters);
    }

    free(input_copy);
    return tokens;
}

// Função para liberar memória dos tokens
void liberar_tokens(Token **tokens, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        liberar_token(tokens[i]);
    }
    free(tokens);
}

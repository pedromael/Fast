#include "../header/tokenizer.h"

// Função para criar um novo token
Token* novo_token(const char *nome, const char *valor) {
    Token *token = malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Erro ao alocar memória para Token\n");
        exit(EXIT_FAILURE);
    }

    token->nome = strdup(nome);
    if (!token->nome) {
        free(token);
        fprintf(stderr, "Erro ao duplicar string do nome\n");
        exit(EXIT_FAILURE);
    }

    token->valor = valor ? strdup(valor) : NULL;
    if (valor && !token->valor) {
        free(token->nome);
        free(token);
        fprintf(stderr, "Erro ao duplicar string do valor\n");
        exit(EXIT_FAILURE);
    }

    return token;
}

// Função para liberar memória de um token
void liberar_token(Token *token) {
    if (!token) return;
    free(token->nome);
    free(token->valor);
    free(token);
}

// Função para tokenizar corretamente a entrada
Token** tokenizar(const char *input, int *num_tokens) {
    if (!input || !num_tokens) {
        fprintf(stderr, "Entrada inválida para tokenizar\n");
        return NULL;
    }

    Token **tokens = malloc(sizeof(Token*) * 100); // Capacidade inicial
    if (!tokens) {
        fprintf(stderr, "Erro ao alocar memória para tokens\n");
        exit(EXIT_FAILURE);
    }
    *num_tokens = 0;

    const char *ptr = input;
    while (*ptr) {
        while (*ptr && isspace(*ptr)) ptr++;  // Ignora espaços

        if (*ptr == '\0') break;

        // Identificar palavras-chave ou operadores
        if (strncmp(ptr, "mostrar", 7) == 0 && !isalnum(ptr[7])) {
            ptr += 7;
            while (*ptr && isspace(*ptr)) ptr++;  // Ignora espaços após mostrar

            // Verificar se há uma string entre aspas
            if (*ptr == '(') {
                ptr++;  // Pular '('
                while (*ptr && isspace(*ptr)) ptr++;

                if (*ptr == '"') {
                    ptr++;  // Pular '"'
                    const char *inicio = ptr;
                    while (*ptr && *ptr != '"') ptr++;

                    if (*ptr == '"') {
                        char *valor = strndup(inicio, ptr - inicio);
                        tokens[(*num_tokens)++] = novo_token("MOSTRAR", valor);
                        free(valor);
                        ptr++;  // Pular '"'
                    }
                }

                while (*ptr && *ptr != ')') ptr++;  // Ir até o ')'
                if (*ptr == ')') ptr++;  // Pular ')'
            } else {
                tokens[(*num_tokens)++] = novo_token("MOSTRAR", NULL);
            }
        }

        // Operadores matemáticos
        else if (*ptr == '+') {
            tokens[(*num_tokens)++] = novo_token("SOMA", NULL);
            ptr++;
        } else if (*ptr == '*') {
            tokens[(*num_tokens)++] = novo_token("MULTIPLICACAO", NULL);
            ptr++;
        }

        // Valores numéricos ou palavras genéricas
        else if (isalnum(*ptr)) {
            const char *inicio = ptr;
            while (isalnum(*ptr)) ptr++;
            char *valor = strndup(inicio, ptr - inicio);
            tokens[(*num_tokens)++] = novo_token("VALOR", valor);
            free(valor);
        }

        // Ignorar caracteres não reconhecidos
        else {
            ptr++;
        }
    }

    return tokens;
}

// Função para liberar memória dos tokens
void liberar_tokens(Token **tokens, int num_tokens) {
    if (!tokens) return;
    
    for (int i = 0; i < num_tokens; i++) {
        liberar_token(tokens[i]);
    }
    free(tokens);
}

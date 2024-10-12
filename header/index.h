#ifndef INDEX_H
#define INDEX_H

// Estruturas e tipos básicos
typedef struct {
    char *nome;
    char *valor;
} Token;

typedef struct Node {
    Token token;
    struct Node *esquerda;
    struct Node *direita;
} Node;

// Funções de parser
Node* parse(const char *input);
void free_node(Node *node);

// Funções de execução
void executar(Node *node);
void mostrar(const char *mensagem);

#endif // INDEX_H

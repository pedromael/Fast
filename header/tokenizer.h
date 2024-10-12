#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "index.h"

// Funções para tokenização
Token** tokenizar(const char *input, int *num_tokens);
void liberar_tokens(Token **tokens, int num_tokens);

#endif // TOKENIZER_H

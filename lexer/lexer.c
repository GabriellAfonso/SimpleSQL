#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

#define MAX_TOKENS 1024

// TODO: levantar error se der TOKEN_UNKNOWN, separar as coisas em funçoes
// menores bem definidas
Token* tokenize(const char* input, int* out_count) {
    Token* tokens = malloc(sizeof(Token) * MAX_TOKENS);
    int count = 0;
    int i = 0;

    while (input[i] != '\0') {
        // Pula espaços
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Palavras-chave ou identificadores
        if (isalpha(input[i])) {
            int start = i;
            while (isalnum(input[i]) || input[i] == '_') i++;
            int len = i - start;

            char* word = strndup(&input[start], len);
            TokenType type = TOKEN_IDENTIFIER;

            if (strcmp(word, "CREATE") == 0)
                type = TOKEN_CREATE;
            else if (strcmp(word, "TABLE") == 0)
                type = TOKEN_TABLE;
            else if (strcmp(word, "INT") == 0)
                type = TOKEN_INT;
            else if (strcmp(word, "TEXT") == 0)
                type = TOKEN_TEXT;

            tokens[count++] = (Token){.type = type, .lexeme = word};
            continue;
        }

        // Símbolos únicos
        switch (input[i]) {
            case '(':
                tokens[count++] = (Token){TOKEN_LPAREN, strdup("(")};
                i++;
                break;
            case ')':
                tokens[count++] = (Token){TOKEN_RPAREN, strdup(")")};
                i++;
                break;
            case ',':
                tokens[count++] = (Token){TOKEN_COMMA, strdup(",")};
                i++;
                break;
            default:
                // Token desconhecido
                tokens[count++] = (Token){TOKEN_UNKNOWN, strndup(&input[i], 1)};
                i++;
                break;
        }
    }

    tokens[count++] = (Token){TOKEN_EOF, strdup("EOF")};
    *out_count = count;
    return tokens;
}

void free_tokens(Token* tokens, int count) {
    for (int i = 0; i < count; i++) {
        free(tokens[i].lexeme);
    }
    free(tokens);
}

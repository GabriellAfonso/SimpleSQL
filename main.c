#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"

#define INPUT_BUFFER_SIZE 1024

int main() {
    char input[INPUT_BUFFER_SIZE];
    printf("SimpleSQL - Interactive Mode\n");
    int token_count = 0;

    while (1) {
        printf("sql> ");

        if (!fgets(input, INPUT_BUFFER_SIZE, stdin)) {
            printf("\nSaindo.\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            printf("Saindo.\n");
            break;  // Sai do while(1)
        }

        Token* tokens = tokenize(input, &token_count);
        for (int i = 0; i < token_count; i++) {
            printf("Token %d: %-15s (%d)\n", i, tokens[i].lexeme,
                   tokens[i].type);
        }
        Statement stmt;
        parse_sql(tokens, &token_count, &stmt);

        free_tokens(tokens, token_count);
        }
    return 0;
}

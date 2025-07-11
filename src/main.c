#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linenoise.h"

#define INPUT_BUFFER_SIZE 1024

extern int yyparse(void);
extern void yy_scan_string(const char *);

int main() {
    char *input;

    printf("SimpleSQL - Interactive Mode\n");

    while ((input = linenoise("sql> ")) != NULL) {
        if (strcmp(input, "exit") == 0) {
            free(input);
            printf("Saindo.\n");
            break;
        }

        yy_scan_string(input);  // Processa a linha
        yyparse();

        linenoiseHistoryAdd(input);  // Adiciona ao histórico
        free(input);
    }

    return 0;
}

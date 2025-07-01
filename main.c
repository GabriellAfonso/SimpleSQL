#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser/parser.h"

#define INPUT_BUFFER_SIZE 1024

int main() {
    char input[INPUT_BUFFER_SIZE];
    printf("SimpleSQL - Interactive Mode\n");

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

        Statement stmt;
        if (parse_sql(input, &stmt) == 0) {
            switch (stmt.type) {
                case STMT_CREATE:
                    printf("[OK] Comando CREATE reconhecido.\n");
                    break;
                case STMT_INSERT:
                    printf("[OK] Comando INSERT reconhecido.\n");
                    break;
                default:
                    printf("[ERRO] Comando válido, mas tipo desconhecido.\n");
            }
        } else {
            printf("[ERRO] Comando inválido.\n");
        }
        return 0;
    }
}

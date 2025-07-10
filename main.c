#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 1024

extern int yyparse(void);
extern void yy_scan_string(const char*);

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
            break;
        }

        yy_scan_string(input);  // <- Aqui a mágica
        yyparse();
    }

    return 0;
}

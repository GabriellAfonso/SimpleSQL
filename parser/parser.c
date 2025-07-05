#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/token.h"

int parse_root_command(Token token, Statement* out_stmt) {
    switch (token.type) {
        case TOKEN_CREATE:
            out_stmt->type = STMT_CREATE;
            printf("usou o comando create\n");
            return 0;
            break;

        default:
            printf("FAZ O L\n");
            return -1;
            break;
    }
}

int parse_create(Token token) {
    // sim gabriel todo segundo comando é um obejeto referenciado pelo primeiro
    // comando
    switch (token.type) {
        case TOKEN_TABLE:
            printf("usou o comando create table\n");
            return 0;
            break;

        default:
            printf("FAZ O L\n");
            return -1;
            break;
    }
}

int parse_sql(Token* tokens, int* token_count, Statement* out_stmt) {
    int pos = 0;
    if (!parse_root_command(tokens[pos], &out_stmt)) return -1;

    pos++;

    switch (out_stmt->type) {
        case STMT_CREATE: {
            if (!parse_create(tokens[pos])) return -1;
            break;
        }

        default:
            break;
    }

    // funçao pegar objeto do root command (TABLE), vai verificar qual o tipo do
    // statment e olhar um switchcase
    //  do root command especifico,
    // tipo eu sei que o root é do tipo create, dentro de create tem table, x,
    // y, etc, se o tokens[1] for Table, faz oq?
    //
}

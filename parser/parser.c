#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/token.h"

int parse_create_table(Token* tokens, int* pos, Statement* out_stmt) {
    (*pos)++;

    // Verifica o nome da tabela (identificador)
    if (tokens[*pos].type != TOKEN_IDENTIFIER) {
        printf("Erro: esperado nome da tabela\n");
        return 0;
    }

    strncpy(out_stmt->table_stmt.name, tokens[*pos].lexeme,
            sizeof(out_stmt->table_stmt.name));
    (*pos)++;
    // Verifica se abriu parênteses
    if (tokens[*pos].type != TOKEN_LPAREN) {
        printf("Erro: esperado '('\n");
        return 0;
    }
    (*pos)++;

    // Início da lista de colunas
    int col_index = 0;
    while (tokens[*pos].type != TOKEN_RPAREN &&
           tokens[*pos].type != TOKEN_EOF) {
        // Nome da coluna
        if (tokens[*pos].type != TOKEN_IDENTIFIER) {
            printf("Erro: esperado nome da coluna\n");
            return 0;
        }
        strncpy(out_stmt->table_stmt.columns[col_index].name,
                tokens[*pos].lexeme, 64);
        (*pos)++;

        // Tipo da coluna
        if (tokens[*pos].type == TOKEN_INT) {
            out_stmt->table_stmt.columns[col_index].type = TYPE_INT;
        } else if (tokens[*pos].type == TOKEN_TEXT) {
            out_stmt->table_stmt.columns[col_index].type = TYPE_TEXT;
        } else {
            printf("Erro: tipo inválido de coluna\n");
            return 0;
        }
        (*pos)++;
        col_index++;

        // Se tiver vírgula, continua; se for parêntese direito, termina
        if (tokens[*pos].type == TOKEN_COMMA) {
            (*pos)++;
        } else if (tokens[*pos].type != TOKEN_RPAREN) {
            printf("Erro: esperado ',' ou ')'\n");
            return 0;
        }
    }

    // Finaliza com parêntese
    if (tokens[*pos].type != TOKEN_RPAREN) {
        printf("Erro: esperado ')'\n");
        return 0;
    }
    (*pos)++;

    out_stmt->table_stmt.column_count = col_index;

    printf("CREATE TABLE '%s' com %d colunas\n", out_stmt->table_stmt.name,
           col_index);

    return 1;
}

int parse_create(Token* tokens, int* pos, Statement* out_stmt) {
    (*pos)++;
    switch (tokens[*pos].type) {
        case TOKEN_TABLE:
            return parse_create_table(tokens, pos, out_stmt);
            break;

        default:
            printf("CREATE NAO TEM ESSE TOKEN\n");
            return -1;
            break;
    }
}

int parse_root_command(Token* tokens, int* pos, Statement* out_stmt) {
    switch (tokens[*pos].type) {
        case TOKEN_CREATE:
            out_stmt->type = STMT_CREATE;
            printf("usou o comando create\n");
            return parse_create(tokens, pos, out_stmt);
            break;

        default:
            printf("FAZ O L\n");
            return -1;
            break;
    }
}

int parse_sql(Token* tokens, int* token_count, Statement* out_stmt) {
    int pos = 0;
    if (!parse_root_command(tokens, &pos, out_stmt)) return -1;
}

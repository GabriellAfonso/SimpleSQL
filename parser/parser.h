#ifndef PARSER_H
#include "../lexer/token.h"
#define PARSER_H
typedef enum { TYPE_INT, TYPE_TEXT } ColumnType;

typedef struct {
    char name[64];
    ColumnType type;
} Column;

typedef struct Table {
    char name[64];
    int column_count;
    Column columns[16];
} TableStmt;

typedef enum { STMT_CREATE, STMT_INSERT, STMT_DROP } StatementType;

typedef struct {
    StatementType type;
    union {
        TableStmt table_stmt;
        // Futuro: InsertStmt insert_stmt;
    };
} Statement;

int parse_sql(Token* tokens, int* token_count, Statement* out_stmt);
#endif

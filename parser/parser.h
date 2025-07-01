#ifndef PARSER_H
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
} CreateTableStmt;

typedef enum { STMT_CREATE, STMT_INSERT } StatementType;

typedef struct {
    StatementType type;
    union {
        CreateTableStmt create_stmt;
        // Futuro: InsertStmt insert_stmt;
    };
} Statement;

int parse_sql(const char* input, Statement* out_stmt);
#endif

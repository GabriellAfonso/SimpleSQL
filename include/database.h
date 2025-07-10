#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>

#define MAX_TABLES 32
#define MAX_COLUMNS 16
#define MAX_NAME_LEN 64
#define MAX_TEXT_LEN 256
#define MAX_ROWS 1024

// Enum que representa tipos de dados aceitos
typedef enum { TYPE_INT, TYPE_TEXT } ColumnType;

typedef struct {
    int int_value;
    char text_value[MAX_TEXT_LEN];
    // Outras possíveis representações para tipos
} Value;

// Estrutura de uma coluna
typedef struct {
    char name[MAX_NAME_LEN];
    ColumnType type;
} Column;

typedef struct {
    Column columns[MAX_COLUMNS];
    int count;
} ColumnList;

typedef struct {
    Value values[MAX_COLUMNS];  // Um valor para cada coluna da tabela
} Row;

// Estrutura de uma tabela
typedef struct {
    char name[MAX_NAME_LEN];
    int column_count;
    Column columns[MAX_COLUMNS];

    int row_count;
    Row rows[MAX_ROWS];  // Aqui ficam os dados
} Table;

// Estrutura do "banco de dados" em memória
typedef struct {
    int table_count;
    Table tables[MAX_TABLES];
} Database;

// Função para executar CREATE TABLE
int execute_create_table(Database* db, const char* table_name, Column* columns,
                         int column_count);

// // (Futuro) salvar em arquivo
// int save_database(Database* db, const char* filename);
// int load_database(Database* db, const char* filename);

// // (Opcional) função para imprimir o estado atual do banco
// void print_database(const Database* db);

#endif  // DATABASE_H

#include "database.h"

#include <stdio.h>
#include <string.h>
#define DATABASE_FILENAME "simpleql.db"
// Inicializa o banco
void init_database(Database* db) { db->table_count = 0; }

int save_database(Database* db) {
    FILE* f = fopen(DATABASE_FILENAME, "wb");
    if (!f) {
        perror("Erro ao abrir arquivo para salvar");
        return -1;
    }
    size_t written = fwrite(db, sizeof(Database), 1, f);
    fclose(f);

    if (written != 1) {
        printf("Erro ao salvar o banco de dados\n");
        return -1;
    }
    printf("Banco salvo em '%s'\n", DATABASE_FILENAME);
    return 0;
}

// Cria uma nova tabela no banco
int execute_create_table(Database* db, const char* table_name, Column* columns,
                         int column_count) {
    if (db->table_count >= MAX_TABLES) {
        printf("Erro: número máximo de tabelas atingido.\n");
        return -1;
    }
    if (column_count > MAX_COLUMNS) {
        printf("Erro: número máximo de colunas excedido.\n");
        return -1;
    }

    Table* table = &db->tables[db->table_count];
    strncpy(table->name, table_name, MAX_NAME_LEN);
    table->column_count = column_count;
    table->row_count = 0;

    for (int i = 0; i < column_count; i++) {
        strncpy(table->columns[i].name, columns[i].name, MAX_NAME_LEN);
        table->columns[i].type = columns[i].type;
    }

    db->table_count++;
    printf("Tabela '%s' criada com sucesso (%d colunas).\n", table_name,
           column_count);
    save_database(db);  // Salva o banco após criar a tabela
    return 0;
}

// Imprime o banco atual (tabelas, colunas, sem dados por enquanto)
void print_database(const Database* db) {
    printf("Database com %d tabelas:\n", db->table_count);
    for (int i = 0; i < db->table_count; i++) {
        const Table* table = &db->tables[i];
        printf("Tabela '%s' (%d colunas, %d linhas):\n", table->name,
               table->column_count, table->row_count);
        for (int j = 0; j < table->column_count; j++) {
            printf("  Coluna %d: %s (%s)\n", j, table->columns[j].name,
                   table->columns[j].type == TYPE_INT ? "INT" : "TEXT");
        }
    }
}

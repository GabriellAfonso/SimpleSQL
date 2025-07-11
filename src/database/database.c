#include "database.h"

#include <stdio.h>
#include <string.h>

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
    print_database(db);
    return 0;
}

void init_database(Database* db) { db->table_count = 0; }
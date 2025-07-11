#include <stdio.h>
#include <string.h>

#include "database.h"

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

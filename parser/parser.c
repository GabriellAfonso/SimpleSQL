#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ColumnType parse_column_type(const char* type_str) {
    if (strcasecmp(type_str, "INT") == 0) return TYPE_INT;
    if (strcasecmp(type_str, "TEXT") == 0) return TYPE_TEXT;
    return -1;
}

int parse_sql(const char* input, Statement* out_stmt) {
    if (strncasecmp(input, "CREATE TABLE", 12) == 0) {
        out_stmt->type = STMT_CREATE;
        return 0;
    }

    if (strncasecmp(input, "INSERT INTO", 11) == 0) {
        out_stmt->type = STMT_INSERT;
        return 0;
    }

    return -1;
}

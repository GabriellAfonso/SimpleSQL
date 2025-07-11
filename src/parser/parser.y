%{
#include "database.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Database db;
void yyerror(const char* msg);
int yylex(void);

%}

%union {
    char* str;
    int   ival;
    Column column; 
    ColumnList column_list;

}

%token <str> TOKEN_IDENTIFIER
%token TOKEN_CREATE TOKEN_TABLE TOKEN_INT TOKEN_TEXT TOKEN_LPAREN TOKEN_RPAREN TOKEN_COMMA TOKEN_UNKNOWN

%type <ival> type
%type <column_list> column_list
%type <column> column
%%


input:
    command
    ;

command:
    TOKEN_CREATE TOKEN_TABLE TOKEN_IDENTIFIER TOKEN_LPAREN column_list TOKEN_RPAREN {
        execute_create_table(&db, $3, $5.columns, $5.count);
        free($3);

    }
    ;

column_list:
    column {
        $$.columns[0] = $1;
        $$.count = 1;
    }
    | column_list TOKEN_COMMA column {
        $$.count = $1.count + 1;
        for (int i = 0; i < $1.count; i++) $$.columns[i] = $1.columns[i];
        $$.columns[$1.count] = $3;
    }
    ;

column:
    TOKEN_IDENTIFIER type {
        strncpy($$.name, $1, MAX_NAME_LEN);
        $$.name[MAX_NAME_LEN-1] = '\0';
        $$.type = $2;
        free($1);
    }
    ;

type:
    TOKEN_INT     { $$ = TOKEN_INT; }
    | TOKEN_TEXT  { $$ = TOKEN_TEXT; }
    ;

%%

void yyerror(const char* msg) {
    fprintf(stderr, "Erro: %s\n", msg);
}

%{ 
#include "database.h"
#include "parser.tab.h"
#include <string.h>
%}

%%

"CREATE"        return TOKEN_CREATE;
"TABLE"         return TOKEN_TABLE;
"INT"           return TOKEN_INT;
"TEXT"          return TOKEN_TEXT;
"("             return TOKEN_LPAREN;
")"             return TOKEN_RPAREN;
","             return TOKEN_COMMA;
[a-zA-Z_][a-zA-Z0-9_]* {
                    yylval.str = strdup(yytext);
                    return TOKEN_IDENTIFIER;
                 }
[ \t\r\n]+       ; // Ignora espaços
.               return TOKEN_UNKNOWN;

%%
int yywrap(void) {
    return 1;
}

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_CREATE,
    TOKEN_TABLE,
    TOKEN_IDENTIFIER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_INT,
    TOKEN_TEXT,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
} Token;

#endif  // TOKEN_H

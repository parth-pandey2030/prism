#include <string.h>

// Tokens
struct Token {
    const char INT[] = 'INT';
    const char FLOAT[] = 'FLOAT';
    const char PLUS[] = 'PLUS';
    const char MINUS[] = 'MINUS';
    const char MUL[] = 'MUL';
    const char DIV[] = 'DIV';
    const char LPAREN[] = 'LPAREN';
    const char RPAREN[] = 'RPAREN';
};

// Lexer
struct Lexer {
    struct Token token;
    const char DIGITS[] = '0123456789';

};

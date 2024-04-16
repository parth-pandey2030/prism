%{
    char tokens = {};

    const char INT[] = "INT";
    const char FLOAT[] = "FLOAT";
    const char PLUS[] = "PLUS";
    const char MINUS[] = MINUS;
    const char MUL[] = "MUL";
    const char DIV[] = "DIV";
    const char LPAREN[] = "LPAREN";
    const char RPAREN[] = "RPAREN";
    const char IDENTIFIER[] = "IDENTIFIER";
    const char COMMENT[] = "COMMENT";

    const char DIGITS[] = "0123456789";
%}

%%

%%

int yywrap() { }
int main() {
    yylex();

    return 0;
}
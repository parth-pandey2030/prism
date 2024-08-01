#ifndef TOKENS_H
#define TOKENS_H

// Token names
#define TOKEN_IDENTIFIER "identifier"
#define TOKEN_LET "let"
#define TOKEN_CONST "const"
#define TOKEN_PLUS "+"
#define TOKEN_MINUS "-"
#define TOKEN_MULTIPLY "*"
#define TOKEN_DIVIDE "/"
#define TOKEN_MODULO "%"
#define TOKEN_POWER "^"
#define TOKEN_LEFT_PAREN "("
#define TOKEN_RIGHT_PAREN ")"
#define TOKEN_LEFT_SQUARE_BRACKET "["
#define TOKEN_RIGHT_SQUARE_BRACKET "]"
#define TOKEN_LEFT_CURLY_BRACKET "{"
#define TOKEN_RIGHT_CURLY_BRACKET "}"
#define TOKEN_COMMA ","
#define TOKEN_COLON ":"
#define TOKEN_ASSIGNMENT "="
#define TOKEN_EQUAL "=="
#define TOKEN_NOT_EQUAL "!="
#define TOKEN_GREATER_THAN ">"
#define TOKEN_GREATER_THAN_OR_EQUAL ">="
#define TOKEN_LESS_THAN "<"
#define TOKEN_LESS_THAN_OR_EQUAL "<="
#define TOKEN_AND "and"
#define TOKEN_OR "or"
#define TOKEN_NOT "not"
#define TOKEN_TRUE "true"
#define TOKEN_FALSE "false"
#define TOKEN_IF "if"
#define TOKEN_ELSE "else"
#define TOKEN_FOR "for"
#define TOKEN_IN "in"
#define TOKEN_INT "int"
#define TOKEN_FLOAT "float"
#define TOKEN_IRRATIONAL "irrational"
#define TOKEN_BOOLEAN "boolean"
#define TOKEN_COMPLEX "complex"
#define TOKEN_STRING "string"
#define TOKEN_ARRAY "array"
#define TOKEN_SET "set"
#define TOKEN_HASH "hash"
#define TOKEN_OPERATOR "operator"
#define TOKEN_PUNCTUATION "punctuation"
#define TOKEN_FOR_LOOP "forLoop"
#define TOKEN_WHILE_LOOP "whileLoop"
#define TOKEN_FINISHED_LOOP "finishedLoop"
#define TOKEN_CONTINUE_LOOP "continueLoop"
#define TOKEN_BREAK_LOOP "breakLoop"
#define TOKEN_COMMENT "comment"
#define TOKEN_WHITESPACE "whitespace"
#define TOKEN_NEW_LINE "newLine"
#define TOKEN_INFINITY "infinity"
#define TOKEN_NULL "null"
#define TOKEN_UNDEFINED "undefined"
#define TOKEN_NAN "nan"
#define TOKEN_FUNCTION "function"

// Token patterns

#define PATTERN_IDENTIFIER "^[a-zA-Z_][a-zA-Z0-9_]*$"
#define PATTERN_LET "^let$"
#define PATTERN_CONST "^const$"
#define PATTERN_INT "^[0-9]+$"
#define PATTERN_FLOAT "^[0-9]+\\.[0-9]+$"
#define PATTERN_IRRATIONAL "^[0-9]+\\.[0-9]+[eE][+-]?[0-9]+$"
#define PATTERN_BOOLEAN "^(true|false)$"
#define PATTERN_COMPLEX "^[0-9]+\\.[0-9]+[iJ][+-]?[0-9]+$"
#define PATTERN_STRING "^[a-zA-Z_][a-zA-Z0-9_]*$"
#define PATTERN_ARRAY "^[\\[\\]\\,\\s]*$"
#define PATTERN_SET "^()$"
#define PATTERN_HASH "^{}$"
#define PATTERN_OPERATOR "^[+\\-]+$"
#define PATTERN_PUNCTUATION "^[{}()[\\]\\.\\,;:]$"
#define PATTERN_FOR_LOOP "^for$"
#define PATTERN_WHILE_LOOP "^while$"
#define PATTERN_FINISHED_LOOP "^finish$"
#define PATTERN_CONTINUE_LOOP "^continue$"
#define PATTERN_BREAK_LOOP "^break$"
#define PATTERN_COMMENT "^#//.*/*$"
#define PATTERN_WHITESPACE "^[ \t]+$"
#define PATTERN_NEW_LINE "^\\n$"
#define PATTERN_INFINITY "^inf$"
#define PATTERN_NULL "^null$"
#define PATTERN_UNDEFINED "^undefined$"
#define PATTERN_NAN "^nan$"
#define PATTERN_FUNCTION "^func$"

#endif // TOKENS_H

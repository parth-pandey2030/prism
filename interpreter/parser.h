#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "errors.h"
#include "cJSON.h"

struct parser; // Structure for AST
struct parser parsefile(const char* filedata); // Parses file and creates AST as structure
void converter(const struct structure); // Converts AST to JSON
void out(const char* filename, const cJSON* data); // Writes JSON to file

#endif 


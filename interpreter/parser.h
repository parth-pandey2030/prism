#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "hash_table.h"
#include "errors.h"
#include "../lib/cJSON.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


int starts_with(const char* string, const char* substring);
HashTable* parsefile(const char* filedata); // Parses file and creates AST
cJSON* converter(const HashTable* obj); // Converts AST to JSON
void out(const char* filename, const cJSON* data); // Writes JSON to file

#endif 


#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "hash_table.h"
#include "errors.h"
#include "cJSON.h"
#include <stddef.h>

#define FIELD_INFO(type, field) {#field, offsetof(type, field), sizeof(((type*)0)->field)}

HashTable* parser; // Hash for AST
void printStructFieldInfo(parser* AST, FieldInfo* fields, int field_count);
void loopOver(parser* AST, FieldInfo* fields, int field_count);

HashTable* parser parsefile(const char* filedata); // Parses file and creates AST as structure
cJSON* converter(const HashTable* obj); // Converts AST to JSON
void out(const char* filename, const cJSON* data); // Writes JSON to file

#endif 


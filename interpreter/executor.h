#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"
#include "../lib/cJSON.h"
#include "hash_table.h"
#include <stdio.h>

void execute(const HashTable* AST);

#endif
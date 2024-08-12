#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"
#include "../lib/cJSON.h"
#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
void interpret_and_execute(const cJSON* json);
void execute_line(const char* code_line);
void execute(const char* code);

#endif
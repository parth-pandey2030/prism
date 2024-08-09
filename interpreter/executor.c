#include "executor.h"

void execute(const HashTable* AST) {
    if (AST == NULL) {
        return;
    }

    const HashTable* declarations = HT_GET(AST, "declarations");
    const HashTable* init = HT_GET(declarations, "init");

    
}
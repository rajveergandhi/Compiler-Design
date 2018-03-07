#ifndef SYMBOL_H
#define SYMBOL_H

#include "tree.h"

#define HashSize 317

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *next;
} SymbolTable;

SymbolTable *initSymbolTable();

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind);
SYMBOL *getSymbol(SymbolTable *t, char *name);

int defSymbol(SymbolTable *t, char *name);

SymbolTable *symbolTop;

void symPROGRAM(PROGRAM *p);
void symTOPLEVELDECL(TOPLEVELDECL *p, SymbolTable *sym);
void symTOPLEVELDECLVARTYPE(DCL *p, SymbolTable *sym);
void symTOPLEVELDECLVAR(VARDCL *p, SymbolTable *sym);
void symTOPLEVELDECLTYPE(TYPEDCL *p, SymbolTable *sym);
void printTYPE(TYPE *node);

#endif

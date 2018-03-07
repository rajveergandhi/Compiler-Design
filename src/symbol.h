#ifndef SYMBOL_H
#define SYMBOL_H

#include "tree.h"

#define HashSize 317

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *next;
} SymbolTable;

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind);
SYMBOL *getSymbol(SymbolTable *t, char *name);

int defSymbol(SymbolTable *t, char *name);

SymbolTable *symbolTop;

void symPROGRAM(PROGRAM *p);
void symTOPLEVELDECL(TOPLEVELDECL *p, SymbolTable *sym);
void symTOPLEVELDECLVARTYPE(DCL *p, SymbolTable *sym);
void symTOPLEVELDECLVAR(VARDCL *p, SymbolTable *sym);
void symTOPLEVELDECLTYPE(TYPEDCL *p, SymbolTable *sym);
void symTOPLEVELDECLFUNC(FUNCDCL *p, SymbolTable *sym);
void symFUNC_SIGNATURE(FUNC_SIGNATURE *p, SymbolTable *sym);
void symFUNC_BODY(BLOCK *p, SymbolTable *sym);
void symSTATEMENTS(STATEMENTS *p, SymbolTable *sym);
void symSTATEMENT(STATEMENT *p, SymbolTable *sym);
void symSIMPLE(SIMPLE *p, SymbolTable *sym);
void symEXPR(EXPR *p, SymbolTable *sym);

#endif

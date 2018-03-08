#ifndef SYMBOL_H
#define SYMBOL_H
#include "tree.h"

#define HashSize 317

//typedef enum { topSym, formalSym } SymbolKind;

typedef enum { type_category, variable_category, function_category, constant_category, } SymbolKind;
typedef struct SYMBOL {
    char *name;
    SymbolKind kind;
    // get rid of union val
    union {
        TOPLEVELDECL *topS;
        DCL *dclS;
        FUNCDCL *methodS;
        FUNC_SIGNATURE *formalS;
    } val;
    struct SYMBOL *next;
} SYMBOL;

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
} SymbolTable;

SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *t);
SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind, TYPE *type, int lineno);
SYMBOL *getSymbol(SymbolTable *t, char *name);
int defSymbol(SymbolTable *t, char *name);

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

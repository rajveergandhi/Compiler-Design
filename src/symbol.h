#ifndef SYMBOL_H
#define SYMBOL_H
#include "tree.h"

#define HashSize 317

typedef enum { type_category, variable_category, function_category, constant_category, } SymbolCategory;
typedef enum { type_type, func_signature_type, } typeKind;
typedef struct DataType {
    SymbolCategory category;
    typeKind valKind;
    union {
        TYPE *type;
        FUNC_SIGNATURE *func;
    } val;
} DataType;

typedef struct SYMBOL {
    char *name;
    DataType *data;
    struct SYMBOL *next;
} SYMBOL;

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
} SymbolTable;

// SYMBOL and SymbolTable management functions
SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *t);
SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolCategory category, typeKind valKind, void *p, int lineno);
void addSymbolType(SymbolTable *sym, char *name, DataType *dat);
SYMBOL *getSymbol(SymbolTable *sym, char *name, int lineno);
bool defSymbol(SymbolTable *t, char *name);

// AST traversal functions
void symPROGRAM(PROGRAM *p);
void symTOPLEVELDECL(TOPLEVELDECL *p, SymbolTable *sym);
void symDCL(DCL *p, SymbolTable *sym);
void symVARDCL(VARDCL *p, SymbolTable *sym);
void symEXPRLIST(EXPRLIST *node, SymbolTable *sym);
void symEXPR(EXPR *node, SymbolTable *sym);
void symOTHER_EXPR(OTHER_EXPR *node, SymbolTable *sym);
void symTYPEDCL(TYPEDCL *p, SymbolTable *sym);
void symFUNCDCL(FUNCDCL *p, SymbolTable *sym);
void symFUNC_SIGNATURE(FUNC_SIGNATURE *node, SymbolTable *sym);
void symTYPE(TYPE *node, SymbolTable *sym);
void symBLOCK(BLOCK *node, SymbolTable *sym, SymbolTable *extra);
void symSTATEMENTS(STATEMENTS *node, SymbolTable *sym);
void symSTATEMENT(STATEMENT *node, SymbolTable *sym);
void symSWITCH_CASELIST(SWITCH_CASELIST *node, SymbolTable *sym);
void symSIMPLE(SIMPLE *node, SymbolTable *sym);

// helper functions
void scopeInc();
void scopeDec();
void printSymbol(SYMBOL *s);

#endif

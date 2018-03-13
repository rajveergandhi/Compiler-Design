#ifndef SYMBOL_H
#define SYMBOL_H
#include "tree.h"

#define HashSize 317

typedef enum { type_category, variable_category, function_category, constant_category, } SymbolCategory;
typedef enum { basic_type, type_type, func_signature_type, } symbolType;
typedef enum { k_int, k_float64, k_string, k_rune, k_bool } SymbolBaseKind;
typedef struct symTYPE {
    SymbolCategory category;
    symbolType symtype;
    union {
        SymbolBaseKind base;
        TYPE *symtype;
        FUNC_SIGNATURE *symsign;
    } val;
} symTYPE;

typedef struct SYMBOL {
    char *name;
    symTYPE *data;
    struct SYMBOL *next;
} SYMBOL;

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
} SymbolTable;

// symbol and symbolTable management functions
SymbolTable *initSymbolTable();
SymbolTable *scopeSymbolTable(SymbolTable *t);
SYMBOL *putSymbol(SymbolTable *t, char *name, symTYPE *data, int lineno);
void addSymbolType(SymbolTable *t, char *name, TYPE *type);
SYMBOL *getSymbol(SymbolTable *sym, char *name, int lineno);
bool defSymbol(SymbolTable *t, char *name);

// AST traversal functions
void symPROGRAM(PROGRAM *p);
void symTOPLEVELDECL(TOPLEVELDECL *p, SymbolTable *sym);
void symDCL(DCL *p, SymbolTable *sym);
void symVARDCL(VARDCL *p, SymbolTable *sym);
void symTYPEDCL(TYPEDCL *p, SymbolTable *sym);
void symFUNCDCL(FUNCDCL *p, SymbolTable *sym);
void symFUNC_SIGNATURE(FUNC_SIGNATURE *node, SymbolTable *sym);
void symBLOCK(BLOCK *node, SymbolTable *sym, SymbolTable *extra);
void symSTATEMENTS(STATEMENTS *node, SymbolTable *sym);
void symSTATEMENT(STATEMENT *node, SymbolTable *sym);
void symSWITCH_CASELIST(SWITCH_CASELIST *node, SymbolTable *sym);
void symSIMPLE(SIMPLE *node, SymbolTable *sym);
void symEXPRLIST(EXPRLIST *node, SymbolTable *sym);
void symEXPR(EXPR *node, SymbolTable *sym);
void symOTHER_EXPR(OTHER_EXPR *node, SymbolTable *sym);
void symSTRUCT_TYPE(STRUCT_TYPE *node);

// helper functions
void scopeInc();
void scopeDec();
void printSymbol(char *name, symTYPE *data);

#endif

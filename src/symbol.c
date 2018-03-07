#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

extern int g_symbols;

int Hash(char *str) {
    unsigned int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}

SymbolTable *initSymbolTable() {
    SymbolTable *t;
    int i;
    t = malloc(sizeof(SymbolTable));
    for (i=0; i < HashSize; i++) t->table[i] = NULL;
    t->next = NULL;
    return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind) {
    int i = Hash(name);
    SYMBOL *s;
    for (s = t->table[i]; s; s=s->next) {
        if (strcmp(s->name,name)==0)
            return s;
    }
    s = malloc(sizeof(SYMBOL));
    s->name = name;
    s->kind = kind;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

SYMBOL *getSymbol(SymbolTable *t, char *name) {
    int i = Hash(name);
    SYMBOL *s;
    for (s = t->table[i]; s; s=s->next) {
        if (strcmp(s->name,name)==0)
            return s;
    }
    if (t->next==NULL)
        return NULL;
    return getSymbol(t->next, name);
}

int defSymbol(SymbolTable *t, char *name) {
    int i = Hash(name);
    SYMBOL *s;
    for (s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name)==0)
            return 1;
    }
    return 0;
}

void symPROGRAM(PROGRAM *p) {
    symbolTop = initSymbolTable();
    symTOPLEVELDECL(p->topleveldecls,symbolTop);
}

void symTOPLEVELDECL(TOPLEVELDECL *p, SymbolTable *sym) {
    if (p!=NULL) {
        symTOPLEVELDECL(p->next, sym);
        symTOPLEVELDECLVARTYPE(p->val.dcl, sym);
        // symTOPLEVELDECLFUNC(p->val.funcdcl, sym);
    }
}

void symTOPLEVELDECLVARTYPE(DCL *p, SymbolTable *sym) {
    if (p!=NULL) {
        switch (p->kind) {
            case var:
                symTOPLEVELDECLVAR(p->val.vardcl, sym);
                break;
            case type:
                symTOPLEVELDECLTYPE(p->val.typedcl, sym);
                break;
        }
    }
}

void symTOPLEVELDECLVAR(VARDCL *p, SymbolTable *sym) {
    SYMBOL *s;
    if (p!=NULL) {
        if (p->type) {
            s = putSymbol(sym, p->idlist->id, topSym);
            if (g_symbols) printf("%s: %s\n", p->idlist->id, p->type->val.basic_type);
        }
        else if (p->exprlist) {
            switch (p->exprlist->expr->kind) {
                case intval:
                    s = putSymbol(sym, p->idlist->id, topSym);
                    if (g_symbols) printf("%s: %s\n", p->idlist->id, "int");
                    break;
                case floatval:
                    s = putSymbol(sym, p->idlist->id, topSym);
                    if (g_symbols) printf("%s: %s\n", p->idlist->id, "float");
                    break;
                case stringval:
                    s = putSymbol(sym, p->idlist->id, topSym);
                    if (g_symbols) printf("%s: %s\n", p->idlist->id, "string");
                    break;
                case rawstringval:
                    s = putSymbol(sym, p->idlist->id, topSym);
                    if (g_symbols) printf("%s: %s\n", p->idlist->id, "raw string");
                    break;
                case runeval:
                    s = putSymbol(sym, p->idlist->id, topSym);
                    if (g_symbols) printf("%s: %s\n", p->idlist->id, "rune");
                    break;
            }
        }
    }
}

void symTOPLEVELDECLTYPE(TYPEDCL *p, SymbolTable *sym) {
    SYMBOL *s;
    if (p!=NULL) {
        s = putSymbol(sym, p->identifier, topSym);
        if (g_symbols) printf("%s: %s\n", p->identifier, p->type->val.basic_type);
    }
}

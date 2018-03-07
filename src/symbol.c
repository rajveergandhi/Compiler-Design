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
        symTOPLEVELDECLVAR(p->next, sym);
        if (p->type) {
            // handle cases like
            // var x1, x2 int
            // var z1, z2 int = 1, 2
            for (IDLIST *i = p->idlist; i; i = i->next) {
                s = putSymbol(sym, i->id, topSym);
                if (g_symbols) printf("%s: %s\n", i->id, p->type->val.basic_type);
            }
        }
        else if (p->exprlist) {
            // handle cases like
            // var y1, y2 = 42, 43
            switch (p->exprlist->expr->kind) {
                case intval:
                    for (IDLIST *i = p->idlist; i; i = i->next) {
                        s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "int");
                    }
                    break;
                case floatval:
                    for (IDLIST *i = p->idlist; i; i = i->next) {
                        s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "float");
                    }
                    break;
                case stringval:
                    for (IDLIST *i = p->idlist; i; i = i->next) {
                        s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "string");
                    }
                    break;
                case rawstringval:
                    for (IDLIST *i = p->idlist; i; i = i->next) {
                        s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "raw string");
                    }
                    break;
                case runeval:
                    for (IDLIST *i = p->idlist; i; i = i->next) {
                        s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "rune");
                    }
                    break;
            }
        }
    }
}

void symTOPLEVELDECLTYPE(TYPEDCL *p, SymbolTable *sym) {
    SYMBOL *s;
    if (p!=NULL) {
        symTOPLEVELDECLTYPE(p->next, sym);
        if (p->type->kind == struct_type_kind) {
            // handle cases like
            // type point struct { x, y float64 }
            for (STRUCT_TYPE *i = p->type->val.struct_type; i; i = i->next) {
                for (IDLIST *j = i->idlist; j; j = j->next) {
                    s = putSymbol(sym, j->id, topSym);
                    if (g_symbols) printf("%s: %s\n", j->id, i->type->val.basic_type);
                }
            }
        }
        else {
            // handle cases like
            // type num int
            s = putSymbol(sym, p->identifier, topSym);
            if (g_symbols) printf("%s: %s\n", p->identifier, p->type->val.basic_type);
        }
    }
}

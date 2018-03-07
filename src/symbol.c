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

SymbolTable *scopeSymbolTable(SymbolTable *s)
{ SymbolTable *t;
  t = initSymbolTable();
  t->next = s;
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
        switch (p->kind) {
            case dcl_toplevel:
                symTOPLEVELDECLVARTYPE(p->val.dcl, sym);
                break;
            case func_dcl_toplevel:
                symTOPLEVELDECLFUNC(p->val.funcdcl, sym);
                break;
        }
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

void symTOPLEVELDECLFUNC(FUNCDCL *p, SymbolTable *sym) {
    SymbolTable *msym;
    if (p!=NULL) {
        //symTOPLEVELDECLFUNC(p->next, sym);
        msym = scopeSymbolTable(sym);
        symFUNC_SIGNATURE(p->signature, msym);
        symFUNC_BODY(p->block, msym);
    }
}

void symFUNC_SIGNATURE(FUNC_SIGNATURE *p, SymbolTable *sym) {
    SYMBOL *s;
    if (p!=NULL) {
        for (PARAM_LIST *i = p->params; i; i = i->next) {
            for (IDLIST *j = i->idlist; j; j = j->next) {
                // FORMAL PARAMETERS
                if (defSymbol(sym,j->id)) {
                     fprintf(stderr, "Error: (line %d) formal %s already declared",j->lineno,j->id);
                     exit(1);
                }
                else {
                    s = putSymbol(sym, j->id, formalSym);
                    s->val.formalS = p;
                    if (g_symbols) printf("%s: %s\n", j->id, i->type->val.basic_type);
                }
            }
        }
    }
}

void symFUNC_BODY(BLOCK *p, SymbolTable *sym) {
    if (p!=NULL) {
        symSTATEMENTS(p->stmts, sym);
    }
}

void symSTATEMENTS(STATEMENTS *p, SymbolTable *sym) {
    if (p!=NULL) {
        symSTATEMENTS(p->next, sym);
        symSTATEMENT(p->stmt, sym);
    }
}

void symSTATEMENT(STATEMENT *p, SymbolTable *sym) {
    if (p!=NULL) {
        switch(p->kind) {
            case dcl_s:
                symTOPLEVELDECLVARTYPE(p->val.dcl, sym);
                break;
            case simple_s:
                symSIMPLE(p->val.simple, sym);
                break;
            case return_stmt_s:
                break;
            case break_stmt_s:
                break;
            case continue_stmt_s:
                break;
            case block_s:
                break;
            case if_stmt_s:
                break;
            case switch_stmt_s:
                break;
            case for_stmt_s:
                break;
            case print_stmt_s:
                break;
            case println_stmt_s:
                break;
            }
    }
}

void symSIMPLE(SIMPLE *p, SymbolTable *sym) {
    switch (p->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            symEXPR(p->val.expr, sym);
            break;
        case increment_kind:
            //prettyEXPR(node->val.expr);
            break;
        case decrement_kind:
            //prettyEXPR(node->val.expr);
            break;
        case assignment_kind:
            // prettyEXPRLIST(node->val.assignment.LHS_expr_list);
            // prettyEXPRLIST(node->val.assignment.RHS_expr_list);
            break;
        case shortDcl_kind:
            // prettyEXPRLIST(node->val.shortDcl.LHS_expr_list);
            // prettyEXPRLIST(node->val.shortDcl.RHS_expr_list);
            break;
    }
}

void symEXPR(EXPR *p, SymbolTable *sym) {
    switch (p->kind) {
        case expressionKindPlus:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindMinus:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindMult:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindDiv:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindMod:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindLT:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindLT_EQ:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindGT:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindGT_EQ:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindEQ_EQ:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindNotEquals:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindShift_Right:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindShift_Left:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindAnd:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindAMP_XOR:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindOr:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindXor:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindLogicalAnd:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindLogicalOr:
            // prettyEXPR(node->val.binary.lhs);
            // prettyEXPR(node->val.binary.rhs);
            break;
        case expressionKindPlusUnary:
            // prettyEXPR(node->val.expr_unary);
            break;
        case expressionKindMinusUnary:
            // prettyEXPR(node->val.expr_unary);
            break;
        case expressionKindNotUnary:
            // prettyEXPR(node->val.expr_unary);
            break;
        case expressionKindXorUnary:
            // prettyEXPR(node->val.expr_unary);
            break;
        case append_expr:
            // prettyEXPR(node->val.append_expr.expr);
            break;
        case intval:
            break;
        case floatval:
            break;
        case stringval:
            break;
        case rawstringval:
            break;
        case runeval:
            break;
        case other_expr_kind:
            // prettyOTHER_EXPR(node->val.other_expr);
            break;
        }
}

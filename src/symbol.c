#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

extern int g_symbols;

// global indentation variable; it is incremented wherever necessary
int g_symIndent = 0;

void symIndent(int indent_level) {
    int indent_val = 4; // one level of indentation is defined as 4 spaces
    for (int i = 0; i < indent_val * indent_level; ++i) {
        printf(" ");
    }
}

int Hash(char *str) {
    unsigned int hash = 0;
    while (*str) hash = (hash << 1) + *str++;
    return hash % HashSize;
}

SymbolTable *initSymbolTable() {
    SymbolTable *t = malloc(sizeof(SymbolTable));
    for (int i=0; i < HashSize; i++)
        t->table[i] = NULL;
    t->parent = NULL;
    return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s) {
    SymbolTable *t = initSymbolTable();
    t->parent = s;
    return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind, TYPE *type, int lineno) {
    int i = Hash(name);
    SYMBOL *s;
    for (s = t->table[i]; s; s=s->next) {
        if (strcmp(s->name,name)==0) {
            fprintf(stderr, "Error: (line %d) \"%s\" is already declared\n", lineno, name);
            exit(1);
        }
    }
    s = malloc(sizeof(SYMBOL));
    s->name = name;
    s->kind = kind;
    s->next = t->table[i];
    t->table[i] = s;

    // if g_symbols turned on, then print symbol
    if (g_symbols) {
        symIndent(g_symIndent);
        char *sym_kind;
        switch (kind) {
            case type_category:
                sym_kind = "type";
                break;
            case variable_category:
                sym_kind = "variable";
                break;
            case function_category:
                sym_kind = "function";
                break;
            case constant_category:
                sym_kind = "constant";
                break;
        }
        if (type) {
            switch (type->kind) {
                case basic_type_kind:
                    printf("%s [%s] = %s\n", name, sym_kind, type->val.basic_type);
                    break;
                case slice_type_kind:
                    printf("%s [%s] = <sliceType>\n", name, sym_kind);
                    break;
                case array_type_kind:
                    printf("%s [%s] = <arrayType>\n", name, sym_kind, type->val.basic_type);
                    break;
                case struct_type_kind:
                    printf("%s [%s] = <structType>\n", name, sym_kind, type->val.basic_type);
                    break;
            }
        }
        else
            printf("%s [%s] = <infer>\n", name, sym_kind);
    }

    return s;
}

SYMBOL *getSymbol(SymbolTable *t, char *name) {
    int i = Hash(name);
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name,name) == 0)
            return s;
    }
    if (t->parent == NULL)
        return NULL;
    return getSymbol(t->parent, name);
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

void symPROGRAM(PROGRAM *node) {
    if (g_symbols) { symIndent(g_symIndent); printf("{\n"); }
    g_symIndent++;

    SymbolTable *sym = initSymbolTable();
    TYPE *type_true = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "bool";
    putSymbol(sym, "true", constant_category, type_true, node->lineno);
    TYPE *type_false = malloc(sizeof(TYPE)); type_false->kind = basic_type_kind; type_false->val.basic_type = "bool";
    putSymbol(sym, "false", constant_category, type_false, node->lineno);
    TYPE *type_int = malloc(sizeof(TYPE)); type_int->kind = basic_type_kind; type_int->val.basic_type = "int";
    putSymbol(sym, "int", type_category, type_int, node->lineno);
    TYPE *type_float64 = malloc(sizeof(TYPE)); type_float64->kind = basic_type_kind; type_float64->val.basic_type = "float64";
    putSymbol(sym, "float64", type_category, type_float64, node->lineno);
    TYPE *type_rune = malloc(sizeof(TYPE)); type_rune->kind = basic_type_kind; type_rune->val.basic_type = "rune";
    putSymbol(sym, "rune", type_category, type_rune, node->lineno);
    TYPE *type_bool = malloc(sizeof(TYPE)); type_bool->kind = basic_type_kind; type_bool->val.basic_type = "bool";
    putSymbol(sym, "bool", type_category, type_bool, node->lineno);
    TYPE *type_string = malloc(sizeof(TYPE)); type_string->kind = basic_type_kind; type_string->val.basic_type = "string";
    putSymbol(sym, "string", type_category, type_string, node->lineno);

    node->symboltable = sym;

    if (g_symbols) { symIndent(g_symIndent); printf("{\n"); }
    g_symIndent++;
    symTOPLEVELDECL(node->topleveldecls, sym);
    g_symIndent--;
    if (g_symbols) { symIndent(g_symIndent); printf("}\n"); }
    g_symIndent--;
    if (g_symbols) { symIndent(g_symIndent); printf("}\n"); }
}

void symTOPLEVELDECL(TOPLEVELDECL *node, SymbolTable *sym) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        switch (i->kind) {
            case dcl_toplevel:
                symDCL(i->val.dcl, sym);
                break;
            case func_dcl_toplevel:
                symFUNCDCL(i->val.funcdcl, sym);
                break;
        }
    }
}

void symDCL(DCL *node, SymbolTable *sym) {
    switch (node->kind) {
        case var:
            symVARDCL(node->val.vardcl, sym);
            break;
        case type:
            symTYPEDCL(node->val.typedcl, sym);
            break;
    }
}

void symVARDCL(VARDCL *node, SymbolTable *sym) {
    for (VARDCL *i = node; i; i = i->next)
        for (IDLIST *j = i->idlist; j; j = j->next)
            putSymbol(sym, j->id, variable_category, i->type, node->lineno);
}

void symTYPEDCL(TYPEDCL *node, SymbolTable *sym) {
    for (TYPEDCL *i = node; i; i = i->next)
        putSymbol(sym, i->identifier, type_category, i->type, node->lineno);
}

void symFUNCDCL(FUNCDCL *node, SymbolTable *sym) {
    putSymbol(sym, node->identifier, function_category, node->signature, node->lineno);
    //prettyBLOCK(node->block);
}

/*
void symTOPLEVELDECLVARTYPE(DCL *node, SymbolTable *sym) {
    if (node!=NULL) {
        switch (node->kind) {
            case var:
                symTOPLEVELDECLVAR(node->val.vardcl, sym);
                break;
            case type:
                symTOPLEVELDECLTYPE(node->val.typedcl, sym);
                break;
        }
    }
}

void symTOPLEVELDECLVAR(VARDCL *node, SymbolTable *sym) {
    SYMBOL *s;
    if (node!=NULL) {
        symTOPLEVELDECLVAR(node->next, sym);
        if (node->type) {
            // handle cases like
            // var x1, x2 int
            // var z1, z2 int = 1, 2
            for (IDLIST *i = node->idlist; i; i = i->next) {
                //s = putSymbol(sym, i->id, topSym);
                if (g_symbols) printf("%s: %s\n", i->id, node->type->val.basic_type);
            }
        }
        else if (node->exprlist) {
            // handle cases like
            // var y1, y2 = 42, 43
            switch (node->exprlist->expr->kind) {
                case intval:
                    for (IDLIST *i = node->idlist; i; i = i->next) {
                        //s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "int");
                    }
                    break;
                case floatval:
                    for (IDLIST *i = node->idlist; i; i = i->next) {
                        //s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "float");
                    }
                    break;
                case stringval:
                    for (IDLIST *i = node->idlist; i; i = i->next) {
                        //s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "string");
                    }
                    break;
                case rawstringval:
                    for (IDLIST *i = node->idlist; i; i = i->next) {
                        //s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "raw string");
                    }
                    break;
                case runeval:
                    for (IDLIST *i = node->idlist; i; i = i->next) {
                        //s = putSymbol(sym, i->id, topSym);
                        if (g_symbols) printf("%s: %s\n", i->id, "rune");
                    }
                    break;
            }
        }
    }
}

void symTOPLEVELDECLTYPE(TYPEDCL *node, SymbolTable *sym) {
    SYMBOL *s;
    if (node!=NULL) {
        symTOPLEVELDECLTYPE(node->next, sym);
        if (node->type->kind == struct_type_kind) {
            // handle cases like
            // type point struct { x, y float64 }
            for (STRUCT_TYPE *i = node->type->val.struct_type; i; i = i->next) {
                for (IDLIST *j = i->idlist; j; j = j->next) {
                    //s = putSymbol(sym, j->id, topSym);
                    if (g_symbols) printf("%s: %s\n", j->id, i->type->val.basic_type);
                }
            }
        }
        else {
            // handle cases like
            // type num int
            //s = putSymbol(sym, node->identifier, topSym);
            if (g_symbols) printf("%s: %s\n", node->identifier, node->type->val.basic_type);
        }
    }
}

void symTOPLEVELDECLFUNC(FUNCDCL *node, SymbolTable *sym) {
    SymbolTable *msym;
    if (node!=NULL) {
        //symTOPLEVELDECLFUNC(node->next, sym);
        msym = scopeSymbolTable(sym);
        symFUNC_SIGNATURE(node->signature, msym);
        symFUNC_BODY(node->block, msym);
    }
}

void symFUNC_SIGNATURE(FUNC_SIGNATURE *node, SymbolTable *sym) {
    SYMBOL *s;
    if (node!=NULL) {
        for (PARAM_LIST *i = node->params; i; i = i->next) {
            for (IDLIST *j = i->idlist; j; j = j->next) {
                // FORMAL PARAMETERS
                if (defSymbol(sym,j->id)) {
                     fprintf(stderr, "Error: (line %d) formal %s already declared",j->lineno,j->id);
                     exit(1);
                }
                else {
                    //s = putSymbol(sym, j->id, formalSym);
                    s->val.formalS = node;
                    if (g_symbols) printf("%s: %s\n", j->id, i->type->val.basic_type);
                }
            }
        }
    }
}

void symFUNC_BODY(BLOCK *node, SymbolTable *sym) {
    if (node!=NULL) {
        symSTATEMENTS(node->stmts, sym);
    }
}

void symSTATEMENTS(STATEMENTS *node, SymbolTable *sym) {
    if (node!=NULL) {
        symSTATEMENTS(node->next, sym);
        symSTATEMENT(node->stmt, sym);
    }
}

void symSTATEMENT(STATEMENT *node, SymbolTable *sym) {
    if (node!=NULL) {
        switch(node->kind) {
            case dcl_s:
                symTOPLEVELDECLVARTYPE(node->val.dcl, sym);
                break;
            case simple_s:
                symSIMPLE(node->val.simple, sym);
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

void symSIMPLE(SIMPLE *node, SymbolTable *sym) {
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            symEXPR(node->val.expr, sym);
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

void symEXPR(EXPR *node, SymbolTable *sym) {
    switch (node->kind) {
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
*/

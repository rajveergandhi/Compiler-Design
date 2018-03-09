#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "pretty.h"

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

void scopeInc() {
    if (g_symbols) {
        symIndent(g_symIndent);
        printf("{\n");
    }
    g_symIndent++;
}

void scopeDec() {
    g_symIndent--;
    if (g_symbols) {
        symIndent(g_symIndent);
        printf("}\n");
    }
}

SYMBOL *putSymbol(SymbolTable *t, char *name, symTYPE *data, int lineno) {
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
    s->data = data;
    s->next = t->table[i];
    t->table[i] = s;

    // if g_symbols turned on, then print symbol
    if (g_symbols) {
        symIndent(g_symIndent);
        char *sym_cat;
        switch (data->category) {
            case type_category:
                sym_cat = "type";
                break;
            case variable_category:
                sym_cat = "variable";
                break;
            case function_category:
                sym_cat = "function";
                break;
            case constant_category:
                sym_cat = "constant";
                break;
        }

        switch (data->symtype) {
            case type_type:
                if (data->val.symtype) {
                    switch (data->val.symtype->kind) {
                        case basic_type_kind:
                            printf("%s [%s] = %s\n", name, sym_cat, data->val.symtype->val.basic_type);
                            break;
                        case slice_type_kind:
                            printf("%s [%s] = ", name, sym_cat);
                            prettyTYPE(data->val.symtype);
                            printf("\n");
                            break;
                        case array_type_kind:
                            printf("%s [%s] = ", name, sym_cat);
                            prettyTYPE(data->val.symtype);
                            printf("\n");
                            break;
                        case struct_type_kind:
                            printf("%s [%s] = ", name, sym_cat);
                            prettyTYPE(data->val.symtype);
                            printf("\n");
                            break;
                    }
                }
                else
                    printf("%s [%s] = <infer>\n", name, sym_cat);
                break;
            case func_signature_type:
                symPrettyFUNC_SIGNATURE(data->val.symsign);
                break;
        }
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

symTYPE *initSymType(SymbolCategory category, symbolType symtype, void *p) {
    symTYPE *ret = malloc(sizeof(symTYPE));
    ret->category = category;
    ret->symtype = symtype;
    switch (symtype) {
        case type_type:
            ret->val.symtype = (TYPE *) p;
            break;
        case func_signature_type:
            ret->val.symsign = (FUNC_SIGNATURE *) p;
            break;
    }
    return ret;
}

void symPROGRAM(PROGRAM *node) {
    scopeInc();

    SymbolTable *sym = initSymbolTable();
    TYPE *type_true = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "bool";
    symTYPE *sym_true = initSymType(constant_category, type_type, type_true);
    putSymbol(sym, "true", sym_true, node->lineno);
    TYPE *type_false = malloc(sizeof(TYPE)); type_false->kind = basic_type_kind; type_false->val.basic_type = "bool";
    symTYPE *sym_false = initSymType(constant_category, type_type, type_false);
    putSymbol(sym, "false", sym_false, node->lineno);
    TYPE *type_bool = malloc(sizeof(TYPE)); type_bool->kind = basic_type_kind; type_bool->val.basic_type = "bool";
    symTYPE *sym_bool = initSymType(type_category, type_type, type_bool);
    putSymbol(sym, "bool", sym_bool, node->lineno);
    TYPE *type_int = malloc(sizeof(TYPE)); type_int->kind = basic_type_kind; type_int->val.basic_type = "int";
    symTYPE *sym_int = initSymType(type_category, type_type, type_int);
    putSymbol(sym, "int", sym_int, node->lineno);
    TYPE *type_float64 = malloc(sizeof(TYPE)); type_float64->kind = basic_type_kind; type_float64->val.basic_type = "float64";
    symTYPE *sym_float64 = initSymType(type_category, type_type, type_float64);
    putSymbol(sym, "float64", sym_float64, node->lineno);
    TYPE *type_rune = malloc(sizeof(TYPE)); type_rune->kind = basic_type_kind; type_rune->val.basic_type = "rune";
    symTYPE *sym_rune = initSymType(type_category, type_type, type_rune);
    putSymbol(sym, "rune", sym_rune, node->lineno);
    TYPE *type_string = malloc(sizeof(TYPE)); type_string->kind = basic_type_kind; type_string->val.basic_type = "string";
    symTYPE *sym_string = initSymType(type_category, type_type, type_string);
    putSymbol(sym, "string", sym_string, node->lineno);

    node->symboltable = sym;

    scopeInc();
    symTOPLEVELDECL(node->topleveldecls, sym);
    scopeDec();
    scopeDec();
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
    for (VARDCL *i = node; i; i = i->next) {
        for (IDLIST *j = i->idlist; j; j = j->next) {
            symTYPE *symvardcl = initSymType(variable_category, type_type, i->type);
            putSymbol(sym, j->id, symvardcl, node->lineno);
        }
        symEXPRLIST(i->exprlist, sym);
    }
}

void symTYPEDCL(TYPEDCL *node, SymbolTable *sym) {
    for (TYPEDCL *i = node; i; i = i->next) {
        symTYPE *symtypedcl = initSymType(type_category, type_type, i->type);
        putSymbol(sym, i->identifier, symtypedcl, node->lineno);
    }
}

void symFUNCDCL(FUNCDCL *node, SymbolTable *sym) {
    symTYPE *symfuncdcl = initSymType(function_category, func_signature_type, node->signature);
    putSymbol(sym, node->identifier, symfuncdcl, node->lineno);

    SymbolTable *func = scopeSymbolTable(sym);

    scopeInc();
    symFUNC_SIGNATURE(node->signature, func);
    symBLOCK(node->block, NULL, func);
    scopeDec();

}

void symFUNC_SIGNATURE(FUNC_SIGNATURE *node, SymbolTable *sym) {
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        for (IDLIST *j = i->idlist; j; j = j->next) {
            symTYPE *symparamdcl = initSymType(variable_category, type_type, i->type);
            putSymbol(sym, j->id, symparamdcl, node->lineno);
        }
    }
}

void symBLOCK(BLOCK *node, SymbolTable *sym, SymbolTable *extra) {
    scopeInc();
    if (extra)
        node->symboltable = extra;
    else
        node->symboltable = scopeSymbolTable(sym);

    symSTATEMENTS(node->stmts, node->symboltable);
    scopeDec();
}

void symSTATEMENTS(STATEMENTS *node, SymbolTable *sym) {
    for (STATEMENTS *i = node; i; i = i->next) {
        symSTATEMENT(i->stmt, sym);
    }
}

void symSTATEMENT(STATEMENT *node, SymbolTable *sym) {
    switch(node->kind) {
        case dcl_s:
            symDCL(node->val.dcl, sym);
            break;
        case simple_s:
            symSIMPLE(node->val.simple, sym);
            break;
        case block_s:
            symBLOCK(node->val.block, sym, NULL);
            break;
        case print_stmt_s:
        case println_stmt_s:
            symEXPRLIST(node->val.print, sym);
            break;
        case if_stmt_s:
            /*
            scopeInc();
            SymbolTable *switchif = scopeSymbolTable(sym);
            if (node->val.if_stmt.simple)
                symSIMPLE(node->val.if_stmt.simple, switchif);
            symEXPR(node->val.if_stmt.expr, switchif);
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    symBLOCK(node->val.if_stmt.val.if_block, switchif, NULL);
                    break;
                case else_if:
                    scopeInc();
                    SymbolTable *switchifelse = scopeSymbolTable(switchif);
                    symSTATEMENTS(node->val.if_stmt.val.else_block.stmts, switchifelse);
                    switch (node->val.if_stmt.val.else_block.else_block->kind) {
                        case if_stmt_else:
                            symSTATEMENT(node->val.if_stmt.val.else_block.else_block->val.if_stmt, switchifelse);
                            break;
                        case block_else:
                            symBLOCK(node->val.if_stmt.val.else_block.else_block->val.block, switchifelse, NULL);
                            break;
                    }
                    scopeDec();
                    break;
                scopeDec();
            }
            */
            break;
        case switch_stmt_s:
            scopeInc();
            SymbolTable *switchsym = scopeSymbolTable(sym);
            if (node->val.switch_stmt.condition->simple)
                symSIMPLE(node->val.switch_stmt.condition->simple, switchsym);
            if (node->val.switch_stmt.condition->expr)
                symEXPR(node->val.switch_stmt.condition->expr, switchsym);
            if (node->val.switch_stmt.caselist)
                symSWITCH_CASELIST(node->val.switch_stmt.caselist, switchsym);
                scopeDec();
            break;
        case for_stmt_s:
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    symBLOCK(node->val.for_stmt.block, sym, NULL);
                    break;
                case while_loop:
                    symEXPR(node->val.for_stmt.condition->val.while_expr, sym);
                    symBLOCK(node->val.for_stmt.block, sym, NULL);
                    break;
                case threepart:
                    {
                        scopeInc();
                        SymbolTable *threepart = scopeSymbolTable(sym);
                        if (node->val.for_stmt.condition->val.threepart.init)
                            symSIMPLE(node->val.for_stmt.condition->val.threepart.init, threepart);
                        if (node->val.for_stmt.condition->val.threepart.condition)
                            symEXPR(node->val.for_stmt.condition->val.threepart.condition, threepart);
                        if (node->val.for_stmt.condition->val.threepart.post)
                            symSIMPLE(node->val.for_stmt.condition->val.threepart.post, threepart);
                        symBLOCK(node->val.for_stmt.block, threepart, NULL);
                        scopeDec();
                    }
                    break;
            }
            break;
        case return_stmt_s:
            if (node->val.return_stmt)
                symEXPR(node->val.return_stmt, sym);
            break;
        case break_stmt_s:
        case continue_stmt_s:
            break;
    }

}

void symSWITCH_CASELIST(SWITCH_CASELIST *node, SymbolTable *sym) {
    for (SWITCH_CASELIST *i = node; i; i=i->next) {
        scopeInc();
        SymbolTable *symswitch_case = scopeSymbolTable(sym);
        if (!(i->default_case))
            symEXPRLIST(i->exprlist, symswitch_case);
        if (i->statements)
            symSTATEMENTS(i->statements, symswitch_case);
        scopeDec();
    }
}

void symSIMPLE(SIMPLE *node, SymbolTable *sym) {
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            //symEXPR(node->val.expr, sym);
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
}

void symEXPRLIST(EXPRLIST *node, SymbolTable *sym) {
    for (EXPRLIST *i = node; i; i = i->next)
        symEXPR(i->expr, sym);
}

/*

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


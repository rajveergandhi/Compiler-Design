#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "pretty.h"

extern int g_symbols;

// global indentation variable; it is incremented wherever necessary
int g_symIndent = 0;

// print the indentation as spaces
void symIndent(int indent_level) {
    int indent_val = 4; // one level of indentation is defined as 4 spaces
    for (int i = 0; i < indent_val * indent_level; ++i) {
        printf(" ");
    }
}

// create the hash from a string
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

SYMBOL *putSymbol(SymbolTable *t, char *name, symTYPE *data, int lineno) {
    int i = Hash(name);
    SYMBOL *s;

    // ignore blank identifiers
    if (strcmp(name, "_") == 0)
        return NULL;

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
    if (g_symbols)
        printSymbol(name, data);

    return s;
}

// modify an entry in the symbol table to point to the new TYPE
void addSymbolType(SymbolTable *t, char *name, symTYPE *base) {
    int i = Hash(name);
    if(!t->table[i]){
        return;
    }else{
        SYMBOL *s = t->table[i];
        while (s) {
            if (strcmp(s->name,name)==0) {
                switch(base->symtype){
                    case basic_type:
                        s->data->symtype = basic_type;
                        s->data->val.base = base->val.base;
                        break;
                    case type_type:
                        s->data->symtype = type_type;
                        s->data->val.symtype = base->val.symtype;
                        break;
                    case func_signature_type:
                        s->data->symtype = func_signature_type;
                        s->data->val.symsign = base->val.symsign;
                        break;
                }
                s->data = base;
                //printf("%d"t->table[97]->data)
                return;
            }
            if(s->next)
                s=s->next;
        }
        if (!t->parent) {
            printf("DID NOT ADD\n");
            return;
        }else{
        }
    }
    addSymbolType(t->parent, name, base);
    return;
}

// helper function: add indentation with braces for a new scope
void scopeInc() {
    if (g_symbols) {
        symIndent(g_symIndent);
        printf("{\n");
    }
    g_symIndent++;
}

// helper function: add indentation with braces for a new scope
void scopeDec() {
    g_symIndent--;
    if (g_symbols) {
        symIndent(g_symIndent);
        printf("}\n");
    }
}

// helper function: print the symbol
void printSymbol(char *name, symTYPE *data) {
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
            case basic_type:
                // don't do anything since symbol table doesn't print literals
                break;
        }
}
int p = 0;
// retreive symbol; throw an error and exit if symbol not found
SYMBOL *getSymbol(SymbolTable *sym, char *name, int lineno) {
    int i = Hash(name);
        printf("%s\n\n\n",sym->table[i]->name);
        for (SYMBOL *s = sym->table[i]; s; s = s->next) {
            if (strcmp(s->name,name) == 0){
                printf("W");
                return s;
            }
        }
    if (sym->parent == NULL) {
        fprintf(stderr, "Error: (line %d) \"%s\" is not declared\n", lineno, name);
        exit(1);
    }
    p++;
    printf("%d",p);
    return getSymbol(sym->parent, name, lineno);
}

// return true if "name" is defined in "sym", return false otherwise
bool defSymbol(SymbolTable *sym, char *name) {
    int i = Hash(name);
    for (SYMBOL *s = sym->table[i]; s; s = s->next) {
        if (strcmp(s->name,name) == 0)
            return true;
    }
    if (sym->parent == NULL) {
        return false;
    }
    return defSymbol(sym->parent, name);
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
        case basic_type:
            // don't do anything since symbol table doesn't handle literals
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
        i->symboltable = sym;
        for (IDLIST *j = i->idlist; j; j = j->next) {
            symTYPE *symvardcl = initSymType(variable_category, type_type, i->type);
            putSymbol(sym, j->id, symvardcl, node->lineno);
            if (i->type && i->type->kind == struct_type_kind)
                symSTRUCT_TYPE(node->type->val.struct_type);
        }
        symEXPRLIST(i->exprlist, sym);
    }
}

void symTYPEDCL(TYPEDCL *node, SymbolTable *sym) {
    for (TYPEDCL *i = node; i; i = i->next) {
        i->symboltable = sym;
        symTYPE *symtypedcl = initSymType(type_category, type_type, i->type);
        putSymbol(sym, i->identifier, symtypedcl, node->lineno);
    }
}

void symSTRUCT_TYPE(STRUCT_TYPE *node) {
    SymbolTable *symstruct = initSymbolTable();
    node->symboltable = symstruct;
    for (STRUCT_TYPE *i = node; i; i = i->next) {
        for (IDLIST *j = i->idlist; j; j = j->next) {
            symTYPE *symvardcl = initSymType(variable_category, type_type, i->type);
            putSymbol(symstruct, j->id, symvardcl, node->lineno);
        }
    }
}

void symFUNCDCL(FUNCDCL *node, SymbolTable *sym) {
    node->symboltable = sym;
    symTYPE *symfuncdcl = initSymType(function_category, func_signature_type, node->signature);
    putSymbol(sym, node->identifier, symfuncdcl, node->lineno);

    SymbolTable *func = scopeSymbolTable(sym);

    scopeInc();
    symFUNC_SIGNATURE(node->signature, func);
    symBLOCK(node->block, NULL, func);
    scopeDec();

}

void symFUNC_SIGNATURE(FUNC_SIGNATURE *node, SymbolTable *sym) {
    node->symboltable = sym;
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        for (IDLIST *j = i->idlist; j; j = j->next) {
            symTYPE *symparamdcl = initSymType(variable_category, type_type, i->type);
            putSymbol(sym, j->id, symparamdcl, node->lineno);
        }
    }
}

void symBLOCK(BLOCK *node, SymbolTable *sym, SymbolTable *extra) {
    if (extra) {
        node->symboltable = extra;
        symSTATEMENTS(node->stmts, node->symboltable);
    }
    else {
        scopeInc();
        node->symboltable = scopeSymbolTable(sym);
        symSTATEMENTS(node->stmts, node->symboltable);
        scopeDec();
    }
}

void symSTATEMENTS(STATEMENTS *node, SymbolTable *sym) {
    for (STATEMENTS *i = node; i; i = i->next) {
        symSTATEMENT(i->stmt, sym);
    }
}

void symSTATEMENT(STATEMENT *node, SymbolTable *sym) {
    node->symboltable = sym;
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
            scopeInc();
            SymbolTable *switchif = scopeSymbolTable(sym);
            node->val.if_stmt.symboltable = switchif;
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
                    node->val.if_stmt.val.else_block.symboltable = switchifelse;
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
            }
            scopeDec();
            break;
        case switch_stmt_s:
            scopeInc();
            SymbolTable *switchsym = scopeSymbolTable(sym);
            node->val.switch_stmt.symboltable = switchsym;
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
                        node->val.for_stmt.condition->val.threepart.symboltable = threepart;
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
        i->symboltable = symswitch_case;
        if (!(i->default_case))
            symEXPRLIST(i->exprlist, symswitch_case);
        if (i->statements)
            symSTATEMENTS(i->statements, symswitch_case);
        scopeDec();
    }
}

void symSIMPLE(SIMPLE *node, SymbolTable *sym) {
    node->symboltable = sym;
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
        case increment_kind:
        case decrement_kind:
            symEXPR(node->val.expr, sym);
            break;
        case assignment_kind:
            symEXPRLIST(node->val.assignment.LHS_expr_list, sym);
            symEXPRLIST(node->val.assignment.RHS_expr_list, sym);
            break;
        case shortDcl_kind:
            // all the expressions on the RHS must be in scope
            symEXPRLIST(node->val.shortDcl.RHS_expr_list, sym);

            // loop through LHS and add undeclared variables to the symbol table
            bool atLeastOneVarNotDeclared = false;
            for (EXPRLIST *i = node->val.shortDcl.LHS_expr_list; i; i = i->next) {
                if (!(defSymbol(sym, i->expr->val.other_expr->val.identifier))) {
                    atLeastOneVarNotDeclared  = true;

                    // add to the symbol table
                    symTYPE *symshortvardcl = initSymType(variable_category, type_type, NULL);
                    putSymbol(sym, i->expr->val.other_expr->val.identifier, symshortvardcl, node->lineno);
                }
            }

            // at least one variable on the LHS should not be declared in the current scope
            if (!(atLeastOneVarNotDeclared)) {
                fprintf(stderr, "Error: (line %d) short declaration: there must be at least one variable on the LHS not declared in the current scope\n", node->lineno);
                exit(1);
            }
            break;
    }
}

void symEXPRLIST(EXPRLIST *node, SymbolTable *sym) {
    for (EXPRLIST *i = node; i; i = i->next)
        symEXPR(i->expr, sym);
}

void symEXPR(EXPR *node, SymbolTable *sym) {
    node->symboltable = sym;
    switch (node->kind) {
        case expressionKindPlus:
        case expressionKindMinus:
        case expressionKindMult:
        case expressionKindDiv:
        case expressionKindMod:
        case expressionKindLT:
        case expressionKindLT_EQ:
        case expressionKindGT:
        case expressionKindGT_EQ:
        case expressionKindEQ_EQ:
        case expressionKindNotEquals:
        case expressionKindShift_Right:
        case expressionKindShift_Left:
        case expressionKindAnd:
        case expressionKindAMP_XOR:
        case expressionKindOr:
        case expressionKindXor:
        case expressionKindLogicalAnd:
        case expressionKindLogicalOr:
            symEXPR(node->val.binary.lhs, sym);
            symEXPR(node->val.binary.rhs, sym);
            break;
        case expressionKindPlusUnary:
        case expressionKindMinusUnary:
        case expressionKindNotUnary:
        case expressionKindXorUnary:
            symEXPR(node->val.expr_unary, sym);
            break;
        case append_expr:
            getSymbol(sym, node->val.append_expr.identifier, node->lineno);
            symEXPR(node->val.append_expr.expr, sym);
            break;
        case intval:
        case floatval:
        case stringval:
        case rawstringval:
        case runeval:
            break;
        case other_expr_kind:
            symOTHER_EXPR(node->val.other_expr, sym);
            break;
    }
}

void symOTHER_EXPR(OTHER_EXPR *node, SymbolTable *sym) {
    node->symboltable = sym;
    switch (node->kind) {
        case identifier_kind:
            getSymbol(sym, node->val.identifier, node->lineno);
            break;
        case paren_kind:
            symEXPR(node->val.expr, sym);
            break;
        case func_call_kind:
            symOTHER_EXPR(node->val.func_call.id, sym);
            symEXPRLIST(node->val.func_call.args, sym);
            break;
        case index_kind:
            symOTHER_EXPR(node->val.index.expr, sym);
            symEXPR(node->val.index.index, sym);
            break;
        case struct_access_kind:
            {
                symOTHER_EXPR(node->val.struct_access.expr, sym);

                // assuming "other expression" is one identifier whose type is struct; no other cases supported yet
                if (node->val.struct_access.expr->kind == identifier_kind) {
                    SYMBOL *s = getSymbol(sym, node->val.struct_access.expr->val.identifier, node->lineno);
                    if ((s->data->val.symtype->kind == struct_type_kind) && (s->data->val.symtype->val.struct_type))
                        getSymbol(s->data->val.symtype->val.struct_type->symboltable, node->val.struct_access.identifier, node->lineno);
                }
            }
            break;
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "type.h"

// helper functions; either return true or print error and exit
bool isBool(symTYPE *base, int lineno) {
    if ((base->symtype == basic_type) && (base->val.base == k_bool))
        return true;
    else {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
}
bool isInteger(symTYPE *base, int lineno) {
    if ((base->symtype == basic_type) && ((base->val.base == k_int) || (base->val.base == k_rune)))
        return true;
    else {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
}
bool isNumeric(symTYPE *base, int lineno) {
    if ((base->symtype == basic_type) && (base->val.base == k_float64))
        return true;
    else
        return isInteger(base, lineno);
}
bool isNumericOrString(symTYPE *base, int lineno) {
    if ((base->symtype == basic_type) && (base->val.base == k_string))
        return true;
    else
        return isNumeric(base, lineno);
}
bool hasSameType(symTYPE *base1, symTYPE *base2, int lineno) {
    if ((base1->symtype == basic_type) && (base2->symtype == basic_type) && (base1->val.base == base2->val.base)) {
        return true;
    }
    else if ((base1->symtype == type_type) && (base2->symtype == basic_type)) {
        if (base1->val.symtype->kind == basic_type_kind) {
            if (((strcmp(base1->val.symtype->val.basic_type, "int")==0) && base2->val.base == k_int) ||
                ((strcmp(base1->val.symtype->val.basic_type, "string")==0) && base2->val.base == k_string) ||
                ((strcmp(base1->val.symtype->val.basic_type, "float64")==0) && base2->val.base == k_float64) ||
                ((strcmp(base1->val.symtype->val.basic_type, "rune")==0) && base2->val.base == k_rune) ||
                ((strcmp(base1->val.symtype->val.basic_type, "bool")==0) && base2->val.base == k_bool))
                return true;
        }
    }
    fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
    exit(1);
}

/*
TYPE *type_true, *type_false, *type_int, *type_float64, *type_rune, *type_bool, *type_string;
void initTypes() {
    SYMBOL *s;
    *type_true = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "bool";
    *type_false = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "bool";
    *type_int = malloc(sizeof(TYPE)); type_true->kind = basic_type_kind; type_true->val.basic_type = "int";
    *type_float64 = malloc(sizeof(TYPE)); type_float64->kind = basic_type_kind; type_float64->val.basic_type = "float64";
    *type_rune = malloc(sizeof(TYPE)); type_rune->kind = basic_type_kind; type_rune->val.basic_type = "rune";
    *type_bool = malloc(sizeof(TYPE)); type_bool->kind = basic_type_kind; type_bool->val.basic_type = "bool";
    *type_string = malloc(sizeof(TYPE)); type_string->kind = basic_type_kind; type_string->val.basic_type = "string";
    // s = getSymbol(classlib,"String");
    // if (s==NULL) {
    //     reportGlobalError("class String not found");
    //     noErrors();
    // }
}
int equalTYPE(TYPE *s, TYPE *t) {
    if (s->val.basic_type!=t->val.basic_type) return 0;
    // if (s->kind==refK) {
    //     return strcmp(s->name,t->name)==0;
    // }
    return 1;
}
int integerTYPE(TYPE *t) {
    return t->val.basic_type=="int";
}
int assignTYPE(TYPE *s, TYPE *t) {
    if (s->val.basic_type!=t->val.basic_type) return 0;
    return 1;
}

int checkBOOL(TYPE *t, int lineno) {
    if (t->val.basic_type!="bool") {
        reportError("boolean type expected",lineno);
        return 0;
    }
    return 1;
}
int checkRUNE(TYPE *t, int lineno) {
    if (t->val.basic_type!="rune") {
        reportError("rune type expected",lineno);
        return 0;
    }
    return 1;
}
int checkSTRING(TYPE *t, int lineno) {
    if (t->val.basic_type!="string") {
        reportError("string type expected",lineno);
        return 0;
    }
    return 1;
}
int checkINT(TYPE *t, int lineno) {
    if (t->val.basic_type!="int") {
        reportError("int type expected",lineno);
        return 0;
    }
    return 1;
}
// int equalFORMAL(FORMAL *f, FORMAL *g) {
//     if (f==NULL || g==NULL) return f==NULL && g==NULL;
//     return equalTYPE(f->type,g->type) && equalFORMAL(f->next,g->next);
// }
*/

void typePROGRAM(PROGRAM *node) {
    typeTOPLEVELDECL(node->topleveldecls);
}

void typeTOPLEVELDECL(TOPLEVELDECL *node) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        switch (i->kind) {
            case dcl_toplevel:
                typeDCL(i->val.dcl);
                break;
            case func_dcl_toplevel:
                typeFUNCDCL(i->val.funcdcl);
                break;
        }
    }
}

void typeDCL(DCL *node) {
    switch (node->kind) {
        case var:
            typeVARDCL(node->val.vardcl);
            break;
        case type:
            typeTYPEDCL(node->val.typedcl);
            break;
    }
}

void typeVARDCL(VARDCL *node) {
    for (VARDCL *i = node; i; i = i->next) {
        // if exprlist is not provided then there is nothing to typecheck
        if (!(node->exprlist))
            continue;
        else
            typeEXPRLIST(i->exprlist);

        // loop through each variable and its corresponding expr; they should be the same length
        IDLIST *j = i->idlist;
        EXPRLIST *k= i->exprlist;
        while (j) { 
            if (i->type) {
                // compare the given type with expr type
                // getbase of expr
                // do the comparison
            }
            else {
                // if type not provided then use the expression's type
                addSymbolType(i->symboltable, j->id, k->expr->base->val.symtype);
            }

            j = j->next;
            k = k->next;
        }
    }
}

void typeTYPEDCL(TYPEDCL *node) {
}
void typeFUNCDCL(FUNCDCL *node) {
}

void typeEXPRLIST(EXPRLIST *node) {
    for (EXPRLIST *i = node; i; i = i->next)
        typeEXPR(i->expr);
}

void typeBLOCK(BLOCK *node) {
    for (STATEMENTS *i = node->stmts; i; i = i->next)
        typeSTATEMENT(i->stmt);
}

void typeSTATEMENT(STATEMENT *node) {
    switch(node->kind) {
        case dcl_s:
            typeDCL(node->val.dcl);
            break;
        case simple_s:
            typeSIMPLE(node->val.simple);
            break;
        case return_stmt_s:
            // a return statement with no expression is well-typed if enclosing fn has no return type.
            // with expr is well-typed if its expression is well-typed and type of expr = return type of function
            // also we should type check all statements after a return.
            if (node->val.return_stmt) {
                typeEXPR(node->val.return_stmt);
            }
            break;
        case break_stmt_s:
        case continue_stmt_s:
            // trivially well-typed.
            break;
        case block_s:
            // check if its statements type check.
            typeBLOCK(node->val.block);
            break;
        case if_stmt_s:
            // if init; expr {} else {}
            // init type-checks, expr is well-typed and resolves to type bool
            // statements in first and second block type-check.
            if (node->val.if_stmt.simple) {
                typeSIMPLE(node->val.if_stmt.simple);
            }
            typeEXPR(node->val.if_stmt.expr);
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    typeBLOCK(node->val.if_stmt.val.if_block);
                    break;
                case else_if:
                    typeSTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    typeELSE_BLOCK(node->val.if_stmt.val.else_block.else_block);
                    break;
            }
            break;
        case switch_stmt_s:
            // switch init; expr { case e1: default: }
            // init type-checks, expr is well-typed.
            // e1,e2.. are well-typed and have same type as expr
            // statements under cases should type-check.
            // if no expr, e1, e2... should have type bool.
            if (node->val.switch_stmt.condition->simple) {
                typeSIMPLE(node->val.switch_stmt.condition->simple);
            }
            if (node->val.switch_stmt.condition->expr) {
                typeEXPR(node->val.switch_stmt.condition->expr);
            }
            if (node->val.switch_stmt.caselist)
                typeSWITCH_CASELIST(node->val.switch_stmt.caselist);
            break;
        case for_stmt_s:
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    // type checks if its body type-checks.
                    break;
                case while_loop:
                    // its expression should be well-typed and resolved to type bool. statements should type-check.
                    typeEXPR(node->val.for_stmt.condition->val.while_expr);
                    break;
                case threepart:
                    // for init; expr; post {}
                    // init type-checks, expr is well-typed and resolves to type bool.
                    // post type checks, statements type-check
                    if (node->val.for_stmt.condition->val.threepart.init) {
                        typeSIMPLE(node->val.for_stmt.condition->val.threepart.init);
                    }
                    if (node->val.for_stmt.condition->val.threepart.condition) {
                        typeEXPR(node->val.for_stmt.condition->val.threepart.condition);
                    }
                    if (node->val.for_stmt.condition->val.threepart.post)
                        typeSIMPLE(node->val.for_stmt.condition->val.threepart.post);
                    break;
            }
            typeBLOCK(node->val.for_stmt.block);
            break;
        case print_stmt_s:
        case println_stmt_s:
            // check if its expressions are well-typed and resolve to a base type.
            typeEXPRLIST(node->val.print);
            for (EXPRLIST *i = node->val.print; i; i = i->next)
                if (!((i->expr->base->symtype == basic_type) || (i->expr->base->symtype == type_type && i->expr->base->val.symtype->kind == basic_type_kind)))
                    fprintf(stderr, "Error: (line %d) incorrect type used\n", node->lineno);
    }
}

/*
void typeTYPEDCL(TYPEDCL *node, SymbolTable *sym) {
    // type T1 T2. if T1 is already declared, new mapping will shadow previous
    for (TYPEDCL *i = node; i; i = i->next)
        //
}

void typeFUNCDCL(FUNCDCL *node) {
    // checks for special function (init and main). should not have parameters or return type.
    // if function being declared twice, raise error (does not hold for init)
    switch(node->identifier) {
        case "init":
            typeInitMainFUNC_SIGNATURE(node->signature);
            typeInitMainBLOCK(node->block);
            break;
        case "main":
            typeInitMainFUNC_SIGNATURE(node->signature);
            typeInitMainBLOCK(node->block);
            break;
        default:
            typeBLOCK(node->block);
            break;
    }

}

void typeInitMainFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    if(node->params!=NULL) {
        //error. init and main should not have parameters
    }
}

void typeInitMainBLOCK(BLOCK *node) {
    typeInitMainSTATEMENTS(node->stmts);
}

void typeInitMainSTATEMENTS(STATEMENTS *node) {
    int checkRETURN = 0;
    for (STATEMENTS *i = node; i; i = i->next) {
        if (i->stmt->kind == return_stmt_s)
            checkRETURN = 1;
    }
    if (!checkRETURN) {
        // error. init and main should not have a return type
    }
}

void typeBLOCK(BLOCK *node) {
    typeSTATEMENTS(node->stmts);
}

void typeSTATEMENTS(STATEMENTS *node) {
    // make sure all statements are well-typed. A statement does not have a type.
    for (STATEMENTS *i = node; i; i = i->next) {
        typeSTATEMENT(i->stmt);
    }
}


void typeSWITCH_CASELIST(SWITCH_CASELIST *node) {
    for (SWITCH_CASELIST *i = node; i; i=i->next) {
        if (i->default_case) {
        }
        else {
            typeEXPRLIST(i->exprlist);
        }
        if (i->statements)
            typeSTATEMENTS(i->statements);
    }
}

void typeELSE_BLOCK(ELSE_BLOCK *node) {
    switch (node->kind) {
        case if_stmt_else:
            typeSTATEMENT(node->val.if_stmt);
            break;
        case block_else:
            typeBLOCK(node->val.block);
            break;
    }
}

void typeSIMPLE(SIMPLE *node) {
    switch (node->kind) {
        case empty_stmt_kind:
            // empty statement is trivially well-typed.
            break;
        case expr_kind:
            typeEXPR(node->val.expr);
            break;
        case increment_kind:
            // type-checks if its expr is well-typed and resolves to a numeric base type (init float rune)
            typeEXPR(node->val.expr);
            break;
        case decrement_kind:
            // type-checks if its expr is well-typed and resolves to a numeric base type (init float rune)
            typeEXPR(node->val.expr);
            break;
        case assignment_kind:
            // LHS AND RHS well-typed, for every pair of lvalue/expression, types are same.
            // expressions on LHS and RHS well typed, operator op accepts 2 arguments of types v and expr. returns
            // a value of type typeof(v). v op= expr
            typeEXPRLIST(node->val.assignment.LHS_expr_list);
            typeEXPRLIST(node->val.assignment.RHS_expr_list);
            break;
        case shortDcl_kind:
            // all expressions on RHS & LHS well-typed, RHS not delcared in current scope. variables already
            // delcared in current scope are assigned expressions of same type. x1 = e1, if x1 -> T1 => type(e1) = T1.
            typeEXPRLIST(node->val.shortDcl.LHS_expr_list);
            typeEXPRLIST(node->val.shortDcl.RHS_expr_list);
            break;
    }
}

void typeTYPE(TYPE *node) {
    switch (node->kind) {
        case basic_type_kind:
            break;
        case slice_type_kind:
            typeTYPE(node->val.slice_type);
            break;
        case array_type_kind:
            typeTYPE(node->val.array_type.type);
            break;
        case struct_type_kind:
            for (STRUCT_TYPE *i = node->val.struct_type; i; i = i->next) {
                typeIDLIST(i->idlist);
                typeTYPE(i->type);
            }
            break;
    }
}

*/

/* make sure expression's children are well typed, and give a type to a expression itself */
void typeEXPR(EXPR *node) {
    switch (node->kind) {
        case expressionKindPlus:
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            hasSameType(node->val.binary.lhs->base, node->val.binary.rhs->base, node->lineno);
            if ((isNumericOrString(node->val.binary.lhs->base, node->lineno)) &&
                (isNumericOrString(node->val.binary.rhs->base, node->lineno)))
                node->base = node->val.binary.lhs->base;
            break;
        case expressionKindMinus:
        case expressionKindMult:
        case expressionKindDiv:
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            hasSameType(node->val.binary.lhs->base, node->val.binary.rhs->base, node->lineno);
            if ((isNumeric(node->val.binary.lhs->base, node->lineno)) &&
                (isNumeric(node->val.binary.rhs->base, node->lineno)))
                node->base = node->val.binary.lhs->base;
            break;
        case expressionKindMod:
        case expressionKindOr:
        case expressionKindAnd:
        case expressionKindShift_Left:
        case expressionKindShift_Right:
        case expressionKindAMP_XOR:
        case expressionKindXor:
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            hasSameType(node->val.binary.lhs->base, node->val.binary.rhs->base, node->lineno);
            if ((isInteger(node->val.binary.lhs->base, node->lineno)) &&
                (isInteger(node->val.binary.rhs->base, node->lineno)))
                node->base = node->val.binary.lhs->base;
            break;
        case expressionKindLogicalAnd:
        case expressionKindLogicalOr:
            // values are not actual the correct ones. implement this properly in codegen phase
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            if ((isBool(node->val.binary.lhs->base, node->lineno)) &&
                (isBool(node->val.binary.rhs->base, node->lineno)))
                node->base = node->val.binary.lhs->base;
            break;
        case expressionKindLT:
        case expressionKindLT_EQ:
        case expressionKindGT:
        case expressionKindGT_EQ:
        case expressionKindEQ_EQ:
        case expressionKindNotEquals:
            // values are not actual the correct ones. implement this properly in codegen phase
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            {
                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = k_bool;
                node->base = symtype;
            }
            break;
        case expressionKindPlusUnary:
        case expressionKindMinusUnary:
            typeEXPR(node->val.expr_unary);
            if (isNumeric(node->val.expr_unary->base, node->lineno))
                node->base = node->val.expr_unary->base;
            break;
        case expressionKindNotUnary:
            typeEXPR(node->val.expr_unary);
            if (isBool(node->val.expr_unary->base, node->lineno))
                node->base = node->val.expr_unary->base;
            break;
        case expressionKindXorUnary:
            typeEXPR(node->val.expr_unary);
            if (isInteger(node->val.expr_unary->base, node->lineno))
                node->base = node->val.expr_unary->base;
            break;
        case append_expr:
            {
                SYMBOL *s = getSymbol(node->symboltable, node->val.append_expr.identifier, node->lineno);

                hasSameType(s->data, node->val.append_expr.expr->base, node->lineno);

                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = type_type;
                symtype->val.symtype = s->data->val.symtype;
                node->base = symtype;
            }
            break;
        case intval:
            {
                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = k_int;
                node->base = symtype;
            }
            break;
        case floatval:
            {
                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = k_float64;
                node->base = symtype;
            }
            break;
        case stringval:
        case rawstringval:
            {
                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = k_string;
                node->base = symtype;
            }
            break;
        case runeval:
            {
                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = k_rune;
                node->base = symtype;
            }
            break;
        case other_expr_kind:
            typeOTHER_EXPR(node->val.other_expr);
            break;
    }
}

void typeOTHER_EXPR(OTHER_EXPR *node) {
    switch (node->kind) {
        case identifier_kind:
            {
                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                node->base = symtype;

                SYMBOL* s =  getSymbol(node->symboltable, node->val.identifier, node->lineno);
                if (strcmp(s->data->val.symtype->val.basic_type, "int") == 0)
                    symtype->val.base = k_int;
                else if (strcmp(s->data->val.symtype->val.basic_type, "float64") == 0)
                    symtype->val.base = k_float64;
                else if (strcmp(s->data->val.symtype->val.basic_type, "string") == 0)
                    symtype->val.base = k_string;
                else if (strcmp(s->data->val.symtype->val.basic_type, "rune") == 0)
                    symtype->val.base = k_rune;
            }
            break;
        case paren_kind:
            typeEXPR(node->val.expr);
            break;
        case func_call_kind:
            /*
            if ((node->val.func_call.id->kind == identifier_kind) && (strcmp(node->val.func_call.id->val.identifier, "init") == 0))
                fprintf(stderr, "Error: (line %d) function \"init\" may not be called\n", node->lineno);
            //typeOTHER_EXPR(node->val.func_call.id);
            //typeEXPRLIST(node->val.func_call.args);
            */
            break;
        case index_kind:
                /*
            {
                isInteger(node->val.index.index->base, node->lineno);
                SYMBOL *s = getSymbol(node->symboltable, node->val.append_expr.identifier, node->lineno);

                hasSameType(s->data, node->val.append_expr.expr->base, node->lineno);

                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = type_type;
                symtype->val.symtype = s->data;
                node->base = symtype;
            }
                */
            // expr is well-typed and resolved to []T
            // index is well-typed and resolves to int
            // result of indexing expression is T
            // out of bounds array check done at runtime.
            //typeOTHER_EXPR(node->val.index.expr);
            typeEXPR(node->val.index.index);
            if (isInteger(node->val.index.index->base, node->lineno))
               // node->base = node->val.expr_unary->base
            break;
        case struct_access_kind:
            // selecting a field in a struct. expr is well-typed and has type S. S should resolve to a
            // struct type that has a field named id.
            //typeOTHER_EXPR(node->val.struct_access.expr);
            break;
    }
}

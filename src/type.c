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
bool isSliceOrArray(symTYPE *base, int lineno) {
    if ((base->symtype == type_type) && ((base->val.symtype->kind == slice_type_kind) || (base->val.symtype->kind == array_type_kind)))
        return true;
    else {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
}
bool isStruct(symTYPE *base, int lineno) {
    if ((base->symtype == type_type) && (base->val.symtype->kind == struct_type_kind))
        return true;
    else {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
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
        else if (base1->val.symtype->kind == slice_type_kind) {
            if (((strcmp(base1->val.symtype->val.slice_type->val.basic_type, "int")==0) && base2->val.base == k_int) ||
                ((strcmp(base1->val.symtype->val.slice_type->val.basic_type, "string")==0) && base2->val.base == k_string) ||
                ((strcmp(base1->val.symtype->val.slice_type->val.basic_type, "float64")==0) && base2->val.base == k_float64) ||
                ((strcmp(base1->val.symtype->val.slice_type->val.basic_type, "rune")==0) && base2->val.base == k_rune) ||
                ((strcmp(base1->val.symtype->val.slice_type->val.basic_type, "bool")==0) && base2->val.base == k_bool))
                return true;
        }
        else if (base1->val.symtype->kind == array_type_kind) {
            if (((strcmp(base1->val.symtype->val.array_type.type->val.basic_type, "int")==0) && base2->val.base == k_int) ||
                ((strcmp(base1->val.symtype->val.array_type.type->val.basic_type, "string")==0) && base2->val.base == k_string) ||
                ((strcmp(base1->val.symtype->val.array_type.type->val.basic_type, "float64")==0) && base2->val.base == k_float64) ||
                ((strcmp(base1->val.symtype->val.array_type.type->val.basic_type, "rune")==0) && base2->val.base == k_rune) ||
                ((strcmp(base1->val.symtype->val.array_type.type->val.basic_type, "bool")==0) && base2->val.base == k_bool))
                return true;
        }
    }
    fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
    exit(1);
}

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
        if (!(i->exprlist))
            continue;
        else
            typeEXPRLIST(i->exprlist);

        // loop through each variable and its corresponding expr; they should be the same length
        IDLIST *j = i->idlist;
        EXPRLIST *k= i->exprlist;
        while (j) {
            typeEXPR(k->expr);
            if (i->type) {
                SYMBOL *s = getSymbol(i->symboltable, j->id, i->lineno);
                hasSameType(s->data, k->expr->base, i->lineno);
            }
            else {
                // if type not provided then use the expression's type
                addSymbolType(i->symboltable, j->id, k->expr->base);
            }
            j = j->next;
            k = k->next;
        }
    }
}

void typeTYPEDCL(TYPEDCL *node) {
}

void typeFUNCDCL(FUNCDCL *node) {
    typeBLOCK(node->block);
}

void typeEXPRLIST(EXPRLIST *node) {
    for (EXPRLIST *i = node; i; i = i->next)
        typeEXPR(i->expr);
}

void typeBLOCK(BLOCK *node) {
    typeSTATEMENTS(node->stmts);
}

void typeSTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next)
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
            /*
            if (node->val.return_stmt != NULL) {
                typeEXPR(node->val.return_stmt);
            }
            if ( "check if return is of type void" && node->val.return_stmt!=NULL) {
                fprintf(stderr, "Error: (line %d) return value not allowed\n", node->lineno);
            }
            if ( "check if return is not of type void" && node->val.return_stmt==NULL) {
                fprintf(stderr, "Error: (line %d) return value expected\n", node->lineno);
            }
            if ( "check if return is not of type void" && node->val.return_stmt!=NULL) {
                if (!hasSameType(node->val.return_stmt->base)) {
                    fprintf(stderr, "Error: (line %d) illegal type of expression\n", node->lineno);
               }
            }
            */
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
            typeSIMPLE(node->val.if_stmt.simple);
            /*
            // if init; expr {} else {}
            // init type-checks, expr is well-typed and resolves to type bool
            // statements in first and second block type-check.
            if (node->val.if_stmt.simple) {
                typeSIMPLE(node->val.if_stmt.simple);
            }
            typeEXPR(node->val.if_stmt.expr);
            if (!isBool(node->val.if_stmt.expr->base, node->lineno))
                fprintf(stderr, "Error: (line %d) expression does not resolve to type bool\n", node->lineno);
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    typeBLOCK(node->val.if_stmt.val.if_block);
                    break;
                case else_if:
                    typeSTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    typeELSE_BLOCK(node->val.if_stmt.val.else_block.else_block);
                    break;
            }
            */
            break;
        case switch_stmt_s:
        {
            /*
            // switch init; expr { case e1: default: }
            // init type-checks, expr is well-typed.
            // e1,e2.. are well-typed and have same type as expr
            // statements under cases should type-check.
            // if no expr, e1, e2... should have type bool.
            symTYPE *symtype = malloc(sizeof(symTYPE));
            if (node->val.switch_stmt.condition->simple) {
                typeSIMPLE(node->val.switch_stmt.condition->simple);
            }
            if (node->val.switch_stmt.condition->expr) {
                typeEXPR(node->val.switch_stmt.condition->expr);
                symtype = node->val.if_stmt.expr->base;
            }
            else {
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = k_bool;
                symtype->val.symtype->val.basic_type = "bool";
            }
            if (node->val.switch_stmt.caselist)
                // compare case list with node->base
                typeSWITCH_CASELIST(node->val.switch_stmt.caselist, symtype);
                */
        }
            break;
        case for_stmt_s:
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    break;
                case while_loop:
                    typeEXPR(node->val.for_stmt.condition->val.while_expr);
                    isBool(node->val.for_stmt.condition->val.while_expr->base, node->lineno);
                    break;
                case threepart:
                    if (node->val.for_stmt.condition->val.threepart.init)
                        typeSIMPLE(node->val.for_stmt.condition->val.threepart.init);
                    if (node->val.for_stmt.condition->val.threepart.condition)
                        typeEXPR(node->val.for_stmt.condition->val.threepart.condition);
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

void typeSWITCH_CASELIST(SWITCH_CASELIST *node, symTYPE *symtype) {
    // switch init; expr { case e1: default: }
    // init type-checks, expr is well-typed.
    // e1,e2.. are well-typed and have same type as expr
    // statements under cases should type-check.
    // if no expr, e1, e2... should have type bool.
    /*
    for (SWITCH_CASELIST *i = node; i; i=i->next) {
        if (i->default_case) {
        }
        else {
            // THIS NEEDS TO BE EXPR NOT EXPRLIST?? HOW DO WE GET CASE EXPR BASE TO COMPARE WITH SWITCH EXPR BASE
            // can we pass symtype into typeEXPRLIST(i->exprlist); and do the check there if symtype!=NULL?
            typeEXPRLIST(i->exprlist);
            hasSameType(i->exprlist->base, symtype, node->lineno);
        }
        if (i->statements)
            typeSTATEMENTS(i->statements);
    }
    */
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
                typeEXPR(node->val.append_expr.expr);
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
            node->base = node->val.other_expr->base;
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

                SYMBOL* s = getSymbol(node->symboltable, node->val.identifier, node->lineno);
                if (s->data->val.symtype) {
                    //printf("%d\n", s->data->val.symtype->lineno);
                    if (strcmp(s->data->val.symtype->val.basic_type, "int") == 0)
                        symtype->val.base = k_int;
                    else if (strcmp(s->data->val.symtype->val.basic_type, "float64") == 0)
                        symtype->val.base = k_float64;
                    else if (strcmp(s->data->val.symtype->val.basic_type, "string") == 0)
                        symtype->val.base = k_string;
                    else if (strcmp(s->data->val.symtype->val.basic_type, "rune") == 0)
                        symtype->val.base = k_rune;
                }
            }
            break;
        case paren_kind:
            typeEXPR(node->val.expr);
            node->base = node->val.expr->base;
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
            {
                typeEXPR(node->val.index.index);
                isInteger(node->val.index.index->base, node->lineno);

                SYMBOL *s = getSymbol(node->symboltable, node->val.index.expr->val.identifier, node->lineno);
                isSliceOrArray(s->data, node->lineno);

                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = type_type;
                symtype->val.symtype = s->data->val.symtype;
                node->base = symtype;
            }
            break;
        case struct_access_kind:
            {
                SYMBOL *s = getSymbol(node->symboltable, node->val.struct_access.expr->val.identifier, node->lineno);
                isStruct(s->data, node->lineno);
                SYMBOL *val = getSymbol(s->data->val.symtype->val.struct_type->symboltable, node->val.struct_access.identifier, node->lineno);

                symTYPE *symtype = malloc(sizeof(symTYPE));
                symtype->category = constant_category;
                symtype->symtype = basic_type;
                symtype->val.base = val->data->val.base;
                node->base = symtype;
            }
            break;
    }
}

void typeSIMPLE(SIMPLE *node) {
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            typeEXPR(node->val.expr);
        case increment_kind:
        case decrement_kind:
            typeEXPR(node->val.expr);
            isNumeric(node->val.expr->base, node->lineno);
            break;
        case assignment_kind:
            {
                typeEXPRLIST(node->val.assignment.LHS_expr_list);
                typeEXPRLIST(node->val.assignment.RHS_expr_list);

                // loop through each variable and its corresponding expr; they should be the same length
                EXPRLIST *j = node->val.assignment.LHS_expr_list;
                EXPRLIST *k = node->val.assignment.RHS_expr_list;
                while (j) {
                    SYMBOL *s = getSymbol(j->expr->symboltable, j->expr->val.other_expr->val.identifier, j->expr->lineno);
                    if (s->data->val.symtype) {
                        hasSameType(s->data, k->expr->base, j->expr->lineno);
                    }
                    else {
                        // if type not provided then use the expression's type
                        addSymbolType(j->expr->symboltable, j->expr->val.other_expr->val.identifier, k->expr->base);
                    }
                    j = j->next;
                    k = k->next;
                }
            }
            break;
        case shortDcl_kind:
            {
                typeEXPRLIST(node->val.shortDcl.RHS_expr_list);

                // loop through each variable and its corresponding expr; they should be the same length
                EXPRLIST *j = node->val.shortDcl.LHS_expr_list;
                EXPRLIST *k = node->val.shortDcl.RHS_expr_list;
                while (j) {
                    SYMBOL *s = getSymbol(node->symboltable, j->expr->val.other_expr->val.identifier, j->expr->lineno);
                    if ((s->data->val.base) || (s->data->val.symtype) || (s->data->val.symsign)) {
                        hasSameType(s->data, k->expr->base, j->expr->lineno);
                    }
                    else {
                        // if type not provided then use the expression's type
                        addSymbolType(node->symboltable, j->expr->val.other_expr->val.identifier, k->expr->base);
                    }
                    j = j->next;
                    k = k->next;
                }
            }
            break;
    }
}

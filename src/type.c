#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "type.h"

// global variable to track function return type
DataType *func_return_type;

// helper function: resolve the type to a base type, as specified in the specification
DataType *resolveType(DataType *data, SymbolTable *sym, int lineno) {
    switch (data->val.type->kind) {
        case basic_type_kind:
            {
                char *basic_type = data->val.type->val.basic_type;
                if ((strcmp(basic_type, "bool")==0) ||
                    (strcmp(basic_type, "int")==0) ||
                    (strcmp(basic_type, "float64")==0) ||
                    (strcmp(basic_type, "string")==0) ||
                    (strcmp(basic_type, "rune")==0))
                    return data;
                else {
                    SYMBOL *s = getSymbol(sym, basic_type, lineno);
                    return resolveType(s->data, sym, lineno);
                }
            }
            break;
        case slice_type_kind:
        case array_type_kind:
        case struct_type_kind:
            return data;
            break;
    }

    fprintf(stderr, "Error: (line %d) resolveType() function error. This point should not be reached.\n", lineno);
    exit(1);
}

// helper functions: check type and if it doesn't match then provide an error message and exit
void isBool(DataType *data, int lineno) {
    if (!((data->val.type->kind == basic_type_kind) && (strcmp(data->val.type->val.basic_type, "bool")==0))) {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
}
void isInteger(DataType *data, int lineno) {
    if (!((data->val.type->kind == basic_type_kind) && ((strcmp(data->val.type->val.basic_type, "int")==0) || (strcmp(data->val.type->val.basic_type, "rune")==0)))) {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
}
void isNumeric(DataType *data, int lineno) {
    if (!((data->val.type->kind == basic_type_kind) && ((strcmp(data->val.type->val.basic_type, "float64")==0))))
        isInteger(data, lineno);
}
void isNumericOrString(DataType *data, int lineno) {
    if (!((data->val.type->kind == basic_type_kind) && ((strcmp(data->val.type->val.basic_type, "string")==0))))
        isNumeric(data, lineno);
}
void isBaseType(DataType *data, int lineno) {
    if (!((data->val.type->kind == basic_type_kind) && (strcmp(data->val.type->val.basic_type, "bool")==0)))
        isNumericOrString(data, lineno);
}

// helper function: return true if it is type function, else false
bool isFunction(DataType *data) {
    if (data->category == function_category)
        return true;
    return false;
}

// helper function: check if the casting is valid according to the specs; else, throw error and exit
void validCast(DataType *typedata, DataType *exprdata, int lineno) {
    if (typedata->val.type->kind != exprdata->val.type->kind) {
        fprintf(stderr, "Error: (line %d) invalid cast\n", lineno);
        exit(1);
    }
    switch (typedata->val.type->kind) {
        case basic_type_kind:
            {
                // either they have the same underlying type
                char *typedata_type = typedata->val.type->val.basic_type;
                char *exprdata_type = exprdata->val.type->val.basic_type;
                if (strcmp(typedata_type, exprdata_type) == 0) {
                    return;
                }
                // or they must both resolve to numeric types
                if (((strcmp(typedata_type, "float64")==0) || (strcmp(typedata_type, "int")==0) || (strcmp(typedata_type, "rune")==0)) && 
                    ((strcmp(exprdata_type, "float64")==0) || (strcmp(exprdata_type, "int")==0) || (strcmp(exprdata_type, "rune")==0)))
                    return;
                // or type resolves to string and expr resolves to an integer type
                if ((strcmp(typedata_type, "string")==0) && 
                    ((strcmp(exprdata_type, "int")==0) || (strcmp(exprdata_type, "rune")==0)))
                    return;

                fprintf(stderr, "Error: (line %d) invalid cast\n", lineno);
                exit(1);
            }
            break;
        case slice_type_kind:
        case array_type_kind:
        case struct_type_kind:
            // unimplemented
            break;
    }
}

// helper function: if data is not of type slice then throw error, else return the enclosing type as a DataType
DataType *isSlice(DataType *data, int lineno) {
    if (!((data->valKind == type_type) && (data->val.type->kind == slice_type_kind))) {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
    DataType *ret = malloc(sizeof(DataType));
    ret->category = constant_category;
    ret->valKind = type_type;
    ret->val.type = data->val.type->val.slice_type;
    return ret;
}

// helper function: if data is not of type slice or array then throw error, else return the enclosing type as a DataType
DataType *isSliceOrArray(DataType *data, int lineno) {
    if (!((data->valKind == type_type) && ((data->val.type->kind == slice_type_kind) || (data->val.type->kind == array_type_kind)))) {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
    DataType *ret = malloc(sizeof(DataType));
    ret->category = constant_category;
    ret->valKind = type_type;
    switch (data->val.type->kind) {
        case slice_type_kind:
            ret->val.type = data->val.type->val.slice_type;
            break;
        case array_type_kind:
            ret->val.type = data->val.type->val.array_type.type;
            break;
        case basic_type_kind:
        case struct_type_kind:
            break;
    }
    return ret;
}

// helper function: if data not of type struct then throw error and exit 
void isStruct(DataType *data, int lineno) {
    if (!((data->valKind == type_type) && (data->val.type->kind == struct_type_kind))) {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
}

// helper function: if data1 and data2 don't have the same type then provide an error message and exit
void mustHaveSameType(DataType *data1, DataType *data2, int lineno) {
    if (data1->val.type->kind != data2->val.type->kind) {
        fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
        exit(1);
    }
    switch (data1->val.type->kind) {
        case basic_type_kind:
            if (strcmp(data1->val.type->val.basic_type, data2->val.type->val.basic_type) != 0) {
                fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
                exit(1);
            }
            break;
        case slice_type_kind:
            {
                // create two DataTypes and recursively call mustHaveSameType()
                DataType *data_1 = malloc(sizeof(DataType));
                data_1->category = constant_category;
                data_1->valKind = type_type;
                data_1->val.type = data1->val.type->val.slice_type;

                DataType *data_2 = malloc(sizeof(DataType));
                data_2->category = constant_category;
                data_2->valKind = type_type;
                data_2->val.type = data2->val.type->val.slice_type;

                mustHaveSameType(data_1, data_2, lineno);
            }
            break;
        case array_type_kind:
            {
                //array sizes must be equal
                if (data1->val.type->val.array_type.size != data2->val.type->val.array_type.size) {
                    fprintf(stderr, "Error: (line %d) incorrect type used\n", lineno);
                    exit(1);
                }

                // create two DataTypes and recursively call mustHaveSameType()
                DataType *data_1 = malloc(sizeof(DataType));
                data_1->category = constant_category;
                data_1->valKind = type_type;
                data_1->val.type = data1->val.type->val.array_type.type;

                DataType *data_2 = malloc(sizeof(DataType));
                data_2->category = constant_category;
                data_2->valKind = type_type;
                data_2->val.type = data2->val.type->val.array_type.type;

                mustHaveSameType(data_1, data_2, lineno);
            }
            break;
        case struct_type_kind:
            // unimplemented
            break;
    }
}

void handleSpecialFunctions(FUNCDCL *node) {
    // functions named "init" and "main" cannot have parameters or return types
    if ((strcmp(node->identifier, "main")==0) || (strcmp(node->identifier, "init")==0)) {
        if (node->signature->params || node->signature->type) {
            fprintf(stderr, "Error: (line %d) functions \"init\" and \"main\" cannot have paramaters or return type\n", node->signature->lineno);
            exit(1);
        }
    }
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
            // nothing to typecheck with type declarations
            //typeTYPEDCL(node->val.typedcl);
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

        // loop through each variable and its corresponding expr; the lists should be the same length
        IDLIST *j = i->idlist;
        EXPRLIST *k= i->exprlist;
        while (j) {
            // if variable has a declared type then check that expr type is the same
            if (i->type) { 
                // ignore requests for blank identifier in symbol table
                if (strcmp(j->id, "_") != 0) {
                    SYMBOL *s = getSymbol(i->symboltable, j->id, j->lineno);
                    //mustHaveSameType(resolveType(s->data, i->symboltable, j->lineno), k->expr->data, j->lineno);
                    mustHaveSameType(s->data, k->expr->data, j->lineno);
                }
            }
            else {
                // if variable does not have a declared type then just use the expression's type and add to symbol table
                if (!(k->expr->data->val.type)) {
                    fprintf(stderr, "Error: (line %d) RHS has no type\n", j->lineno);
                    exit(1);
                }
                addSymbolType(i->symboltable, j->id, k->expr->data);
            }
            j = j->next;
            k = k->next;
        }
    }
}

void typeFUNCDCL(FUNCDCL *node) {
    handleSpecialFunctions(node);
    func_return_type = malloc(sizeof(DataType));
    func_return_type->valKind = type_type;
    func_return_type->val.type = node->signature->type;
    typeBLOCK(node->block);
}

void typeEXPRLIST(EXPRLIST *node) {
    for (EXPRLIST *i = node; i; i = i->next)
        typeEXPR(i->expr);
}

void typeBLOCK(BLOCK *node) {
    if(node->stmts)
        typeSTATEMENTS(node->stmts);
}

void typeSTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next){
        typeSTATEMENT(i->stmt);
    }
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
            if(node->val.return_stmt) {
                typeEXPR(node->val.return_stmt);
                mustHaveSameType(func_return_type, node->val.return_stmt->data, node->lineno);
            }
            break;
        case break_stmt_s:
        case continue_stmt_s:
            break;
        case block_s:
            typeBLOCK(node->val.block);
            break;
        case if_stmt_s:
            if(node->val.if_stmt.simple)
                typeSIMPLE(node->val.if_stmt.simple);
            typeEXPR(node->val.if_stmt.expr);
            isBool(resolveType(node->val.if_stmt.expr->data, node->symboltable, node->lineno), node->lineno);
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    typeBLOCK(node->val.if_stmt.val.if_block);
                    break;
                case else_if:
                    if(node->val.if_stmt.val.else_block.stmts)
                        typeSTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    switch (node->val.if_stmt.val.else_block.else_block->kind) {
                        case if_stmt_else:
                            if(node->val.if_stmt.val.else_block.else_block->val.if_stmt)
                                typeSTATEMENT(node->val.if_stmt.val.else_block.else_block->val.if_stmt);
                            break;
                        case block_else:
                            if(node->val.if_stmt.val.else_block.else_block->val.block)
                                typeBLOCK(node->val.if_stmt.val.else_block.else_block->val.block);
                            break;
                    }
                    break;
            }
            break;
        case switch_stmt_s:
            {
                if(node->val.switch_stmt.condition->simple)
                    typeSIMPLE(node->val.switch_stmt.condition->simple);
                if(node->val.switch_stmt.condition->expr)
                    typeEXPR(node->val.switch_stmt.condition->expr);
                if(node->val.switch_stmt.caselist){
                    for (SWITCH_CASELIST *i = node->val.switch_stmt.caselist; i; i=i->next) {
                        if(i->exprlist){
                            typeEXPRLIST(i->exprlist);
                            for (EXPRLIST *j = i->exprlist; j; j = j->next) {
                                if (!node->val.switch_stmt.condition->expr) {
                                    isBool(j->expr->data, j->lineno);
                                } else {
                                    mustHaveSameType(node->val.switch_stmt.condition->expr->data, j->expr->data, j->lineno);
                                }
                            }
                            if(i->statements)
                                typeSTATEMENTS(i->statements);
                        } else if (i->default_case){
                            if(i->statements)
                                typeSTATEMENTS(i->statements);
                        }
                    }
                }
            }
            break;
        case for_stmt_s:
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    if(node->val.for_stmt.block)
                        typeBLOCK(node->val.for_stmt.block);
                    break;
                case while_loop:
                    if(node->val.for_stmt.condition->val.while_expr)
                        typeEXPR(node->val.for_stmt.condition->val.while_expr);
                    isBool(resolveType(node->val.for_stmt.condition->val.while_expr->data, node->symboltable, node->val.for_stmt.condition->val.while_expr->lineno),
                            node->val.for_stmt.condition->val.while_expr->lineno);
                    if(node->val.for_stmt.block)
                        typeBLOCK(node->val.for_stmt.block);
                    break;
                case threepart:
                    if (node->val.for_stmt.condition->val.threepart.init)
                        typeSIMPLE(node->val.for_stmt.condition->val.threepart.init);
                    if (node->val.for_stmt.condition->val.threepart.condition){
                        typeEXPR(node->val.for_stmt.condition->val.threepart.condition);
                        isBool(resolveType(node->val.for_stmt.condition->val.threepart.condition->data, node->symboltable, node->val.for_stmt.condition->val.threepart.condition->lineno),
                                node->val.for_stmt.condition->val.threepart.condition->lineno);
                    }
                    if (node->val.for_stmt.condition->val.threepart.post)
                        typeSIMPLE(node->val.for_stmt.condition->val.threepart.post);
                    if(node->val.for_stmt.block)
                        typeBLOCK(node->val.for_stmt.block);
                    break;
            }
            break;
        case print_stmt_s:
        case println_stmt_s:
            typeEXPRLIST(node->val.print);
            for (EXPRLIST *i = node->val.print; i; i = i->next) {
                if (!(i->expr->data->val.type)) {
                    fprintf(stderr, "Error: (line %d) invalid type for print(ln)\n", node->lineno);
                    exit(1);
                }
                isBaseType(resolveType(i->expr->data, i->expr->symboltable, i->expr->lineno), i->expr->lineno);
            }
            break;
    }
}

/* make sure expression's children are well typed, and give a type to a expression itself */
void typeEXPR(EXPR *node) {
    switch (node->kind) {
        case expressionKindPlus:
            {
                typeEXPR(node->val.binary.lhs);
                typeEXPR(node->val.binary.rhs);
                mustHaveSameType(node->val.binary.lhs->data, node->val.binary.rhs->data, node->lineno);
                isNumericOrString(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), node->lineno);
                isNumericOrString(resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
                //node->data = resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno);

                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = node->val.binary.lhs->data->val.type;
            }
            break;
        case expressionKindMinus:
        case expressionKindMult:
        case expressionKindDiv:
            {
                typeEXPR(node->val.binary.lhs);
                typeEXPR(node->val.binary.rhs);
                isNumeric(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), node->lineno);
                isNumeric(resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
                mustHaveSameType(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
                //node->data = resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno);
                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = node->val.binary.lhs->data->val.type;
            }
            break;
        case expressionKindMod:
        case expressionKindOr:
        case expressionKindAnd:
        case expressionKindShift_Left:
        case expressionKindShift_Right:
        case expressionKindAMP_XOR:
        case expressionKindXor:
            {
                typeEXPR(node->val.binary.lhs);
                typeEXPR(node->val.binary.rhs);
                isInteger(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), node->lineno);
                isInteger(resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
                mustHaveSameType(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
                //node->data = resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno);
                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = node->val.binary.lhs->data->val.type;
            }
            break;
        case expressionKindLogicalAnd:
        case expressionKindLogicalOr:
            {
                typeEXPR(node->val.binary.lhs);
                typeEXPR(node->val.binary.rhs);
                isBool(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), node->lineno);
                isBool(resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
                //node->data = resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno);
                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = node->val.binary.lhs->data->val.type;
            }
            break;
        case expressionKindLT:
        case expressionKindLT_EQ:
        case expressionKindGT:
        case expressionKindGT_EQ:
        case expressionKindEQ_EQ:
        case expressionKindNotEquals:
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            //mustHaveSameType(resolveType(node->val.binary.lhs->data, node->symboltable, node->lineno), resolveType(node->val.binary.rhs->data, node->symboltable, node->lineno), node->lineno);
            mustHaveSameType(node->val.binary.lhs->data, node->val.binary.rhs->data, node->lineno);
            {
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;

                TYPE *type = malloc(sizeof(TYPE));
                type->kind = basic_type_kind;
                type->val.basic_type = "bool";

                data->val.type = type;
                node->data = data;
            }
            break;
        case expressionKindPlusUnary:
        case expressionKindMinusUnary:
            {
                typeEXPR(node->val.expr_unary);
                isNumeric(resolveType(node->val.expr_unary->data, node->symboltable, node->lineno), node->lineno);
                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = resolveType(node->val.expr_unary->data, node->symboltable, node->lineno)->val.type;
            }
            break;
        case expressionKindNotUnary:
            {
                typeEXPR(node->val.expr_unary);
                isBool(resolveType(node->val.expr_unary->data, node->symboltable, node->lineno), node->lineno);
                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = resolveType(node->val.expr_unary->data, node->symboltable, node->lineno)->val.type;
            }
            break;
        case expressionKindXorUnary:
            {
                typeEXPR(node->val.expr_unary);
                isInteger(resolveType(node->val.expr_unary->data, node->symboltable, node->lineno), node->lineno);
                node->data = malloc(sizeof(DataType));
                node->data->category = constant_category;
                node->data->valKind = type_type;
                node->data->val.type = resolveType(node->val.expr_unary->data, node->symboltable, node->lineno)->val.type;
            }
            break;
        case append_expr:
            {
                SYMBOL *s = getSymbol(node->symboltable, node->val.append_expr.identifier, node->lineno);
                DataType *slicetypedata = isSlice(resolveType(s->data, node->symboltable, node->lineno), node->lineno);
                typeEXPR(node->val.append_expr.expr);

                mustHaveSameType(slicetypedata, node->val.append_expr.expr->data, node->lineno);

                DataType *appendtype = malloc(sizeof(DataType));
                appendtype->category = constant_category;
                appendtype->valKind = type_type;
                appendtype->val.type = s->data->val.type;
                node->data = appendtype;
            }
            break;
        case intval:
            {
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;

                TYPE *type = malloc(sizeof(TYPE));
                type->kind = basic_type_kind;
                type->val.basic_type = "int";

                data->val.type = type;
                node->data = data;
            }
            break;
        case floatval:
            {
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;

                TYPE *type = malloc(sizeof(TYPE));
                type->kind = basic_type_kind;
                type->val.basic_type = "float64";

                data->val.type = type;
                node->data = data;
            }
            break;
        case stringval:
        case rawstringval:
            {
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;

                TYPE *type = malloc(sizeof(TYPE));
                type->kind = basic_type_kind;
                type->val.basic_type = "string";

                data->val.type = type;
                node->data = data;
            }
            break;
        case runeval:
            {
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;

                TYPE *type = malloc(sizeof(TYPE));
                type->kind = basic_type_kind;
                type->val.basic_type = "rune";

                data->val.type = type;
                node->data = data;
            }
            break;
        case other_expr_kind:
            typeOTHER_EXPR(node->val.other_expr);
            node->data = node->val.other_expr->data;
            break;
    }
}

void typeOTHER_EXPR(OTHER_EXPR *node) {
    switch (node->kind) {
        case identifier_kind:
            {
                // ignore requests for blank identifier in symbol table; in typechecking this can only happen in vardcl, assignment, shortdcl
                // all other invalid cases would already have been weeded out
                if (strcmp(node->val.identifier, "_") != 0) {
                    SYMBOL* s = getSymbol(node->symboltable, node->val.identifier, node->lineno);
                    node->data = s->data;
                }
            }
            break;
        case paren_kind:
            typeEXPR(node->val.expr);
            node->data = node->val.expr->data;
            break;
        case func_call_kind:
        {
            // typecheck argument list, and function expr
            typeEXPRLIST(node->val.func_call.args);
            typeOTHER_EXPR(node->val.func_call.id);

            // check if func expr is a function type
            //SYMBOL *s = getSymbol(node->symboltable, node->val.func_call.id->val.identifier, node->lineno);
            EXPRLIST *k = node->val.func_call.args;

            // we handle the semantics of both func calls and casts with func_call
            if (isFunction(node->val.func_call.id->data)) {

                // function parameter types must match argument types
                for (PARAM_LIST *i = node->val.func_call.id->data->val.func->params; i != NULL; i = i->next) {
                    for (IDLIST *j = i->idlist; j; j = j->next) {
                        SYMBOL *t = getSymbol(node->val.func_call.id->data->val.func->symboltable, j->id, node->lineno);
                        if (!k) {
                            fprintf(stderr, "Error: (line %d) invalid function call: number of parameters do not match number of arguments\n", node->lineno);
                            exit(1);
                        }
                        mustHaveSameType(t->data, k->expr->data, node->lineno);
                        k = k->next;
                    }
                }
                if (k) {
                    fprintf(stderr, "Error: (line %d) invalid function call: number of parameters do not match number of arguments\n", node->lineno);
                    exit(1);
                }
                
                // assign a type to this function call as the return type of the function
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;
                data->val.type = node->val.func_call.id->data->val.func->type;
                node->data = data;
            }
            else { // cast
                // check if cast type resolves to a base type
                isBaseType(resolveType(node->val.func_call.id->data, node->symboltable, node->lineno), node->lineno);

                if (!k || k->next) {
                    fprintf(stderr, "Error: (line %d) conversion expects exactly 1 argument\n", node->lineno);
                    exit(1);
                }
                validCast(resolveType(node->val.func_call.id->data, node->symboltable, node->lineno), resolveType(k->expr->data, node->symboltable, node->lineno), node->lineno);

                // assign a type to this cast as the type of the cast
                DataType *data = malloc(sizeof(DataType));
                data->category = constant_category;
                data->valKind = type_type;
                data->val.type = malloc(sizeof(TYPE));
                data->val.type->kind = basic_type_kind;
                data->val.type->val.basic_type = node->val.func_call.id->val.identifier;

                node->data = data;
            }
        }
            break;
        case index_kind:
            {
                typeOTHER_EXPR(node->val.index.expr);
                DataType *indextypedata = isSliceOrArray(resolveType(node->val.index.expr->data, node->symboltable, node->lineno), node->lineno);
                typeEXPR(node->val.index.index);
                isInteger(resolveType(node->val.index.index->data, node->symboltable, node->lineno), node->lineno);

                DataType *indextype = malloc(sizeof(DataType));
                indextype->category = variable_category;
                indextype->valKind = type_type;
                indextype->val.type = indextypedata->val.type;
                node->data = indextype;
            }
            break;
        case struct_access_kind:
            {
                typeOTHER_EXPR(node->val.struct_access.expr);
                isStruct(resolveType(node->val.struct_access.expr->data, node->symboltable, node->lineno), node->lineno);

                SYMBOL *s = getSymbol(resolveType(node->val.struct_access.expr->data, node->symboltable, node->lineno)->val.type->val.struct_type->symboltable, node->val.struct_access.identifier, node->lineno);

                DataType *structtype = malloc(sizeof(DataType));
                structtype->category = variable_category;
                structtype->valKind = type_type;
                structtype->val.type = s->data->val.type;
                node->data = structtype;
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
            break;
        case increment_kind:
        case decrement_kind:
            typeEXPR(node->val.expr);
            isNumeric(resolveType(node->val.expr->data, node->symboltable, node->lineno), node->lineno);
            break;
        case assignment_kind:
            {
                typeEXPRLIST(node->val.assignment.LHS_expr_list);
                typeEXPRLIST(node->val.assignment.RHS_expr_list);

                // loop through each variable and its corresponding expr; the lists should be the same length
                EXPRLIST *j = node->val.assignment.LHS_expr_list;
                EXPRLIST *k = node->val.assignment.RHS_expr_list;
                while (j) {
                    //SYMBOL *s = getSymbol(j->expr->symboltable, j->expr->val.other_expr->val.identifier, j->expr->lineno);
                    //mustHaveSameType(s->data, k->expr->data, j->expr->lineno);
                    if (j->expr->data) {
                        if (j->expr->data->category != variable_category) {
                            fprintf(stderr, "Error: (line %d) assignment expected lvalue\n", j->expr->lineno);
                            exit(1);
                        }
                        mustHaveSameType(j->expr->data, k->expr->data, j->expr->lineno);
                    }
                    j = j->next;
                    k = k->next;
                }
            }
            break;
        case shortDcl_kind:
            {
                typeEXPRLIST(node->val.shortDcl.RHS_expr_list);

                // loop through each variable and its corresponding expr; the lists should be the same length
                EXPRLIST *j = node->val.shortDcl.LHS_idlist;
                EXPRLIST *k = node->val.shortDcl.RHS_expr_list;
                while (j) {
                    char *id = j->expr->val.other_expr->val.identifier;

                    // ignore requests for blank identifier in symbol table
                    if (strcmp(id, "_") != 0) {
                        SYMBOL *s = getSymbol(node->symboltable, id, j->lineno);

                        // if variable has a declared type then check that expr type is the same
                        if (s->data->val.type) { 
                            mustHaveSameType(s->data, k->expr->data, j->lineno);
                        }
                        else {
                            // if variable does not have a declared type then just use the expression's type and add to symbol table
                            addSymbolType(node->symboltable, id, k->expr->data);
                        }
                    }
                    j = j->next;
                    k = k->next;
                }
            }
            break;
    }
}

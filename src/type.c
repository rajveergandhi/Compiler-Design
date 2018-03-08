#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "type.h"

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


void typePROGRAM(PROGRAM *node) {
    initTypes();
    if (node!=NULL) {
        typeTOPLEVELDECL(node->topleveldecls);
    }
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
    // for var x T = expr, check that expr is well-typed and T1 = T. if no T, add mapping x:T is expr is well-typed
    // if x is already declared, but in an outer scope, new mapping will shadow previous one.
    for (VARDCL *i = node; i; i = i->next)
        for (IDLIST *j = i->idlist; j; j = j->next)
}

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
            // trivially well-typed.
            break;
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
            // check if its expressions are well-typed and resolve to a base type.
            typeEXPRLIST(node->val.print);
            break;
        case println_stmt_s:
            // check if its expressions are well-typed and resolve to a base type.
            typeEXPRLIST(node->val.print);
            break;
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

void typeEXPRLIST(EXPRLIST *node) {
    for (EXPRLIST *i = node; i; i = i->next) {
        typeEXPR(i->expr);
    }
}

void typeEXPR(EXPR *node) {
    // give a type to a expression itself. this type should be stored in AST as it will be queried by expressions parent

    switch (node->kind) {
        // well-typed if its sub-expressions are well-typed, are of the same type and that type
        // resolved to a type appropriate for the operation.
        case expressionKindPlus:
            // result = numeric or string
            // LHS = RHS = numeric or string
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindMinus:
            // LHS = RHS = numeric
            // result = numeric
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindMult:
            // LHS = RHS = numeric
            // result = numeric
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindDiv:
            // LHS = RHS = numeric
            // result = numeric
            // dont handle division by 0. let executable throw appropriate error
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindMod:
            // LHS = RHS = integer
            // result = integer
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindLT:
            // LHS = RHS = ordered
            // result = bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindLT_EQ:
            // LHS = RHS = ordered
            // result bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindGT:
            // LHS = RHS = ordered
            // result bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindGT_EQ:
            // LHS = RHS = ordered
            // result bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindEQ_EQ:
            // LHS = RHS = comparable
            // result bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindNotEquals:
            // LHS = RHS = comparable
            // result bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindShift_Right:
            // LHS = RHS = integer
            // result int
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindShift_Left:
            // LHS = RHS = integer
            // result int
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindAnd:
            // result bool
            // LHS = RHS = bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindAMP_XOR:
            // LHS = RHS = integer.
            // result = integer
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindOr:
            // result bool
            // LHS = RHS = bool
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindXor:
            // LHS = RHS = result = integer
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindLogicalAnd:
            // LHS = RHS = RESULT = integer
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindLogicalOr:
            // LHS = RHS = RESULT = integer
            typeEXPR(node->val.binary.lhs);
            typeEXPR(node->val.binary.rhs);
            break;
        case expressionKindPlusUnary:
            // well-typed if its sub-expression is well-typed and have appropriate type for the operation.
            // the type of a unary expression is always the same as its child.
            // here expr must resolve to a numeric type (int float rune)
            typeEXPR(node->val.expr_unary);
            break;
        case expressionKindMinusUnary:
            // here expr must resolve to a numeric type (int float rune)
            typeEXPR(node->val.expr_unary);
            break;
        case expressionKindNotUnary:
            // here expr must resolve to bool
            typeEXPR(node->val.expr_unary);
            break;
        case expressionKindXorUnary:
            // here expr must resolve to bool
            // bitwise negation must resolve to integer type (int, rune)
            typeEXPR(node->val.expr_unary);
            break;
        case append_expr:
            // append (e1, e2)
            // e1 is well-typed, has type S and S resolves to a []T
            // e2 is well-typed and has type T
            typeEXPR(node->val.append_expr.expr);
            break;
        case intval:
            // int literals should have type int
            break;
        case floatval:
            // float literals should have type float
            break;
        case stringval:
            // string literals should have type string
            break;
        case rawstringval:
            // string literals should have type string
            break;
        case runeval:
            // rune literals should have type rune
            break;
        case other_expr_kind:
            typeOTHER_EXPR(node->val.other_expr);
            break;
    }
}

void typeOTHER_EXPR(OTHER_EXPR *node) {
    switch (node->kind) {
        case identifier_kind:
            // type of identifier obtained by querying symbol table. if not found, error.
            break;
        case paren_kind:
            typeEXPR(node->val.expr);
            break;
        case func_call_kind:
            // args are well typed and have typed T1, T2...Tk.
            // expr is well-typed and has function type (T1 * T2 *..) -> Tr
            // special function init should NOT be called.
            // type-cast: type resolves to a base type (int float bool rune string)
            // expr is well-typed and has a type that can be cast to type:
            // type and expr resolve to identical underlying types;
            // type and expr both resolve to numeric types;
            // type resolved to a string type and expr resolves to an integer type (rune or int);
            typeOTHER_EXPR(node->val.func_call.id);
            typeEXPRLIST(node->val.func_call.args);
            break;
        case index_kind:
            // expr is well-typed and resolved to []T
            // index is well-typed and resolves to int
            // result of indexing expression is T
            // out of bounds array check done at runtime.
            typeOTHER_EXPR(node->val.index.expr);
            typeEXPR(node->val.index.index);
            break;
        case struct_access_kind:
            // selecting a field in a struct. expr is well-typed and has type S. S should resolve to a
            // struct type that has a field named id.
            typeOTHER_EXPR(node->val.struct_access.expr);
            break;
    }
}

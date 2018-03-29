#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "weed.h"

static int insideFor = 0;
static int insideSwitch = 0;
static bool isBlankIdValid = false;
static int insideFunction = 0;
static bool hasReturn = false;

void weedPROGRAM(PROGRAM *node) {
    weedPACKAGE(node->package);
    weedTOPLEVELDECL(node->topleveldecls);
}

void weedPACKAGE(PACKAGE *node) {
    if(strcmp(node->package,"_") == 0){
        fprintf(stderr, "Error: invalid usage of blank identifier. (line %d)\n",node->lineno);
        exit(1);
    }
}

void weedTOPLEVELDECL(TOPLEVELDECL *node) {
    for (TOPLEVELDECL *i = node; i; i = i->next) {
        switch (i->kind) {
            case dcl_toplevel:
                weedDCL(i->val.dcl);
                break;
            case func_dcl_toplevel:
                weedFUNCDCL(i->val.funcdcl);
                break;
        }
    }
}

void weedDCL(DCL *node) {
    switch (node->kind) {
        case var:
            weedVARDCL(node->val.vardcl);
            break;
        case type:
            weedTYPEDCL(node->val.typedcl);
            break;
    }
}

void weedVARDCL(VARDCL *node) {
    int lhsCount = 0;
    int rhsCount = 0;
    for (VARDCL *i = node; i; i = i->next) {
        isBlankIdValid = true;
        lhsCount = weedIDLIST(i->idlist);
        isBlankIdValid = false;
        if (i->type) {
            weedTYPE(i->type);
        }
        if (i->exprlist) {
            rhsCount = weedEXPRLIST(i->exprlist);
        }
        if(rhsCount > 0 && lhsCount != rhsCount){
            fprintf(stderr, "Error: LHS and RHS assignment mismatch (%d = %d). (line %d)\n",lhsCount, rhsCount, node->lineno);
            exit(1);
        }
        lhsCount = 0;
        rhsCount = 0;
    }
}

void weedTYPEDCL(TYPEDCL *node) {
    for (TYPEDCL *i = node; i; i = i->next) {
        weedTYPE(i->type);
    }
}

void weedFUNCDCL(FUNCDCL *node) {
    weedFUNC_SIGNATURE(node->signature);
    insideFunction++;
    weedBLOCK(node->block);
    insideFunction--;
}

void weedFUNC_SIGNATURE(FUNC_SIGNATURE *node) {
    for (PARAM_LIST *i = node->params; i; i = i->next) {
        isBlankIdValid = true;
        weedIDLIST(i->idlist);
        isBlankIdValid = false;
        weedTYPE(i->type);
    }
    if (node->type) {
        isBlankIdValid = false;
        hasReturn = true;
        weedTYPE(node->type);
    }
}

int weedIDLIST(IDLIST *node) {
    int lhs = 0;
    for (IDLIST *i = node; i; i = i->next) {
        if(!isBlankIdValid && strcmp(i->id,"_") == 0 && i->id != NULL) {
            fprintf(stderr, "Error: invalid usage of blank identifier. (line %d)\n",node->lineno);
            exit(1);
        }
        lhs++;
    }
    return lhs;
}

void weedBLOCK(BLOCK *node) {
    if(node->stmts)
        weedSTATEMENTS(node->stmts);
}

void weedSTATEMENTS(STATEMENTS *node) {
    for (STATEMENTS *i = node; i; i = i->next){
        weedSTATEMENT(i->stmt);
    }
}

void weedSTATEMENT(STATEMENT *node) {
    switch(node->kind) {
        case dcl_s:
            weedDCL(node->val.dcl);
            break;
        case simple_s:
            weedSIMPLE(node->val.simple);
            break;
        case return_stmt_s:
            if (insideFunction == 0)
            {
                fprintf(stderr, "Error: return statement can only be inside a function. (line %d)\n",node->lineno);
                exit(1);
            }
            if (node->val.return_stmt && hasReturn == true) {
                weedEXPR(node->val.return_stmt);
            }
            break;
        case break_stmt_s:
            if(insideFor == 0 && insideSwitch == 0){
                fprintf(stderr, "Error: break statement can only be inside a for loop or switch block. (line %d)\n",node->lineno);
                exit(1);
            }
            break;
        case continue_stmt_s:
            if(insideFor == 0){
                fprintf(stderr, "Error: continue statement can only be inside a for loop. (line %d)\n",node->lineno);
                exit(1);
            }
            break;
        case block_s:
            weedBLOCK(node->val.block);
            break;
        case if_stmt_s:
            if (node->val.if_stmt.simple) {
                weedSIMPLE(node->val.if_stmt.simple);
            }
            weedEXPR(node->val.if_stmt.expr);
            switch (node->val.if_stmt.kind_else) {
                case no_else:
                    weedBLOCK(node->val.if_stmt.val.if_block);
                    break;
                case else_if:
                    if(node->val.if_stmt.val.else_block.stmts)
                        weedSTATEMENTS(node->val.if_stmt.val.else_block.stmts);
                    weedELSE_BLOCK(node->val.if_stmt.val.else_block.else_block);
                    break;
            }
            break;
        case switch_stmt_s:
            insideSwitch++;
            if (node->val.switch_stmt.condition->simple) {
                weedSIMPLE(node->val.switch_stmt.condition->simple);
            }
            if (node->val.switch_stmt.condition->expr) {
                weedEXPR(node->val.switch_stmt.condition->expr);
            }
            if (node->val.switch_stmt.caselist)
                weedSWITCH_CASELIST(node->val.switch_stmt.caselist);
            insideSwitch--;
            break;
        case for_stmt_s:
            insideFor++;
            switch(node->val.for_stmt.condition->kind) {
                case infinite:
                    break;
                case while_loop:
                    weedEXPR(node->val.for_stmt.condition->val.while_expr);
                    break;
                case threepart:
                    if (node->val.for_stmt.condition->val.threepart.init) {
                        weedSIMPLE(node->val.for_stmt.condition->val.threepart.init);
                    }
                    if (node->val.for_stmt.condition->val.threepart.condition) {
                        weedEXPR(node->val.for_stmt.condition->val.threepart.condition);
                    }
                    if (node->val.for_stmt.condition->val.threepart.post)
                        weedSIMPLE(node->val.for_stmt.condition->val.threepart.post);
                    break;
            }
            weedBLOCK(node->val.for_stmt.block);
            insideFor--;
            break;
        case print_stmt_s:
            weedEXPRLIST(node->val.print);
            break;
        case println_stmt_s:
            weedEXPRLIST(node->val.print);
            break;
    }
}

void weedSWITCH_CASELIST(SWITCH_CASELIST *node) {
    bool hasDefault = false;
    for (SWITCH_CASELIST *i = node; i; i=i->next) {
        if (i->default_case && !hasDefault) {
            hasDefault = true;
        }
        else if (i->default_case && hasDefault) {
            fprintf(stderr, "Error: switch block can have only one default case. (line %d)\n",node->lineno);
            exit(1);
        }
        else {
            weedEXPRLIST(i->exprlist);
        }
        if (i->statements)
            weedSTATEMENTS(i->statements);
    }
}

void weedELSE_BLOCK(ELSE_BLOCK *node) {
    switch (node->kind) {
        case if_stmt_else:
            weedSTATEMENT(node->val.if_stmt);
            break;
        case block_else:
            weedBLOCK(node->val.block);
            break;
    }
}

void weedSIMPLE(SIMPLE *node) {
    int lhsCount = 0;
    int rhsCount = 0;
    switch (node->kind) {
        case empty_stmt_kind:
            break;
        case expr_kind:
            weedEXPR(node->val.expr);
            break;
        case increment_kind:
            weedEXPR(node->val.expr);
            break;
        case decrement_kind:
            weedEXPR(node->val.expr);
            break;
        case assignment_kind:
            if(strcmp(node->val.assignment.assign_op,"=") == 0)
                isBlankIdValid = true;
            lhsCount = 0;
            lhsCount = weedEXPRLIST(node->val.assignment.LHS_expr_list);
            isBlankIdValid = false;
            rhsCount = 0;
            rhsCount = weedEXPRLIST(node->val.assignment.RHS_expr_list);
            if(rhsCount > 0 && lhsCount != rhsCount){
                fprintf(stderr, "Error: LHS and RHS assignment mismatch (%d = %d). (line %d)\n",lhsCount, rhsCount, node->lineno);
                exit(1);
            }
            lhsCount = 0;
            rhsCount = 0;
            break;
        case shortDcl_kind:
            isBlankIdValid = true;
            lhsCount = 0;
            lhsCount = weedEXPRLIST(node->val.shortDcl.LHS_idlist);
            isBlankIdValid = false;
            rhsCount = 0;
            rhsCount = weedEXPRLIST(node->val.shortDcl.RHS_expr_list);
            if(rhsCount > 0 && lhsCount != rhsCount){
                fprintf(stderr, "Error: LHS and RHS assignment mismatch (%d = %d). (line %d)\n",lhsCount, rhsCount, node->lineno);
                exit(1);
            }
            lhsCount = 0;
            rhsCount = 0;
            break;
    }
}

void weedTYPE(TYPE *node) {
    switch (node->kind) {
        case basic_type_kind:
            if(strcmp(node->val.basic_type,"_") == 0 && node->val.basic_type != NULL){
                fprintf(stderr, "Error: invalid usage of blank identifier. (line %d)\n",node->lineno);
                exit(1);
            }
            break;
        case slice_type_kind:
            weedTYPE(node->val.slice_type);
            break;
        case array_type_kind:
            weedTYPE(node->val.array_type.type);
            break;
        case struct_type_kind:
            for (STRUCT_TYPE *i = node->val.struct_type; i; i = i->next) {
                isBlankIdValid = true;
                weedIDLIST(i->idlist);
                isBlankIdValid = false;
                weedTYPE(i->type);
            }
            break;
    }
}

int weedEXPRLIST(EXPRLIST *node) {
    int rhs = 0;
    for (EXPRLIST *i = node; i; i = i->next) {
        weedEXPR(i->expr);
        rhs++;
    }
    return rhs;
}

void weedEXPR(EXPR *node) {
    bool copy = isBlankIdValid;
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
	    isBlankIdValid = false;
            weedEXPR(node->val.binary.lhs);
            weedEXPR(node->val.binary.rhs);
            break;
        case expressionKindPlusUnary:
        case expressionKindMinusUnary:
        case expressionKindNotUnary:
        case expressionKindXorUnary:
	    isBlankIdValid = false;
            weedEXPR(node->val.expr_unary);
            break;
        case append_expr:
	    if(strcmp(node->val.append_expr.identifier,"_") == 0 && node->val.append_expr.identifier != NULL){
                fprintf(stderr, "Error: invalid usage of blank identifier. (line %d)\n",node->lineno);
                exit(1);
            }
	    isBlankIdValid = false;
            weedEXPR(node->val.append_expr.expr);
            break;
        case intval:
        case floatval:
        case stringval:
        case rawstringval:
        case runeval:
            break;
        case other_expr_kind:
            weedOTHER_EXPR(node->val.other_expr);
            break;
    }
    isBlankIdValid = copy;
}

void weedOTHER_EXPR(OTHER_EXPR *node) {
    switch (node->kind) {
        case identifier_kind:
            if(!isBlankIdValid && strcmp(node->val.identifier,"_") == 0 && node->val.identifier != NULL){
                fprintf(stderr, "Error: invalid usage of blank identifier. (line %d)\n",node->lineno);
                exit(1);
            }
            break;
        case paren_kind:
            weedEXPR(node->val.expr);
            break;
        case func_call_kind:
	{
	    bool copy = isBlankIdValid;
	    isBlankIdValid = false;
            weedOTHER_EXPR(node->val.func_call.id);
            weedEXPRLIST(node->val.func_call.args);
	    isBlankIdValid = copy;
            break;
	}
        case index_kind:
	{
	    bool copy = isBlankIdValid;
            isBlankIdValid = false;
            weedOTHER_EXPR(node->val.index.expr);
            weedEXPR(node->val.index.index);
	    isBlankIdValid = copy;
            break;
	}
        case struct_access_kind:
            if(strcmp(node->val.struct_access.identifier,"_") == 0 && node->val.struct_access.identifier != NULL){
                fprintf(stderr, "Error: invalid usage of blank identifier. (line %d)\n",node->lineno);
                exit(1);
            }
            bool copy = isBlankIdValid;
            isBlankIdValid = false;
            weedOTHER_EXPR(node->val.struct_access.expr);
            isBlankIdValid = copy;
            break;
    }
}


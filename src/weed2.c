#include <stdio.h>
#include <stdlib.h> //remove later after testing this file
#include <stdbool.h>
#include <string.h>
#include "weed2.h"

static int insideFor = 0;
static int insideSwitch = 0;
static bool hasDefault = false;
static bool isBlankIdValid = false;


void weed(NODE *node) {
    switch (node->kind) {
        case k_program:
            weed(node->val.program.package);
            weed(node->val.program.topLevelDecls);
            break;
        case k_package:
            if(strcmp(node->val.package,"_") == 0){
                fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
                exit(1);
            }
            break;
        case k_dcl_var:
            for (NODE *TOPLEVEL = node; TOPLEVEL != NULL; TOPLEVEL = TOPLEVEL->val.toplevel.next) {
                if (TOPLEVEL->kind == k_dcl_var) {
                    for (NODE *i = TOPLEVEL; i != NULL; i = i->val.toplevel.type.varDcl.next) {
                        if (i->val.toplevel.type.varDcl.idlist) {
                            isBlankIdValid = true;
                            weed(i->val.toplevel.type.varDcl.idlist);
                            isBlankIdValid = false;
                        }
                        if (i->val.toplevel.type.varDcl.type) {
                            weed(i->val.toplevel.type.varDcl.type);
                        }
                        if (i->val.toplevel.type.varDcl.expr_list) {
                            for (NODE *j = i->val.toplevel.type.varDcl.expr_list; j != NULL; j = j->val.expr.next) {
                                weed(j);
                            }
                        }
                    }
                } else {
                    weed(TOPLEVEL);
                    break;
                }
            }
            break;
        case k_idlist:
            for (NODE *i = node; i != NULL; i = i->val.idlist.next) {
                //Do nothing
            }
            break;
        case k_dcl_type:
            for (NODE *TOPLEVEL = node; TOPLEVEL; TOPLEVEL = TOPLEVEL->val.toplevel.next) {
                if (TOPLEVEL->kind == k_dcl_type) {
                    for (NODE *i = TOPLEVEL; i != NULL; i = i->val.toplevel.type.typeDcl.next) {
                        if(i->val.toplevel.type.typeDcl.identifier) {
                            if(strcmp(i->val.toplevel.type.typeDcl.identifier,"_") == 0){
                                fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
                                exit(1);
                            }
                            weed(i->val.toplevel.type.typeDcl.type);
                        }
                    }
                }
                else {
                    weed(TOPLEVEL);
                    break;
                }
            }
            break;
        case k_array:
            weed(node->val.typeArray.type);
            break;
        case k_slice:
            weed(node->val.typeSlice.type);
            break;
        case k_struct:
            for (NODE *i = node; i; i = i->val.typeStruct.next) {
                if (i->val.typeStruct.idlist) {
                    weed(i->val.typeStruct.idlist);
                    weed(i->val.typeStruct.type);
                }
            }
            break;
        case k_function:
            for (NODE *TOPLEVEL = node; TOPLEVEL; TOPLEVEL = TOPLEVEL->val.toplevel.next) {
                if (TOPLEVEL->kind == k_function) {
                    if(strcmp(TOPLEVEL->val.toplevel.type.funcDcl.identifier,"_") == 0){
                        fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
                        exit(1);
                    }
                    weed(TOPLEVEL->val.toplevel.type.funcDcl.signature);
                    weed(TOPLEVEL->val.toplevel.type.funcDcl.block);
                }
                else {
                    weed(TOPLEVEL);
                    break;
                }
            }
            break;
        case k_function_signature:
            if (node->val.funcSign.params)
                weed(node->val.funcSign.params);
            if (node->val.funcSign.type) {
                weed(node->val.funcSign.type);
            }
            break;
        case k_function_params:
            weed(node->val.funcParams.idlist);
            weed(node->val.funcParams.type);
            if (node->val.funcParams.param_list) {
                weed(node->val.funcParams.param_list);
            }
            break;
        case k_block:
            if (node->val.stmt.type.block.stmts)
                weed(node->val.stmt.type.block.stmts);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_append:
            if(strcmp(node->val.expr.type.expr_append.identifier,"_") == 0){
                fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
                exit(1);
            }
            weed(node->val.expr.type.expr_append.expr);
            break;
        case k_function_call:
            weed(node->val.expr.type.funcCall.id);
            weed(node->val.expr.type.funcCall.args);
            //if (node->val.expr.next)
                //weed(node->val.expr.next);
            break;
        case k_statementKindPrint:
            if (node->val.stmt.type.print.expr_list)
                weed(node->val.stmt.type.print.expr_list);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindReturn:
            if (node->val.stmt.type.stmtReturn.expr)
                weed(node->val.stmt.type.stmtReturn.expr);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindIf:
            if (node->val.stmt.type.stmtIf.simple) {
                weed(node->val.stmt.type.stmtIf.simple);
            }
            weed(node->val.stmt.type.stmtIf.expr);
            weed(node->val.stmt.type.stmtIf.stmts);
            if (node->val.stmt.type.stmtIf.elseBlock) {
                weed(node->val.stmt.type.stmtIf.elseBlock);
            }
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindFor:
            if (node->val.stmt.type.stmtFor.condition) {
                weed(node->val.stmt.type.stmtFor.condition);
            }
            insideFor++;
            weed(node->val.stmt.type.stmtFor.block);
            insideFor--;
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindForCond:
            weed(node->val.stmtForCondition.part1);
            weed(node->val.stmtForCondition.part2);
            weed(node->val.stmtForCondition.part3);
            break;
        case k_statementKindSwitch:
            
            if (node->val.stmt.type.stmtSwitch.condition) {
                weed(node->val.stmt.type.stmtSwitch.condition);
            }
            insideSwitch++;
            weed(node->val.stmt.type.stmtSwitch.caselist);
            insideSwitch++;
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindSwitchCondition:
            if (node->val.stmtSwitchCondition.simple) {
                weed(node->val.stmtSwitchCondition.simple);
            }
            if (node->val.stmtSwitchCondition.expr)
                weed(node->val.stmtSwitchCondition.expr);
            break;
        case k_statementKindSwitchCase:
            if (node->val.stmtSwitchCase.expr_list) {
                weed(node->val.stmtSwitchCase.expr_list);
            } else if (!node->val.stmtSwitchCase.expr_list && !hasDefault){
                hasDefault = true;
            } else if (!node->val.stmtSwitchCase.expr_list && hasDefault){
                fprintf(stderr, "Error: (line %d) a switch-case block can only have one default block\n", node->lineno);
                exit(1);
            }
            if (node->val.stmtSwitchCase.statement_list)
                weed(node->val.stmtSwitchCase.statement_list);
            if (node->val.stmtSwitchCase.next)
                weed(node->val.stmtSwitchCase.next);
            else
                hasDefault = false;
            break;
        case k_statementKindBreak:
            if(insideFor == 0 || insideSwitch == 0){
                fprintf(stderr, "Error: (line %d) break statements can only be inside a for loop or switch block\n", node->lineno);
                exit(1);
            }
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindContinue:
            if(!insideFor){
                fprintf(stderr, "Error: (line %d) continue statements can only be inside a for loop\n", node->lineno);
                exit(1);
            }
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindSimple:
            weed(node->val.stmt.type.stmtSimple.simple);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindIncrement:
            weed(node->val.stmt.type.stmtInc.expr);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindAssign:
            isBlankIdValid = true; 
            weed(node->val.stmt.type.stmtAssign.LHS_expr_list);
            isBlankIdValid = false;
            weed(node->val.stmt.type.stmtAssign.RHS_expr_list);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_statementKindShortDcl:
            weed(node->val.stmt.type.stmtShortDcl.LHS_expr_list);
            weed(node->val.stmt.type.stmtShortDcl.RHS_expr_list);
            if (node->val.stmt.next)
                weed(node->val.stmt.next);
            break;
        case k_expressionArrayIndex:
            weed(node->val.expr.type.arrayIndex.expr);
            weed(node->val.expr.type.arrayIndex.index);
            //if (node->val.expr.next)
                //weed(node->val.expr.next);
            break;
        case k_expressionKindStructSelector:
            weed(node->val.expr.type.structSelector.expr);
            if(strcmp(node->val.expr.type.structSelector.identifier,"_") == 0){
                fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
                exit(1);
            }
            //if (node->val.expr.next)
                //weed(node->val.expr.next);
            break;
        case k_expressionKindIdentifier:
            if(!isBlankIdValid && strcmp(node->val.expr.type.identifier,"_") == 0){
                fprintf(stderr, "Error: (line %d) invalid use of blank identifier\n", node->lineno);
                exit(1);
            }           
            break;
        case k_expressionKindIntLiteral:
        case k_expressionKindFloatLiteral:
        case k_expressionKindStringLiteral:
        case k_expressionKindRuneLiteral:
            break;
        case k_expressionKindPlus:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindMinus:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindMult:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindDiv:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindMod:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLT:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLT_EQ:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindGT:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindGT_EQ:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindEQ_EQ:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindNotEquals:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindShift_Right:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindShift_Left:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindAnd:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindAMP_XOR:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindOr:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindXor:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLogicalAnd:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindLogicalOr:
            weed(node->val.expr.type.exp_binary.lhs);
            weed(node->val.expr.type.exp_binary.rhs);
            break;
        case k_expressionKindNotUnary:
            weed(node->val.expr.type.exp_unary);
            break;
        case k_expressionKindPlusUnary:
            weed(node->val.expr.type.exp_unary);
            break;
        case k_expressionKindMinusUnary:
            weed(node->val.expr.type.exp_unary);
            break;
        case k_expressionKindXorUnary:
            weed(node->val.expr.type.exp_unary);
            break;
    }
}

#include <stdio.h>
#include <stdlib.h> //remove later after testing this file
#include "pretty.h"

// global indentation variable; it is incremented whenever necessary (if or while statement)
int g_indent = 0;

void prettyIndent(int indent_level) {
    int indent_val = 4; // one level of indentation is defined as 4 spaces
    for (int i = 0; i < indent_val * indent_level; ++i) {
        printf(" ");
    }
}

void prettyPrint(NODE *node) {
    switch (node->kind) {
        case k_program:
            prettyPrint(node->val.program.package);
            prettyPrint(node->val.program.topLevelDecls);
            break;
        case k_package:
            printf("package %s\n", node->val.package);
            break;
        case k_dcl_var:
            for (NODE *TOPLEVEL = node; TOPLEVEL != NULL; TOPLEVEL = TOPLEVEL->val.toplevel.next) {
                if (TOPLEVEL->kind == k_dcl_var) {
                    for (NODE *i = TOPLEVEL; i != NULL; i = i->val.toplevel.type.varDcl.next) {
                        printf("var ");
                        if (i->val.toplevel.type.varDcl.idlist)
                            prettyPrint(i->val.toplevel.type.varDcl.idlist);
                        if (i->val.toplevel.type.varDcl.type) {
                            printf(" ");
                            prettyPrint(i->val.toplevel.type.varDcl.type);
                        }
                        if (i->val.toplevel.type.varDcl.expr_list) {
                            printf(" = ");
                            for (NODE *j = i->val.toplevel.type.varDcl.expr_list; j != NULL; j = j->val.expr.next) {
                                prettyPrint(j);
                                if (j->val.expr.next != NULL) printf(", ");
                            }
                        }
                        printf("\n");
                        //TOPLEVEL = TOPLEVEL->val.toplevel.next;
                        //printf("-----\n");
                    }
                } else {
                    prettyPrint(TOPLEVEL);
                    break;
                }
            }
            break;
        case k_idlist:
            for (NODE *i = node; i != NULL; i = i->val.idlist.next) {
                printf("%s", i->val.idlist.identifier);
                if (i->val.idlist.next != NULL) printf(", ");
            }
            break;
        case k_dcl_type:
            for (NODE *TOPLEVEL = node; TOPLEVEL; TOPLEVEL = TOPLEVEL->val.toplevel.next) {
                if (TOPLEVEL->kind == k_dcl_type) {
                    for (NODE *i = TOPLEVEL; i != NULL; i = i->val.toplevel.type.typeDcl.next) {
                        if(i->val.toplevel.type.typeDcl.identifier) {
                        printf("type ");
                        printf("%s ", i->val.toplevel.type.typeDcl.identifier);
                        prettyPrint(i->val.toplevel.type.typeDcl.type);
                        printf("\n");
                        }
                    }
                }
                else {
                    prettyPrint(TOPLEVEL);
                    break;
                }
            }
            break;
        case k_array:
            printf("[");
            printf("%d", node->val.typeArray.intval);
            printf("]");
            prettyPrint(node->val.typeArray.type);
            break;
        case k_slice:
            printf("[");
            printf("]");
            prettyPrint(node->val.typeSlice.type);
            break;
        case k_struct:
            printf("struct {\n");
            for (NODE *i = node; i; i = i->val.typeStruct.next) {
                prettyPrint(i->val.typeStruct.idlist);
                prettyPrint(i->val.typeStruct.type);
                printf(";\n");
            }
            printf("}\n");
            break;
        case k_function:
            for (NODE *TOPLEVEL = node; TOPLEVEL; TOPLEVEL = TOPLEVEL->val.toplevel.next) {
                if (TOPLEVEL->kind == k_function) {
                    printf("func %s", TOPLEVEL->val.toplevel.type.funcDcl.identifier);
                    prettyPrint(TOPLEVEL->val.toplevel.type.funcDcl.signature);
                    printf(" {\n");
                    prettyPrint(TOPLEVEL->val.toplevel.type.funcDcl.block);
                    printf("}\n");
                }
                else {
                    prettyPrint(TOPLEVEL);
                    break;
                }
            }
            break;
        case k_function_signature:
            printf("(");
            if (node->val.funcSign.params)
                prettyPrint(node->val.funcSign.params);
            printf(")");
            if (node->val.funcSign.type) {
                printf(" ");
                prettyPrint(node->val.funcSign.type);
            }
            break;
        case k_function_params:
            prettyPrint(node->val.funcParams.idlist);
            printf(" ");
            prettyPrint(node->val.funcParams.type);
            if (node->val.funcParams.param_list) {
                printf(", ");
                prettyPrint(node->val.funcParams.param_list);
            }
            break;
        case k_block:
            printf("{\n");
            if (node->val.stmt.type.block.stmts)
                prettyPrint(node->val.stmt.type.block.stmts);
            printf("\n}\n");
            break;
        case k_append:
            printf("append(%s, ", node->val.expr.type.expr_append.identifier);
            prettyPrint(node->val.expr.type.expr_append.expr);
            printf(")\n");
            break;
        case k_function_call:
            prettyPrint(node->val.expr.type.funcCall.id);
            printf("(");
            prettyPrint(node->val.expr.type.funcCall.args);
            printf(")\n");
            //if (node->val.expr.next)
                //prettyPrint(node->val.expr.next);
            break;
        case k_statementKindPrint:
            printf("print");
            if (node->val.stmt.type.print.println)
                printf("ln");
            printf(" (");
            if (node->val.stmt.type.print.expr_list)
                prettyPrint(node->val.stmt.type.print.expr_list);
            printf(")\n");
            break;
        case k_statementKindReturn:
            printf("return ");
            if (node->val.stmt.type.stmtReturn.expr)
                prettyPrint(node->val.stmt.type.stmtReturn.expr);
            printf("\n");
            break;
        case k_statementKindIf:
            printf("if ");
            if (node->val.stmt.type.stmtIf.simple) {
                prettyPrint(node->val.stmt.type.stmtIf.simple);
                printf(";");
            }
            prettyPrint(node->val.stmt.type.stmtIf.expr);
            printf(" {\n");
            prettyPrint(node->val.stmt.type.stmtIf.stmts);
            printf("}");
            if (node->val.stmt.type.stmtIf.elseBlock) {
                printf(" else ");
                prettyPrint(node->val.stmt.type.stmtIf.elseBlock);
            }
            break;
        case k_statementKindFor:
            printf("for ");
            if (node->val.stmt.type.stmtFor.condition) {
                prettyPrint(node->val.stmt.type.stmtFor.condition);
                printf(" ");
            }
            printf("{\n");
            prettyPrint(node->val.stmt.type.stmtFor.block);
            printf("}\n");
            break;
        case k_statementKindForCond:
            prettyPrint(node->val.stmtForCondition.part1);
            printf("; ");
            prettyPrint(node->val.stmtForCondition.part2);
            printf("; ");
            prettyPrint(node->val.stmtForCondition.part3);
            break;
        case k_statementKindSwitch:
            printf("switch ");
            if (node->val.stmt.type.stmtSwitch.condition) {
                prettyPrint(node->val.stmt.type.stmtSwitch.condition);
                printf(" ");
            }
            printf("{\n");
            prettyPrint(node->val.stmt.type.stmtSwitch.caselist);
            printf("}\n");
            break;
        case k_statementKindSwitchCondition:
            if (node->val.stmtSwitchCondition.simple) {
                prettyPrint(node->val.stmtSwitchCondition.simple);
                printf(";");
            }
            if (node->val.stmtSwitchCondition.expr)
                prettyPrint(node->val.stmtSwitchCondition.expr);
            break;
        case k_statementKindSwitchCase:
            if (node->val.stmtSwitchCase.expr_list)
                prettyPrint(node->val.stmtSwitchCase.expr_list);
            else
                printf("default");
            printf(":\n");
            prettyPrint(node->val.stmtSwitchCase.statement_list);
            if (node->val.stmtSwitchCase.next)
                prettyPrint(node->val.stmtSwitchCase.next);
            break;
        case k_statementKindBreak:
            printf("break;\n");
            break;
        case k_statementKindContinue:
            printf("continue;\n");
            break;
        case k_statementKindSimple:
            prettyPrint(node->val.stmt.type.stmtSimple.simple);
            printf(";");
            break;
        case k_statementKindIncrement:
            prettyPrint(node->val.stmt.type.stmtInc.expr);
            if (node->val.stmt.type.stmtInc.inc)
                printf("++");
            else
                printf("--");
            break;
        case k_statementKindAssign:
            prettyPrint(node->val.stmt.type.stmtAssign.LHS_expr_list);
            printf(" %s ", node->val.stmt.type.stmtAssign.assign_op);
            prettyPrint(node->val.stmt.type.stmtAssign.RHS_expr_list);
            break;
        case k_statementKindShortDcl:
            prettyPrint(node->val.stmt.type.stmtShortDcl.LHS_expr_list);
            printf(" := ");
            prettyPrint(node->val.stmt.type.stmtShortDcl.RHS_expr_list);
            break;
        case k_expressionArrayIndex:
            prettyPrint(node->val.expr.type.arrayIndex.expr);
            printf("[");
            prettyPrint(node->val.expr.type.arrayIndex.index);
            printf("]");
            //if (node->val.expr.next)
                //prettyPrint(node->val.expr.next);
            break;
        case k_expressionKindStructSelector:
            prettyPrint(node->val.expr.type.structSelector.expr);
            printf(".%s", node->val.expr.type.structSelector.identifier);
            //if (node->val.expr.next)
                //prettyPrint(node->val.expr.next);
            break;
        case k_expressionKindIdentifier:
            printf("%s", node->val.expr.type.identifier);
            break;
        case k_expressionKindIntLiteral:
            printf("%d", node->val.expr.type.intLiteral);
            break;
        case k_expressionKindFloatLiteral:
            printf("%f", node->val.expr.type.floatLiteral);
            break;
        case k_expressionKindStringLiteral:
            printf("%s", node->val.expr.type.stringLiteral.stringLiteral);
            break;
        case k_expressionKindRuneLiteral:
            printf("%s", node->val.expr.type.runeLiteral);
            break;
        case k_expressionKindPlus:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" + ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindMinus:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" - ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindMult:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" * ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindDiv:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" / ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindMod:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" %% ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindLT:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" < ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindLT_EQ:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" <= ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindGT:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" > ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindGT_EQ:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" >= ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindEQ_EQ:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" == ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindNotEquals:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" != ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindShift_Right:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" >> ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindShift_Left:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" << ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindAnd:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" & ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindAMP_XOR:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" %%^ ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindOr:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" | ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindXor:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" ^ ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindLogicalAnd:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" && ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindLogicalOr:
            printf("(");
            prettyPrint(node->val.expr.type.exp_binary.lhs);
            printf(" || ");
            prettyPrint(node->val.expr.type.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindNotUnary:
            printf("(!(");
            prettyPrint(node->val.expr.type.exp_unary);
            printf(")");
            break;
        case k_expressionKindPlusUnary:
            printf("(+(");
            prettyPrint(node->val.expr.type.exp_unary);
            printf(")");
            break;
        case k_expressionKindMinusUnary:
            printf("(-(");
            prettyPrint(node->val.expr.type.exp_unary);
            printf(")");
            break;
        case k_expressionKindXorUnary:
            printf("(^(");
            prettyPrint(node->val.expr.type.exp_unary);
            printf(")");
            break;
    }
}

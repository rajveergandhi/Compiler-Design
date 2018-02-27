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
            for (NODE *i = node; i->val.program.topLevelDecls != NULL; i = i->val.program.topLevelDecls->val.next) {
                prettyPrint(i->val.program.topLevelDecls);
            }
            break;
        case k_package:
            printf("package %s\n", node->val.package);
            break;
        case k_dcl_var:
            for (NODE *i = node; i != NULL; i = i->val.stmt.type.varDcl.next) 
            {
                printf("var ");
                prettyPrint(i->val.stmt.type.varDcl.idlist);
                if (i->val.stmt.type.varDcl.type) {
                    printf(" ");
                    prettyPrint(i->val.stmt.type.varDcl.type);
                }
                if (i->val.stmt.type.varDcl.expr_list) {
                    printf(" = ");
                    for (NODE *j = i->val.stmt.type.varDcl.expr_list; j != NULL; j = j->val.expr.next) {
                        prettyPrint(j);
                        if (j->val.expr.next != NULL) printf(", ");
                    }
                }
                printf("\n");
            }
            break;
        case k_idlist:
            for (NODE *i = node; i != NULL; i = i->val.idlist.next) {
                printf("%s", i->val.idlist.identifier);
                if (i->val.idlist.next != NULL) printf(", ");
            }
            break;
        case k_dcl_type:
            break;
        case k_array:
            break;
        case k_slice:
            break;
        case k_struct:
            break;
        case k_function:
            break;
        case k_function_signature:
            break;
        case k_function_params:
            break;
        case k_block:
            printf("{\n");
            if (node->val.stmt.type.block.stmts)
                prettyPrint(node->val.stmt.type.block.stmts);
            printf("\n}\n");
            break;
        case k_append:
            break;
        case k_function_call:
            if (node->val.expr.next)
                prettyPrint(node->val.expr.next);
            break;
        case k_statementKindPrint:
            break;
        case k_statementKindReturn:
            break;
        case k_statementKindIf:
            break;
        case k_statementKindFor:
            break;
        case k_statementKindForCond:
            break;
        case k_statementKindSwitch:
            break;
        case k_statementKindSwitchCondition:
            break;
        case k_statementKindSwitchCase:
            break;
        case k_statementKindBreak:
            printf("break;\n");
            break;
        case k_statementKindContinue:
            printf("continue;\n");
            break;
        case k_statementKindSimple:
            break;
        case k_statementKindIncrement:
            break;
        case k_statementKindAssign:
            break;
        case k_statementKindShortDcl:
            break;
        case k_expressionArrayIndex:
            if (node->val.expr.next)
                prettyPrint(node->val.expr.next);
            break;
        case k_expressionKindStructSelector:
            if (node->val.expr.next)
                prettyPrint(node->val.expr.next);
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
            break;
        case k_expressionKindRuneLiteral:
            break;
        case k_expressionKindPlus:
            break;
        case k_expressionKindMinus:
            break;
        case k_expressionKindMult:
            break;
        case k_expressionKindDiv:
            break;
        case k_expressionKindMod:
            break;
        case k_expressionKindLT:
            break;
        case k_expressionKindLT_EQ:
            break;
        case k_expressionKindGT:
            break;
        case k_expressionKindGT_EQ:
            break;
        case k_expressionKindEQ_EQ:
            break;
        case k_expressionKindNotEquals:
            break;
        case k_expressionKindShift_Right:
            break;
        case k_expressionKindShift_Left:
            break;
        case k_expressionKindAnd:
            break;
        case k_expressionKindAMP_XOR:
            break;
        case k_expressionKindOr:
            break;
        case k_expressionKindXor:
            break;
        case k_expressionKindLogicalAnd:
            break;
        case k_expressionKindLogicalOr:
            break;
        case k_expressionKindNot:
            break;

    /* assignment 2 code
        case k_program:
            if (node->val.program.dcls)
                prettyPrint(node->val.program.dcls);
            printf("\n");
            if (node->val.program.stmts)
                prettyPrint(node->val.program.stmts);
            break;
        case k_dcl:
            for (NODE *i = node; i != NULL; i = i->val.dcl.nextDcl) {
                printf("var %s: %s = ", i->val.dcl.identifier, i->val.dcl.type);
                prettyPrint(i->val.dcl.expr);
                printf(";\n");
            }
            break;
        case k_statementKindRead:
            prettyIndent(g_indent);
            printf("read %s;\n", node->val.stmt.type.stmtRead);
            if (node->val.stmt.nextStmt)
                prettyPrint(node->val.stmt.nextStmt);
            break;
        case k_statementKindPrint:
            prettyIndent(g_indent);
            printf("print ");
            prettyPrint(node->val.stmt.type.stmtPrint);
            printf(";\n");
            if (node->val.stmt.nextStmt)
                prettyPrint(node->val.stmt.nextStmt);
            break;
        case k_statementKindAssignment:
            prettyIndent(g_indent);
            printf("%s = ", node->val.stmt.type.stmtAssign.identifier);
            prettyPrint(node->val.stmt.type.stmtAssign.expr);
            printf(";\n");
            if (node->val.stmt.nextStmt)
                prettyPrint(node->val.stmt.nextStmt);
            break;
        case k_statementKindWhile:
            prettyIndent(g_indent);
            printf("while ");
            prettyPrint(node->val.stmt.type.stmtWhile.expr);
            printf(" {\n");
            g_indent++;
            if (node->val.stmt.type.stmtWhile.stmts)
                prettyPrint(node->val.stmt.type.stmtWhile.stmts);
            g_indent--;
            prettyIndent(g_indent);
            printf("}\n");
            if (node->val.stmt.nextStmt)
                prettyPrint(node->val.stmt.nextStmt);
            break;
        case k_statementKindIfStmt:
            prettyIndent(g_indent);
            printf("if ");
            prettyPrint(node->val.stmt.type.stmtIf.expr);
            printf(" {\n");
            g_indent++;
            if (node->val.stmt.type.stmtIf.stmts)
                prettyPrint(node->val.stmt.type.stmtIf.stmts);
            g_indent--;
            prettyIndent(g_indent);
            printf("}\n");
            if (node->val.stmt.nextStmt)
                prettyPrint(node->val.stmt.nextStmt);
            break;
        case k_statementKindIfElseStmt:
            prettyIndent(g_indent);
            printf("if ");
            prettyPrint(node->val.stmt.type.stmtIfElse.expr);
            printf(" {\n");
            g_indent++;
            if (node->val.stmt.type.stmtIfElse.ifStmts)
                prettyPrint(node->val.stmt.type.stmtIfElse.ifStmts);
            g_indent--;
            prettyIndent(g_indent);
            printf("} else {\n");
            g_indent++;
            if (node->val.stmt.type.stmtIfElse.elseStmts)
                prettyPrint(node->val.stmt.type.stmtIfElse.elseStmts);
            g_indent--;
            prettyIndent(g_indent);
            printf("}\n");
            if (node->val.stmt.nextStmt)
                prettyPrint(node->val.stmt.nextStmt);
            break;
        case k_expressionKindIdentifier:
            printf("%s", node->val.identifier);
            break;
        case k_expressionKindIntLiteral:
            printf("%d", node->val.intLiteral);
            break;
        case k_expressionKindFloatLiteral:
            printf("%f", node->val.floatLiteral);
            break;
        case k_expressionKindBoolLiteral:
            printf("%d", node->val.boolLiteral);
            break;
        case k_expressionKindStringLiteral:
            printf("%s", node->val.stringLiteral);
            break;
        case k_expressionKindAddition:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" + ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindSubtraction:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" - ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindMultiplication:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" * ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindDivision:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" / ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindEqualsEquals:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" == ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindNotEquals:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" != ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindLogicalAnd:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" && ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindLogicalOr:
            printf("(");
            prettyPrint(node->val.exp_binary.lhs);
            printf(" || ");
            prettyPrint(node->val.exp_binary.rhs);
            printf(")");
            break;
        case k_expressionKindNot:
            printf("!(");
            prettyPrint(node->val.exp_unary);
            printf(")");
            break;
        case k_expressionKindUnaryMinus:
            printf("-(");
            prettyPrint(node->val.exp_unary);
            printf(")");
            break;
    */
    }
}

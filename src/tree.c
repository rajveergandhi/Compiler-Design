#include <stdlib.h>
#include "tree.h"

extern int yylineno;

NODE *makePROGRAM(NODE *package, NODE *topLevelDecls) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_program;
    node->val.program.package = package;
    node->val.program.topLevelDecls = topLevelDecls;
    return node;
}

NODE *makePACKAGE(char *package) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_package;
    node->val.identifier = package;
    return node;
}

NODE *makeTOPLEVELDECLS(NODE *topLevelDecls, NODE *topLevelDecl) {
    // make a linked list structure so that each declaration points to the next
    if (topLevelDecls)
        topLevelDecl->val.topLevelDecl.next = topLevelDecls;
    return topLevelDecl;
}

/*
NODE *makeDCLS(NODE *dcl, NODE *dcls) {
    // make a linked list structure so that each declaration points to the next
    if (dcls)
        dcl->val.dcl.nextDcl = dcls;
    return dcl;
}

NODE *makeDCL(char *identifier, char *type, NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_dcl;
    node->val.dcl.identifier = identifier;
    node->val.dcl.type = type;
    node->val.dcl.expr = expr;
    node->val.dcl.nextDcl = NULL;
    return node;
}

NODE *makeSTMTS(NODE *stmt, NODE *stmts) {
    // make a linked list structure so that each statement points to the next
    if (stmts)
        stmt->val.stmt.nextStmt = stmts;
    return stmt;
}

NODE *makeSTATEMENT_read(char *identifier) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindRead;
    node->val.stmt.type.stmtRead = identifier;
    node->val.stmt.nextStmt = NULL;
    return node;
}

NODE *makeSTATEMENT_print(NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindPrint;
    node->val.stmt.type.stmtPrint = expr;
    node->val.stmt.nextStmt = NULL;
    return node;
}

NODE *makeSTATEMENT_assign(char *identifier, NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindAssignment;
    node->val.stmt.type.stmtAssign.identifier = identifier;
    node->val.stmt.type.stmtAssign.expr = expr;
    node->val.stmt.nextStmt = NULL;
    return node;
}

NODE *makeSTATEMENT_while(NODE *expr, NODE *stmts) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindWhile;
    node->val.stmt.type.stmtWhile.expr = expr;
    node->val.stmt.type.stmtWhile.stmts = stmts;
    node->val.stmt.nextStmt = NULL;
    return node;
}

NODE *makeSTATEMENT_if(NODE *expr, NODE *stmts) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindIfStmt;
    node->val.stmt.type.stmtIf.expr = expr;
    node->val.stmt.type.stmtIf.stmts = stmts;
    node->val.stmt.nextStmt = NULL;
    return node;
}

NODE *makeSTATEMENT_ifElse(NODE *expr, NODE *ifStmts, NODE *elseStmts) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindIfElseStmt;
    node->val.stmt.type.stmtIfElse.expr = expr;
    node->val.stmt.type.stmtIfElse.ifStmts = ifStmts;
    node->val.stmt.type.stmtIfElse.elseStmts = elseStmts;
    node->val.stmt.nextStmt = NULL;
    return node;
}

NODE *makeEXP_identifier(char *identifier) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindIdentifier;
    node->val.identifier = identifier;
    return node;
}

NODE *makeEXP_intLiteral(int intLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindIntLiteral;
    node->val.intLiteral = intLiteral;
    return node;
}

NODE *makeEXP_floatLiteral(float floatLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindFloatLiteral;
    node->val.floatLiteral = floatLiteral;
    return node;
}

NODE *makeEXP_boolLiteral(bool boolLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindBoolLiteral;
    node->val.boolLiteral = boolLiteral;
    return node;
}

NODE *makeEXP_stringLiteral(char *stringLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindStringLiteral;
    node->val.stringLiteral = stringLiteral;
    return node;
}

NODE *makeEXP_binary(Kind op, NODE *lhs, NODE *rhs) {
    // binary expressions: addition, subtraction, multiplication, division, equalsequals, notequals, logical and, logical or
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = op;
    node->val.exp_binary.lhs = lhs;
    node->val.exp_binary.rhs = rhs;
    return node;
}

NODE *makeEXP_not(NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindNot;
    node->val.exp_unary = expr;
    return node;
}

NODE *makeEXP_unaryminus(NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindUnaryMinus;
    node->val.exp_unary = expr;
    return node;
}
*/

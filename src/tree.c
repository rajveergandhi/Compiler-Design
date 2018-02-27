#include <stdlib.h>
#include <stdio.h> // for debugging
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
    node->val.package = package;
    return node;
}

NODE *makeTOPLEVELDECLS(NODE *topLevelDecl, NODE *topLevelDecls) {
    // make a linked list structure so that each item points to the next
    if (topLevelDecls)
        topLevelDecl->val.toplevel.next = topLevelDecls;
    return topLevelDecl;
}

NODE *makeDCL_var(NODE *idlist, NODE *type, NODE *expr_list) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_dcl_var;
    node->val.toplevel.type.varDcl.idlist = idlist;
    node->val.toplevel.type.varDcl.type = type;
    node->val.toplevel.type.varDcl.expr_list = expr_list;
    return node;
}

NODE *makeDCL_vars(NODE *varDcl, NODE *varDcls) {
    // make a linked list structure so that each item points to the next
    if (varDcls)
        varDcl->val.toplevel.type.varDcl.next = varDcls;
    return varDcl;
}

NODE *makeIDLIST(char *id, NODE *nextId) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_idlist;
    node->val.toplevel.type.idlist.identifier = id;
    node->val.toplevel.type.idlist.next = nextId;
    return node;
}

NODE *makeDCL_type(char *identifier, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_dcl_type;
    node->val.toplevel.type.typeDcl.identifier = identifier;
    node->val.toplevel.type.typeDcl.type = type;
    node->val.toplevel.type.typeDcl.next = NULL;
    return node;
}

NODE *makeDCL_types(NODE *type, NODE *types) {
    // make a linked list structure so that each item points to the next
    if (types)
        type->val.toplevel.type.typeDcl.next = types;
    return type;
}

NODE *makeSlice(NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_slice;
    node->val.typeSlice.type = type;
    return node;
}

NODE *makeArray(int intval, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_array;
    node->val.typeArray.intval = intval;
    node->val.typeArray.type = type;
    return node;
}

NODE *makeStruct(NODE *idlist, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_struct;
    node->val.typeStruct.idlist = idlist;
    node->val.typeStruct.type = type;
    return node;
}

NODE *makeStruct_members(NODE *member, NODE *members) {
    // make a linked list structure so that each item points to the next
    if (members)
        member->val.typeStruct.next = members;
    return member;
}

NODE *makeFUNCTION(char *identifier, NODE *signature, NODE *block) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function;
    node->val.toplevel.type.funcDcl.identifier = identifier;
    node->val.toplevel.type.funcDcl.signature = signature;
    node->val.toplevel.type.funcDcl.block = block;
    return node;
}

NODE *makeFUNCTION_signature(NODE *params, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function_signature;
    node->val.funcSign.params = params;
    node->val.funcSign.type = type;
    return node;
}

NODE *makeFUNCTION_parameterList(NODE *idlist, NODE *type, NODE *param_list) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function_params;
    node->val.funcParams.param_list = param_list;
    node->val.funcParams.idlist = idlist;
    node->val.funcParams.type = type;
    return node;
}

NODE *makeBLOCK(NODE *statements) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_block;
    node->val.stmt.type.block.stmts = statements;
    return node;
}

NODE *makeSTATEMENTS(NODE *stmt, NODE *stmts) {
    // make a linked list structure so that each item points to the next
    if (stmts)
        stmt->val.stmt.next = stmts;
    return stmt;
}

NODE *makeSTATEMENT_print(NODE *expr_list, bool println) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindPrint;
    node->val.stmt.type.print.expr_list = expr_list;
    node->val.stmt.type.print.println = println;
    return node;
}

NODE *makeSTATEMENT_return(NODE *stmtReturn) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindReturn;
    node->val.stmt.type.stmtReturn.expr = stmtReturn;
    return node;
}

NODE *makeSTATEMENT_if(NODE *simple, NODE *expr, NODE *stmts, NODE *elseBlock) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindIf;
    node->val.stmt.type.stmtIf.simple = simple;
    node->val.stmt.type.stmtIf.expr = expr;
    node->val.stmt.type.stmtIf.stmts = stmts;
    node->val.stmt.type.stmtIf.elseBlock = elseBlock;
    return node;
}

NODE *makeSTATEMENT_for(NODE *condition, NODE *block) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindFor;
    node->val.stmt.type.stmtFor.condition = condition;
    node->val.stmt.type.stmtFor.block = block;
    return node;
}

NODE *makeSTATEMENT_forCondition(NODE *part1, NODE *part2, NODE *part3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindForCond;
    node->val.stmtForCondition.part1 = part1;
    node->val.stmtForCondition.part2 = part2;
    node->val.stmtForCondition.part3 = part3;
    return node;
}

NODE *makeSTATEMENT_switch(NODE *condition, NODE *caselist) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindSwitch;
    node->val.stmt.type.stmtSwitch.condition = condition;
    node->val.stmt.type.stmtSwitch.caselist = caselist;
    return node;
}

NODE *makeSTATEMENT_switchCondition(NODE *simple, NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindSwitchCondition;
    node->val.stmtSwitchCondition.simple = simple;
    node->val.stmtSwitchCondition.expr = expr;
    return node;
}

NODE *makeSTATEMENT_switchCases(NODE *givenCase, NODE *cases) {
    // make a linked list structure so that each item points to the next
    if (cases)
        givenCase->val.stmtSwitchCase.next = cases;
    return givenCase;
}

NODE *makeSTATEMENT_switchCase(NODE *expr_list, NODE *statement_list) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindSwitchCase;
    node->val.stmtSwitchCase.expr_list = expr_list;
    node->val.stmtSwitchCase.statement_list = statement_list;
    return node;
}

NODE *makeSTATEMENT_break() {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindBreak;
    return node;
}

NODE *makeSTATEMENT_continue() {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindContinue;
    return node;
}

NODE *makeSTATEMENT_simple(NODE *simple) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindSimple;
    node->val.stmt.type.stmtSimple.simple = simple;
    return node;
}

NODE *makeSTATEMENT_simpleIncrement(NODE *expr, bool inc) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindIncrement;
    node->val.stmt.type.stmtInc.expr = expr;
    node->val.stmt.type.stmtInc.inc = inc;
    return node;
}

NODE *makeSTATEMENT_assign(NODE *LHS_expr_list, char *assign_op, NODE *RHS_expr_list) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindAssign;
    node->val.stmt.type.stmtAssign.LHS_expr_list = LHS_expr_list;
    node->val.stmt.type.stmtAssign.assign_op = assign_op;
    node->val.stmt.type.stmtAssign.RHS_expr_list = RHS_expr_list;
    return node;
}

NODE *makeSTATEMENT_shortDcl(NODE *LHS_expr_list, NODE *RHS_expr_list) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindShortDcl;
    node->val.stmt.type.stmtShortDcl.LHS_expr_list = LHS_expr_list;
    node->val.stmt.type.stmtShortDcl.RHS_expr_list = RHS_expr_list;
    return node;
}

NODE *makeEXPRLIST(NODE *expr, NODE *expr_list) {
    // make a linked list structure so that each item points to the next
    if (expr_list)
        expr->val.expr.next = expr_list;
    return expr;
}

NODE *makeEXP_binary(Kind op, NODE *lhs, NODE *rhs) {
    // all binary expressions
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = op;
    node->val.expr.type.exp_binary.lhs = lhs;
    node->val.expr.type.exp_binary.rhs = rhs;
    return node;
}

NODE *makeEXP_unary(Kind op, NODE *expr) {
    // all unary expressions
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = op;
    node->val.expr.type.exp_unary = expr;
    return node;
}

NODE *makeAPPEND(char *identifier, NODE *expr) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_append;
    node->val.expr.type.expr_append.identifier = identifier;
    node->val.expr.type.expr_append.expr = expr;
    return node;
}

NODE *makeEXPRESSION_arrayIndex(NODE *expr, NODE *index) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionArrayIndex;
    node->val.expr.type.arrayIndex.expr = expr;
    node->val.expr.type.arrayIndex.index = index;
    return node;
}

NODE *makeEXPRESSION_structSelector(NODE *expr, char *identifier) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindStructSelector;
    node->val.expr.type.structSelector.expr = expr;
    node->val.expr.type.structSelector.identifier = identifier;
    return node;
}

NODE *makeEXP_identifier(char *identifier) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindIdentifier;
    node->val.expr.type.identifier = identifier;
    return node;
}

NODE *makeEXP_intLiteral(int intLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindIntLiteral;
    node->val.expr.type.intLiteral = intLiteral;
    return node;
}

NODE *makeEXP_floatLiteral(float floatLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindFloatLiteral;
    node->val.expr.type.floatLiteral = floatLiteral;
    return node;
}

NODE *makeEXP_stringLiteral(char *stringLiteral, bool interpreted) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindStringLiteral;
    node->val.expr.type.stringLiteral.stringLiteral = stringLiteral;
    node->val.expr.type.stringLiteral.interpreted = interpreted;
    return node;
}

NODE *makeEXP_runeLiteral(char *runeLiteral) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_expressionKindRuneLiteral;
    node->val.expr.type.runeLiteral = runeLiteral;
    return node;
}

NODE *makeFUNCTIONCALL(NODE *id, NODE *args) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function_call;
    node->val.expr.type.funcCall.id = id;
    node->val.expr.type.funcCall.args = args;
    return node;
}

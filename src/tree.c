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
    // make a linked list structure so that each item points to the next
    if (topLevelDecls)
        topLevelDecl->val.topLevelDecl.next = topLevelDecls;
    return topLevelDecl;
}

NODE *makeDCL_var(NODE *idlist, NODE *type, NODE *expr_list) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_dcl_var;
    node->val.varDcl.idlist = idlist;
    node->val.varDcl.type = type;
    node->val.varDcl.expr_list = expr_list;
    return node;
}
NODE *makeDCL_vars(NODE *varDcls, NODE *varDcl) {
    // make a linked list structure so that each item points to the next
    if (varDcls)
        varDcl->val.varDcl.next = varDcls;
    return varDcl;
}

NODE *makeIDLIST(char *id, NODE *nextId) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_idlist;
    node->val.idlist.identifier = id;
    node->val.idlist.next = nextId;
    return node;
}

NODE *makeDCL_type(char *identifier, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_dcl_type;
    node->val.varType.identifier = identifier;
    node->val.varType.type = type;
    return node;
}

NODE *makeDCL_types(NODE *typeDclList, NODE *typeDcl) {
    // make a linked list structure so that each item points to the next
    if (typeDclList)
        typeDcl->val.varType.next = typeDclList;
    return typeDcl;
}

NODE *makeEXP_identifier(char *identifier) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_identifier;
    node->val.identifier = identifier;
    return node;
}

NODE *makeArray(NODE *intval, NODE *type) {
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
NODE *makeStruct_members(NODE *members, NODE *member) {
    // make a linked list structure so that each item points to the next
    if (members)
        member->val.typeStruct.next = members;
    return member;
}

NODE *makeFUNCTION(char *identifier, NODE *signature, NODE *block) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function;
    node->val.typeFunction.identifier = identifier;
    node->val.typeFunction.signature = signature;
    node->val.typeFunction.block = block;
    return node;
}
NODE *makeFUNCTION_signature(NODE *params, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function_signature;
    node->val.func_sign.params = params;
    node->val.func_sign.type = type;
    return node;
}

NODE *makeFUNCTION_parameterList(NODE *param_list, NODE *idlist, NODE *type) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_function_params;
    node->val.func_params.param_list = param_list;
    node->val.func_params.idlist = idlist;
    node->val.func_params.type = type;
    return node;
}

NODE *makeBLOCK(NODE *statements) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_block;
    node->val.statements = statements;
    return node;
}

NODE *makeSTATEMENTS(NODE *stmts, NODE *stmt) {
    // make a linked list structure so that each item points to the next
    if (stmts)
        stmt->val.stmt.next = stmts;
    return stmt;
}

// add this to tree.h: bool println is true iff println was called
NODE *makeSTATEMENT_print(NODE *expr_list, bool println) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = k_statementKindPrint;
    node->val.stmt.print.expr_list = expr_list;
    node->val.stmt.print.println = println;
    return node;
}

NODE *makeSTATEMENT_return(NODE *return) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_if($2, $3, $4, NULL) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_for($2, $3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_forCondition($1, $3, $5) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_switch($2, $3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_switchCondition($1, NULL) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_switchCases($1, $2) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_switchCase($2, $4) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_break() {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_continue() {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_simple($1) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_simpleIncrement($1, true) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_assign($1, $2, $3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeSTATEMENT_shortDcl($1, $3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXPRLIST($1, $3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_binary(k_expressionKindPlus, $1, $3) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_unary($1, $2) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeAPPEND($3, $5) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXPRESSION_arrayIndex($1, $2) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXPRESSION_structSelector($1, $2) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_identifier($1) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_intLiteral($1) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_floatLiteral($1) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_stringLiteral($1, true) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_stringLiteral($1, false) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeEXP_runeLiteral($1) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}

NODE *makeFUNCTIONCALL($1, $2) {
    NODE *node = malloc(sizeof(NODE));
    node->lineno = yylineno;
    node->kind = 
    node->val.
    return node;
}


/*
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

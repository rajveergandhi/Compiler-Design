#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

extern int yylineno;

PROGRAM *makePROGRAM(PACKAGE *package, TOPLEVELDECL *topleveldecls) {
    PROGRAM *node = malloc(sizeof(PROGRAM));
    node->lineno = yylineno;
    node->package = package;
    node->topleveldecls = topleveldecls;
    return node;
}

PACKAGE *makePACKAGE(char *package) {
    PACKAGE *node = malloc(sizeof(PACKAGE));
    node->lineno = yylineno;
    node->package = package;
    return node;
}

TOPLEVELDECL *makeTOPLEVELDECLS(TOPLEVELDECL *current, TOPLEVELDECL *next) {
    if (next)
        current->next = next;
    return current;
}

TOPLEVELDECL *makeTOPLEVELDECL_dcl(DCL *dcl) {
    TOPLEVELDECL *node = malloc(sizeof(TOPLEVELDECL)); 
    node->lineno = yylineno;
    node->kind = dcl_toplevel;
    node->val.dcl = dcl;
    return node;
}

TOPLEVELDECL *makeTOPLEVELDECL_funcdcl(FUNCDCL *funcdcl) {
    TOPLEVELDECL *node = malloc(sizeof(TOPLEVELDECL)); 
    node->lineno = yylineno;
    node->kind = func_dcl_toplevel;
    node->val.funcdcl = funcdcl;
    return node;
}

DCL *makeDCLTYPE_var(VARDCL *vardcl) {
    DCL *node = malloc(sizeof(DCL)); 
    node->lineno = yylineno;
    node->kind = var;
    node->val.vardcl = vardcl;
    return node;
}

DCL *makeDCLTYPE_type(TYPEDCL *typedcl) {
    DCL *node = malloc(sizeof(DCL)); 
    node->lineno = yylineno;
    node->kind = type;
    node->val.typedcl = typedcl;
    return node;
}
VARDCL *makeDCL_var(IDLIST *idlist, TYPE *type, EXPRLIST *exprlist) {
    VARDCL *node = malloc(sizeof(VARDCL)); 
    node->lineno = yylineno;
    node->idlist = idlist;
    node->type = type;
    node->exprlist = exprlist;
    return node;
}

VARDCL *makeDCL_vars(VARDCL *current, VARDCL *next) {
    if (next)
        current->next = next;
    return current;
}

TYPEDCL *makeDCL_type(char *identifier, TYPE *type) {
    TYPEDCL *node = malloc(sizeof(TYPEDCL)); 
    node->lineno = yylineno;
    node->identifier = identifier;
    node->type = type;
    return node;
}
TYPEDCL *makeDCL_types(TYPEDCL *current, TYPEDCL *next) {
    if (next)
        current->next = next;
    return current;
}

TYPE *makeTYPE_identifier(char *identifier) {
    TYPE *node = malloc(sizeof(TYPE)); 
    node->lineno = yylineno;
    node->kind = basic_type_kind;
    node->val.basic_type = identifier;
    return node;
}

TYPE *makeTYPE_slice(TYPE *slice_type) {
    TYPE *node = malloc(sizeof(TYPE)); 
    node->lineno = yylineno;
    node->kind = slice_type_kind;
    node->val.slice_type = slice_type;
    return node;
}

TYPE *makeTYPE_array(int size, TYPE *type) {
    TYPE *node = malloc(sizeof(TYPE)); 
    node->lineno = yylineno;
    node->kind = array_type_kind;
    node->val.array_type.size = size;
    node->val.array_type.type = type;
    return node;
}

TYPE *makeTYPE_struct(STRUCT_TYPE *struct_type) {
    TYPE *node = malloc(sizeof(TYPE)); 
    node->lineno = yylineno;
    node->kind = struct_type_kind;
    node->val.struct_type = struct_type;
    return node;
}

STRUCT_TYPE *makeSTRUCT(IDLIST *idlist, TYPE *type) {
    STRUCT_TYPE *node = malloc(sizeof(STRUCT_TYPE)); 
    node->lineno = yylineno;
    node->idlist = idlist;
    node->type = type;
    return node;
}

STRUCT_TYPE *makeSTRUCTS(STRUCT_TYPE *current, STRUCT_TYPE *next) {
    if (next)
        current->next = next;
    return current;
}

FUNCDCL *makeFUNCTION(char *identifier, FUNC_SIGNATURE *signature, BLOCK *block) {
    FUNCDCL *node = malloc(sizeof(FUNCDCL)); 
    node->lineno = yylineno;
    node->identifier = identifier;
    node->signature = signature;
    node->block = block;
    return node;
}

FUNC_SIGNATURE *makeFUNCTION_signature(PARAM_LIST *params, TYPE *type) {
    FUNC_SIGNATURE *node = malloc(sizeof(FUNC_SIGNATURE)); 
    node->lineno = yylineno;
    node->params = params;
    node->type = type;
    return node;
}

PARAM_LIST *makeFUNCTION_parameterList(IDLIST *idlist, TYPE *type, PARAM_LIST *next) {
    PARAM_LIST *node = malloc(sizeof(PARAM_LIST)); 
    node->lineno = yylineno;
    node->idlist = idlist;
    node->type = type;
    node->next = next;
    return node;
}

IDLIST *makeIDLIST(char *id, IDLIST *next) {
    IDLIST *node = malloc(sizeof(IDLIST)); 
    node->lineno = yylineno;
    node->id = id;
    node->next = next;
    return node;
}

BLOCK *makeBLOCK(STATEMENTS *stmts) {
    BLOCK *node = malloc(sizeof(BLOCK)); 
    node->lineno = yylineno;
    node->stmts = stmts;
    return node;
}

STATEMENTS *makeSTATEMENTS(STATEMENT *stmt, STATEMENTS *next) {
    STATEMENTS *node = malloc(sizeof(STATEMENTS)); 
    node->lineno = yylineno;
    node->stmt = stmt;
    node->next = next;
    return node;
}

STATEMENT *makeSTATEMENT_print(EXPRLIST *print) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = print_stmt_s;
    node->val.print = print;
    return node;
}

STATEMENT *makeSTATEMENT_println(EXPRLIST *print) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = println_stmt_s;
    node->val.print = print;
    return node;
}

STATEMENT *makeSTATEMENT_return(EXPR *return_stmt) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = return_stmt_s;
    node->val.return_stmt = return_stmt;
    return node;
}

STATEMENT *makeSTATEMENT_if(SIMPLE *simple, EXPR *expr, BLOCK *block) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = if_stmt_s;
    node->val.if_stmt.simple = simple;
    node->val.if_stmt.expr = expr;
    node->val.if_stmt.kind_else = no_else;
    node->val.if_stmt.val.if_block = block;
    return node;
}

STATEMENT *makeSTATEMENT_ifElse(SIMPLE *simple, EXPR *expr, STATEMENTS *stmts, ELSE_BLOCK *else_block) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = if_stmt_s;
    node->val.if_stmt.simple = simple;
    node->val.if_stmt.expr = expr;
    node->val.if_stmt.kind_else = else_if;
    node->val.if_stmt.val.else_block.stmts = stmts;
    node->val.if_stmt.val.else_block.else_block = else_block;
    return node;
}

ELSE_BLOCK *makeELSEBLOCK_block(BLOCK *block) {
    ELSE_BLOCK *node = malloc(sizeof(ELSE_BLOCK)); 
    node->lineno = yylineno;
    node->kind = block_else;
    node->val.block = block;
    return node;
}

ELSE_BLOCK *makeELSEBLOCK_if(STATEMENT *if_stmt) {
    ELSE_BLOCK *node = malloc(sizeof(ELSE_BLOCK)); 
    node->lineno = yylineno;
    node->kind = if_stmt_else;
    node->val.if_stmt = if_stmt;
    return node;
}

STATEMENT *makeSTATEMENT_for(FOR_CONDITION *condition, BLOCK *block) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = for_stmt_s;
    node->val.for_stmt.condition = condition;
    node->val.for_stmt.block = block;
    return node;
}

FOR_CONDITION *makeSTATEMENT_forCondition_infinite() {
    FOR_CONDITION *node = malloc(sizeof(FOR_CONDITION)); 
    node->lineno = yylineno;
    node->kind = infinite;
    return node;
}

FOR_CONDITION *makeSTATEMENT_forCondition_while(EXPR *while_expr) {
    FOR_CONDITION *node = malloc(sizeof(FOR_CONDITION)); 
    node->lineno = yylineno;
    node->kind = while_loop;
    node->val.while_expr = while_expr;
    return node;
}

FOR_CONDITION *makeSTATEMENT_forCondition_threepart(SIMPLE *init, EXPR *condition, SIMPLE *post) {
    FOR_CONDITION *node = malloc(sizeof(FOR_CONDITION)); 
    node->lineno = yylineno;
    node->kind = threepart;
    node->val.threepart.init = init;
    node->val.threepart.condition = condition;
    node->val.threepart.post = post;
    return node;
}

STATEMENT *makeSTATEMENT_switch(SWITCH_CONDITION *condition, SWITCH_CASELIST *caselist) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = switch_stmt_s;
    node->val.switch_stmt.condition = condition;
    node->val.switch_stmt.caselist = caselist;
    return node;
}

SWITCH_CONDITION *makeSTATEMENT_switchCondition(SIMPLE *simple, EXPR *expr) {
    SWITCH_CONDITION *node = malloc(sizeof(SWITCH_CONDITION)); 
    node->lineno = yylineno;
    node->simple = simple;
    node->expr = expr;
    return node;
}

SWITCH_CASELIST *makeSTATEMENT_switchCase(EXPRLIST *exprlist, STATEMENTS *statements) {
    SWITCH_CASELIST *node = malloc(sizeof(SWITCH_CASELIST)); 
    node->lineno = yylineno;
    node->default_case = false;
    node->exprlist = exprlist;
    node->statements = statements;
    return node;
}

SWITCH_CASELIST *makeSTATEMENT_switchCaseDefault(STATEMENTS *statements) {
    SWITCH_CASELIST *node = malloc(sizeof(SWITCH_CASELIST)); 
    node->lineno = yylineno;
    node->default_case = true;
    node->statements = statements;
    return node;
}

SWITCH_CASELIST *makeSTATEMENT_switchCases(SWITCH_CASELIST *current, SWITCH_CASELIST *next) {
    if (next)
        current->next = next;
    return current;
}

STATEMENT *makeSTATEMENT_break() {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = break_stmt_s;
    return node;
}

STATEMENT *makeSTATEMENT_continue() {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = continue_stmt_s;
    return node;
}

STATEMENT *makeSTATEMENT_block(BLOCK *block) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = block_s;
    node->val.block = block;
    return node;
}

STATEMENT *makeSTATEMENT_dcl(DCL *dcl) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = dcl_s;
    node->val.dcl = dcl;
    return node;
}

STATEMENT *makeSTATEMENT_simple(SIMPLE *simple) {
    STATEMENT *node = malloc(sizeof(STATEMENT)); 
    node->lineno = yylineno;
    node->kind = simple_s;
    node->val.simple = simple;
    return node;
}

SIMPLE *makeSIMPLE_expr(EXPR *expr) {
    SIMPLE *node = malloc(sizeof(SIMPLE)); 
    node->lineno = yylineno;
    node->kind = expr_kind;
    node->val.expr = expr;
    return node;
}

SIMPLE *makeSIMPLE_inc(EXPR *expr) {
    SIMPLE *node = malloc(sizeof(SIMPLE)); 
    node->lineno = yylineno;
    node->kind = increment_kind;
    node->val.expr = expr;
    return node;
}

SIMPLE *makeSIMPLE_dec(EXPR *expr) {
    SIMPLE *node = malloc(sizeof(SIMPLE)); 
    node->lineno = yylineno;
    node->kind = decrement_kind;
    node->val.expr = expr;
    return node;
}

SIMPLE *makeSIMPLE_assignment(EXPRLIST *LHS_expr_list, char *assign_op, EXPRLIST *RHS_expr_list) {
    SIMPLE *node = malloc(sizeof(SIMPLE)); 
    node->lineno = yylineno;
    node->kind = assignment_kind;
    node->val.assignment.LHS_expr_list = LHS_expr_list;
    node->val.assignment.assign_op = assign_op;
    node->val.assignment.RHS_expr_list = RHS_expr_list;
    return node;
}

SIMPLE *makeSIMPLE_OPassignment(EXPR *LHS_expr, char *assign_op, EXPR *RHS_expr) {
    SIMPLE *node = malloc(sizeof(SIMPLE));
    node->lineno = yylineno;
    node->kind = assignment_kind;
    EXPRLIST *lhs = malloc(sizeof(EXPRLIST));
    lhs->expr = LHS_expr;
    lhs->lineno = yylineno;
    lhs->next = NULL;
    EXPRLIST *rhs = malloc(sizeof(EXPRLIST));
    rhs->expr = RHS_expr;
    rhs->lineno = yylineno;
    rhs->next = NULL;
    node->val.assignment.LHS_expr_list = lhs;
    node->val.assignment.assign_op = assign_op;
    node->val.assignment.RHS_expr_list = rhs;
    return node;
}

SIMPLE *makeSIMPLE_shortdcl(EXPRLIST *LHS_idlist, EXPRLIST *RHS_expr_list) {
    SIMPLE *node = malloc(sizeof(SIMPLE)); 
    node->lineno = yylineno;
    node->kind = shortDcl_kind;
    node->val.shortDcl.LHS_idlist = LHS_idlist;
    node->val.shortDcl.RHS_expr_list = RHS_expr_list;
    return node;
}

SIMPLE *makeSIMPLE_empty() {
    SIMPLE *node = malloc(sizeof(SIMPLE)); 
    node->lineno = yylineno;
    node->kind = empty_stmt_kind;
    return node;
}

EXPRLIST *makeEXPRLIST(EXPR *expr, EXPRLIST *next) {
    EXPRLIST *node = malloc(sizeof(EXPRLIST)); 
    node->lineno = yylineno;
    node->expr = expr;
    node->next = next;
    return node;
}

EXPR *makeEXPR_binary(exprKind kind, EXPR *lhs, EXPR *rhs) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = kind;
    node->val.binary.lhs = lhs;
    node->val.binary.rhs = rhs;
    return node;
}

EXPR *makeEXPR_unary(exprKind kind, EXPR *expr_unary) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = kind;
    node->val.expr_unary = expr_unary;
    return node;
}

EXPR *makeEXPR_append(char *identifier, EXPR *expr) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = append_expr;
    node->val.append_expr.identifier = identifier;
    node->val.append_expr.expr = expr;
    return node;
}

EXPR *makeEXPR_intLiteral(int intLiteral) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = intval;
    node->val.intLiteral = intLiteral;
    return node;
}

EXPR *makeEXPR_floatLiteral(float floatLiteral) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = floatval;
    node->val.floatLiteral = floatLiteral;
    return node;
}

EXPR *makeEXPR_stringLiteral(char *stringLiteral, bool interpreted) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = interpreted ? stringval : rawstringval;
    node->val.stringLiteral = stringLiteral;
    return node;
}

EXPR *makeEXPR_runeLiteral(char *runeLiteral) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = runeval;
    node->val.runeLiteral = runeLiteral;
    return node;
}

EXPR *makeEXPR_other(OTHER_EXPR *other_expr) {
    EXPR *node = malloc(sizeof(EXPR)); 
    node->lineno = yylineno;
    node->kind = other_expr_kind;
    node->val.other_expr = other_expr;
    return node;
}

OTHER_EXPR *makeEXPR_identifier(char *identifier) {
    OTHER_EXPR *node = malloc(sizeof(OTHER_EXPR)); 
    node->lineno = yylineno;
    node->kind = identifier_kind;
    node->val.identifier = identifier;
    return node;
}

OTHER_EXPR *makeEXPR_paren(EXPR *expr) {
    OTHER_EXPR *node = malloc(sizeof(OTHER_EXPR)); 
    node->lineno = yylineno;
    node->kind = paren_kind;
    node->val.expr = expr;
    return node;
}

OTHER_EXPR *makeEXPR_funcCall(OTHER_EXPR *id, EXPRLIST *args) {
    OTHER_EXPR *node = malloc(sizeof(OTHER_EXPR)); 
    node->lineno = yylineno;
    node->kind = func_call_kind;
    node->val.func_call.id = id;
    node->val.func_call.args = args;
    return node;
}

OTHER_EXPR *makeEXPR_index(OTHER_EXPR *expr, EXPR *index) {
    OTHER_EXPR *node = malloc(sizeof(OTHER_EXPR)); 
    node->lineno = yylineno;
    node->kind = index_kind;
    node->val.index.expr = expr;
    node->val.index.index = index;
    return node;
}

OTHER_EXPR *makeEXPR_structAccess(OTHER_EXPR *expr, char *identifier) {
    OTHER_EXPR *node = malloc(sizeof(OTHER_EXPR)); 
    node->lineno = yylineno;
    node->kind = struct_access_kind;
    node->val.struct_access.expr = expr;
    node->val.struct_access.identifier = identifier;
    return node;
}

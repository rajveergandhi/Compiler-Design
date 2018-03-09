#ifndef TREE_H
#define TREE_H

#include <stdbool.h>


// forward declarations
typedef struct SymbolTable SymbolTable;
typedef struct PROGRAM PROGRAM;
typedef struct PACKAGE PACKAGE;
typedef struct TOPLEVELDECL TOPLEVELDECL;
typedef struct DCL DCL;
typedef struct VARDCL VARDCL;
typedef struct TYPEDCL TYPEDCL;
typedef struct FUNCDCL FUNCDCL;
typedef struct FUNC_SIGNATURE FUNC_SIGNATURE;
typedef struct PARAM_LIST PARAM_LIST;
typedef struct IDLIST IDLIST;
typedef struct TYPE TYPE;
typedef struct STRUCT_TYPE STRUCT_TYPE;
typedef struct BLOCK BLOCK;
typedef struct STATEMENTS STATEMENTS;
typedef struct STATEMENT STATEMENT;
typedef struct ELSE_BLOCK ELSE_BLOCK;
typedef struct SWITCH_CONDITION SWITCH_CONDITION;
typedef struct SWITCH_CASELIST SWITCH_CASELIST;
typedef struct EXPRLIST EXPRLIST;
typedef struct FOR_CONDITION FOR_CONDITION;
typedef struct SIMPLE SIMPLE;
typedef struct EXPR EXPR;
typedef struct OTHER_EXPR OTHER_EXPR;

typedef struct PROGRAM {
    int lineno;
    PACKAGE *package;
    TOPLEVELDECL *topleveldecls;
    SymbolTable *symboltable;
} PROGRAM;

typedef struct PACKAGE {
    int lineno;
    char *package;
} PACKAGE;

typedef struct TOPLEVELDECL {
    int lineno;
    SymbolTable *symboltable;
    enum { dcl_toplevel, func_dcl_toplevel } kind;
    union {
        DCL *dcl;
        FUNCDCL *funcdcl;
    } val;
    TOPLEVELDECL *next;
} TOPLEVELDECL;

typedef struct DCL {
    int lineno;
    SymbolTable *symboltable;
    enum { var, type } kind;
    union {
        VARDCL *vardcl;
        TYPEDCL *typedcl;
    } val;
} DCL;

typedef struct VARDCL {
    int lineno;
    SymbolTable *symboltable;
    IDLIST *idlist;
    TYPE *type;
    EXPRLIST *exprlist;
    VARDCL *next;
} VARDCL;

typedef struct TYPEDCL {
    int lineno;
    SymbolTable *symboltable;
    char *identifier;
    TYPE *type;
    TYPEDCL *next;
} TYPEDCL;

typedef struct FUNCDCL {
    int lineno;
    SymbolTable *symboltable;
    char *identifier;
    FUNC_SIGNATURE *signature;
    BLOCK *block;
} FUNCDCL;

typedef struct FUNC_SIGNATURE {
    int lineno;
    SymbolTable *symboltable;
    PARAM_LIST *params;
    TYPE *type;
} FUNC_SIGNATURE;

typedef struct PARAM_LIST {
    int lineno;
    IDLIST *idlist;
    TYPE *type;
    PARAM_LIST *next;
} PARAM_LIST;

typedef struct IDLIST {
    int lineno;
    char *id;
    IDLIST *next;
} IDLIST;

typedef struct TYPE {
    int lineno;
    enum { basic_type_kind, slice_type_kind, array_type_kind, struct_type_kind } kind;
    union {
        char *basic_type;
        TYPE *slice_type;
        struct {int size; TYPE *type;} array_type;
        STRUCT_TYPE *struct_type;
    } val;
} TYPE;

typedef struct STRUCT_TYPE {
    int lineno;
    IDLIST *idlist;
    TYPE *type;
    STRUCT_TYPE *next;
} STRUCT_TYPE;

typedef struct BLOCK {
    int lineno;
    SymbolTable *symboltable;
    STATEMENTS *stmts;
} BLOCK;

typedef struct STATEMENTS {
    int lineno;
    SymbolTable *symboltable;
    STATEMENT *stmt;
    STATEMENTS *next;
} STATEMENTS;

typedef struct STATEMENT {
    int lineno;
    SymbolTable *symboltable;
    enum {dcl_s, simple_s, return_stmt_s, break_stmt_s, continue_stmt_s, block_s, if_stmt_s, switch_stmt_s, for_stmt_s, print_stmt_s, println_stmt_s} kind;
    union {
        DCL *dcl;
        SIMPLE *simple;
        EXPR *return_stmt;
        BLOCK *block;
        struct {
            SymbolTable *symboltable;
            SIMPLE *simple;
            EXPR *expr;
            enum {else_if, no_else} kind_else;
            union {
                BLOCK *if_block;
                struct { STATEMENTS *stmts; ELSE_BLOCK *else_block; SymbolTable *symboltable; } else_block;
            } val;
        } if_stmt;
        struct {SWITCH_CONDITION *condition; SWITCH_CASELIST *caselist; SymbolTable *symboltable; } switch_stmt;
        struct {FOR_CONDITION *condition; BLOCK *block; } for_stmt;
        EXPRLIST *print;
    } val;
} STATEMENT;

typedef struct ELSE_BLOCK {
    int lineno;
    enum {if_stmt_else, block_else} kind;
    union {
        STATEMENT *if_stmt;
        BLOCK *block;
    } val;
} ELSE_BLOCK;

typedef struct SWITCH_CONDITION {
    int lineno;
    SIMPLE *simple;
    EXPR *expr;
} SWITCH_CONDITION;

typedef struct SWITCH_CASELIST {
    int lineno;
    SymbolTable *symboltable;
    bool default_case;
    EXPRLIST *exprlist;
    STATEMENTS *statements;
    SWITCH_CASELIST *next;
} SWITCH_CASELIST;

typedef struct EXPRLIST {
    int lineno;
    EXPR *expr;
    EXPRLIST *next;
} EXPRLIST;

typedef struct FOR_CONDITION {
    int lineno;
    enum { infinite, while_loop, threepart } kind;
    union {
        EXPR *while_expr;
        struct {SIMPLE *init; EXPR *condition; SIMPLE *post; SymbolTable *symboltable; } threepart;
    } val;
} FOR_CONDITION;

typedef struct SIMPLE {
    int lineno;
    SymbolTable *symboltable;
    enum { empty_stmt_kind, expr_kind, increment_kind, decrement_kind, assignment_kind, shortDcl_kind } kind;
    union {
        EXPR *expr;
        struct { EXPRLIST *LHS_expr_list; char *assign_op; EXPRLIST *RHS_expr_list; } assignment;
        struct { EXPRLIST *LHS_expr_list; EXPRLIST *RHS_expr_list; } shortDcl;
    } val;
} SIMPLE;

typedef enum { expressionKindPlus, expressionKindMinus, expressionKindMult, expressionKindDiv, expressionKindMod, expressionKindLT, expressionKindLT_EQ,
       expressionKindGT, expressionKindGT_EQ, expressionKindEQ_EQ, expressionKindNotEquals, expressionKindShift_Right, expressionKindShift_Left,
       expressionKindAnd, expressionKindAMP_XOR, expressionKindOr, expressionKindXor, expressionKindLogicalAnd, expressionKindLogicalOr,
       expressionKindPlusUnary, expressionKindMinusUnary, expressionKindNotUnary, expressionKindXorUnary,
       append_expr, intval, floatval, stringval, rawstringval, runeval, other_expr_kind, } exprKind;

typedef struct EXPR {
    int lineno;
    SymbolTable *symboltable;
    exprKind kind;
    union {
        char *runeLiteral;
        int intLiteral;
        float floatLiteral;
        char *stringLiteral;
        struct { EXPR *lhs; EXPR *rhs; } binary;
        EXPR *expr_unary;
        struct { char *identifier; EXPR *expr; } append_expr;
        OTHER_EXPR *other_expr;
    } val;
} EXPR;

typedef struct OTHER_EXPR {
    int lineno;
    SymbolTable *symboltable;
    enum { identifier_kind, paren_kind, func_call_kind, index_kind, struct_access_kind } kind;
    union {
        EXPR *expr;
        char *identifier;
        struct { OTHER_EXPR *id; EXPRLIST *args; } func_call;
        struct { OTHER_EXPR *expr; EXPR *index; } index;
        struct { OTHER_EXPR *expr; char *identifier; } struct_access;
    } val;
} OTHER_EXPR;

PROGRAM *makePROGRAM(PACKAGE *package, TOPLEVELDECL *topleveldecls);
PACKAGE *makePACKAGE(char *package);
TOPLEVELDECL *makeTOPLEVELDECLS(TOPLEVELDECL *current, TOPLEVELDECL *next);
TOPLEVELDECL *makeTOPLEVELDECL_dcl(DCL *dcl);
TOPLEVELDECL *makeTOPLEVELDECL_funcdcl(FUNCDCL *funcdcl);
DCL *makeDCLTYPE_var(VARDCL *vardcl);
DCL *makeDCLTYPE_type(TYPEDCL *typedcl);
VARDCL *makeDCL_var(IDLIST *idlist, TYPE *type, EXPRLIST *exprlist);
VARDCL *makeDCL_vars(VARDCL *current, VARDCL *next);
TYPEDCL *makeDCL_type(char *identifier, TYPE *type);
TYPEDCL *makeDCL_types(TYPEDCL *current, TYPEDCL *next);
TYPE *makeTYPE_identifier(char *identifier);
TYPE *makeTYPE_slice(TYPE *slice_type);
TYPE *makeTYPE_array(int size, TYPE *type);
TYPE *makeTYPE_struct(STRUCT_TYPE *struct_type);
STRUCT_TYPE *makeSTRUCT(IDLIST *idlist, TYPE *type);
STRUCT_TYPE *makeSTRUCTS(STRUCT_TYPE *current, STRUCT_TYPE *next);
FUNCDCL *makeFUNCTION(char *identifier, FUNC_SIGNATURE *signature, BLOCK *block);
FUNC_SIGNATURE *makeFUNCTION_signature(PARAM_LIST *params, TYPE *type);
PARAM_LIST *makeFUNCTION_parameterList(IDLIST *idlist, TYPE *type, PARAM_LIST *next);
IDLIST *makeIDLIST(char *id, IDLIST *next);
BLOCK *makeBLOCK(STATEMENTS *stmts);
STATEMENTS *makeSTATEMENTS(STATEMENT *stmt, STATEMENTS *next);
STATEMENT *makeSTATEMENT_print(EXPRLIST *print);
STATEMENT *makeSTATEMENT_println(EXPRLIST *print);
STATEMENT *makeSTATEMENT_return(EXPR *return_stmt);
STATEMENT *makeSTATEMENT_if(SIMPLE *simple, EXPR *expr, BLOCK *block);
STATEMENT *makeSTATEMENT_ifElse(SIMPLE *simple, EXPR *expr, STATEMENTS *stmts, ELSE_BLOCK *else_block);
ELSE_BLOCK *makeELSEBLOCK_block(BLOCK *block);
ELSE_BLOCK *makeELSEBLOCK_if(STATEMENT *if_stmt);
STATEMENT *makeSTATEMENT_for(FOR_CONDITION *condition, BLOCK *block);
FOR_CONDITION *makeSTATEMENT_forCondition_infinite();
FOR_CONDITION *makeSTATEMENT_forCondition_while(EXPR *while_expr);
FOR_CONDITION *makeSTATEMENT_forCondition_threepart(SIMPLE *init, EXPR *condition, SIMPLE *post);
STATEMENT *makeSTATEMENT_switch(SWITCH_CONDITION *condition, SWITCH_CASELIST *caselist);
SWITCH_CONDITION *makeSTATEMENT_switchCondition(SIMPLE *simple, EXPR *expr);
SWITCH_CASELIST *makeSTATEMENT_switchCase(EXPRLIST *exprlist, STATEMENTS *statements);
SWITCH_CASELIST *makeSTATEMENT_switchCaseDefault(STATEMENTS *statements);
SWITCH_CASELIST *makeSTATEMENT_switchCases(SWITCH_CASELIST *current, SWITCH_CASELIST *next);
STATEMENT *makeSTATEMENT_break();
STATEMENT *makeSTATEMENT_continue();
STATEMENT *makeSTATEMENT_block(BLOCK *block);
STATEMENT *makeSTATEMENT_dcl(DCL *dcl);
STATEMENT *makeSTATEMENT_simple(SIMPLE *simple);
SIMPLE *makeSIMPLE_expr(EXPR *expr);
SIMPLE *makeSIMPLE_inc(EXPR *expr);
SIMPLE *makeSIMPLE_dec(EXPR *expr);
SIMPLE *makeSIMPLE_assignment(EXPRLIST *LHS_expr_list, char *assign_op, EXPRLIST *RHS_expr_list);
SIMPLE *makeSIMPLE_shortdcl(EXPRLIST *LHS_expr_list, EXPRLIST *RHS_expr_list);
SIMPLE *makeSIMPLE_empty();
EXPRLIST *makeEXPRLIST(EXPR *expr, EXPRLIST *next);
EXPR *makeEXPR_binary(exprKind kind, EXPR *lhs, EXPR *rhs);
EXPR *makeEXPR_unary(exprKind kind, EXPR *expr_unary);;
EXPR *makeEXPR_append(char *identifier, EXPR *expr);
EXPR *makeEXPR_intLiteral(int intLiteral);
EXPR *makeEXPR_floatLiteral(float floatLiteral);
EXPR *makeEXPR_stringLiteral(char *stringLiteral, bool interpreted);
EXPR *makeEXPR_runeLiteral(char *runeLiteral);
EXPR *makeEXPR_other(OTHER_EXPR *other_expr);
OTHER_EXPR *makeEXPR_identifier(char *identifier);
OTHER_EXPR *makeEXPR_paren(EXPR *expr);
OTHER_EXPR *makeEXPR_funcCall(OTHER_EXPR *id, EXPRLIST *args);
OTHER_EXPR *makeEXPR_index(OTHER_EXPR *expr, EXPR *index);
OTHER_EXPR *makeEXPR_structAccess(OTHER_EXPR *expr, char *identifier);

#endif /* !TREE_H */

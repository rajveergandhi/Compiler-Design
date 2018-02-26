#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef enum {
    s_int,
    s_float,
    s_string,
    s_rune,
    s_bool,
} SymbolKind;

typedef enum {
    k_program,
    k_package,
    k_dclVar,
    k_identifier,
    k_dcl_var,
    k_dcl_type,
    k_idlist,
    k_array,
    k_struct,

    /*
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindFloatLiteral,
    k_expressionKindBoolLiteral,
    k_expressionKindStringLiteral,
    k_expressionKindAddition,
    k_expressionKindSubtraction,
    k_expressionKindMultiplication,
    k_expressionKindDivision,
    k_expressionKindEqualsEquals,
    k_expressionKindNotEquals,
    k_expressionKindLogicalAnd,
    k_expressionKindLogicalOr,
    k_expressionKindNot,
    k_expressionKindUnaryMinus,
    k_statementKindRead,
    k_statementKindPrint,
    k_statementKindAssignment,
    k_statementKindIfStmt,
    k_statementKindIfElseStmt,
    k_statementKindWhile,
    k_dcl,
    */
} Kind;

typedef struct NODE NODE;
struct NODE {
    int lineno;
    Kind kind;
    SymbolKind s_kind;
    union {
        char *identifier;
        struct { char *identifier; NODE *next; } idlist;
        struct { NODE *package; NODE *topLevelDecls; } program;
        struct { NODE *idlist; NODE *type; NODE *expr_list; NODE *next; } varDcl;
        struct { char *identifier; NODE *type; NODE *next; } varType;
        struct { NODE *intval; NODE *type; } typeArray;
        struct { NODE *idlist; NODE *type; NODE *next; } typeStruct;
        struct { char *identifier; NODE *signature; NODE *block; } typeFunction;
        struct { NODE *params; NODE *type; } func_sign;
        struct { NODE *param_list; NODE *idlist; NODE *type; } func_params;

        /*
        int intLiteral;
        float floatLiteral;
        bool boolLiteral;
        char *stringLiteral;
        NODE *exp_unary;
        struct { NODE *lhs; NODE *rhs; } exp_binary;
        struct { char *identifier; char *type; NODE *expr; NODE *nextDcl; } dcl;
        struct {
            union {
                char *stmtRead;
                NODE *stmtPrint;
                struct { char *identifier; NODE *expr; } stmtAssign;
                struct { NODE *expr; NODE *stmts; } stmtWhile;
                struct { NODE *expr; NODE *stmts; } stmtIf;
                struct { NODE *expr; NODE *ifStmts; NODE *elseStmts; } stmtIfElse;
            }  type;
            NODE *nextStmt;
        } stmt;
        */
    } val;
};

NODE *makePROGRAM(NODE *package, NODE *topLevelDecls);
NODE *makePACKAGE(char *package);
NODE *makeTOPLEVELDECLS(NODE *topLevelDecls, NODE *topLevelDecl);
NODE *makeDCL_var(NODE *idlist, NODE *type, NODE *expr_list); // type or expr_list (but not both) can be NULL
NODE *makeDCL_vars(NODE *varDcls, NODE *varDcl);
NODE *makeIDLIST(char *id, NODE *nextId); // nextId can be NULL
NODE *makeDCL_type(char *identifier, NODE *type);



#endif /* !TREE_H */




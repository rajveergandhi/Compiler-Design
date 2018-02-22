#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef enum {
    s_int,
    s_float,
    s_string,
    s_bool,
} SymbolKind;

typedef enum {
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
    k_program,
    k_dcl,
} Kind;

typedef struct NODE NODE;
struct NODE {
    int lineno;
    Kind kind;
    SymbolKind s_kind;
    union {
        char *identifier;
        int intLiteral;
        float floatLiteral;
        bool boolLiteral;
        char *stringLiteral;
        NODE *exp_unary;
        struct { NODE *lhs; NODE *rhs; } exp_binary;
        struct { NODE *dcls; NODE *stmts; } program;
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
    } val;
};

NODE *makePROGRAM(NODE *dcls, NODE *stmts);
NODE *makeDCLS(NODE *dcl, NODE *dcls);
NODE *makeDCL(char *identifier, char *type, NODE *expr);
NODE *makeSTMTS(NODE *stmt, NODE *stmts);
NODE *makeSTATEMENT_read(char *identifier);
NODE *makeSTATEMENT_print(NODE *expr);
NODE *makeSTATEMENT_assign(char *identifier, NODE *expr);
NODE *makeSTATEMENT_while(NODE *expr, NODE *stmts);
NODE *makeSTATEMENT_if(NODE *expr, NODE *stmts);
NODE *makeSTATEMENT_ifElse(NODE *expr, NODE *ifStmts, NODE *elseStmts);
NODE *makeEXP_identifier(char *identifier);
NODE *makeEXP_intLiteral(int intLiteral);
NODE *makeEXP_floatLiteral(float floatLiteral);
NODE *makeEXP_boolLiteral(bool boolLiteral);
NODE *makeEXP_stringLiteral(char *stringLiteral);
NODE *makeEXP_binary(Kind op, NODE *lhs, NODE *rhs); // binary expressions: addition, subtraction, multiplication, division, equalsequals, notequals, logical and, logical or
NODE *makeEXP_not(NODE *expr);
NODE *makeEXP_unaryminus(NODE *expr);

#endif /* !TREE_H */

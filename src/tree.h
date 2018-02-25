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
        struct { NODE *package; NODE *topLevelDecls; } program;
        char *identifier;

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

NODE *makeDCL_var(NODE *dclVar);
NODE *makeDCL_varList(NODE *dclVarList);
NODE *makeDCL_varNoAssign(NODE *idlist, NODE *type);
NODE *makeDCL_varNoType(NODE *idlist, NODE *expr_list);
NODE *makeDCL_varAssignType(NODE *idlist, NODE *type, NODE *expr_list);
NODE *makeDCL_nextVar(NODE *dclVarList, NODE *dclVar);

NODE *makeIDENTIFIER(char *identifier);
NODE *makeIDENTIFIERLIST(char *identifier, NODE *idlist);

NODE *makeDCL_type(NODE *dclType);
NODE *makeDCL_typeList(NODE *dclTypeList);
NODE *makeDCL_typeSpec(char *identifier, NODE *type);

NODE *makeArrayNoIndex(NODE *type);
NODE *makeArray(int index, NODE *type);
NODE *makeStruct(NODE *memberlist);

NODE *makeStruct_nextMember(NODE *memberlist, NODE *member);
NODE *makeStruct_Member(NODE *idlist, NODE *type);
NODE *makeStruct_nextType(NODE *dclTypeList, NODE *dclType);

NODE *makeFUNCTION(char *identifier, NODE *signature, NODE *block);
NODE *makeFUNCTION_para(NODE *paralist);
NODE *makeFUNCTION_empty();
NODE *makeFUNCTION_paraType(NODE *paralist, NODE *type);
NODE *makeFUNCTION_type(NODE *type);
NODE *makeFUNCTION_ParaList(NODE *paralist, NODE *idlist, NODE *type);
NODE *makeFUNCTION_Para(NODE *idlist, NODE *type);


/*
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
*/

#endif /* !TREE_H */


//====================================================================================================
/*
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

// typedef enum {
//     s_int,
//     s_float,
//     s_string,
//     s_bool,
// } SymbolKind;

typedef struct NODE NODE;
struct NODE {
    int lineno;
    Kind kind;
    union {
        char *identifier;
        struct { NODE *packages; NODE *initial_dcls; } program;
        NODE *packages;
        NODE *stmtBreak;
        NODE *stmtContinue;
        NODE *inc;
        NODE *dec;
        NODE *exp_unary;
        struct { NODE *lhs; NODE *rhs; } exp_binary;
        struct { NODE *lhs; NODE *rhs; } append;
        struct {
            union {
                struct { char *identifier; char *type; NODE *expr; } varDcl;
                struct { char *identifier; char *type; NODE *expr; } typeDcl;
                struct { char *identifier; char *type; NODE *expr; } funcDcl;
                NODE *block;
                char *stmtRead;
                NODE *stmtPrint;
                NODE *stmtPrintln;
                NODE *stmtReturn;
                struct { NODE *expr; NODE *stmts; } stmtIf;
                struct { NODE *expr; NODE *stmts; } stmtFor;
                struct { NODE *expr; NODE *stmts; } stmtSwitch;
                struct { char *identifier; NODE *expr; } stmtAssign;
                struct { NODE *expr; NODE *stmts; } stmtShortDcl;
                struct { NODE *expr; NODE *stmts; } stmtFuncCall;
                struct { NODE *expr; NODE *stmts; } stmtTypeCast;
                struct { NODE *expr; NODE *stmts; } stmtArrayIndex;
                struct { NODE *expr; NODE *stmts; } stmtSliceRange;
                struct { NODE *expr; NODE *stmts; } stmtStructSelector;
            }  type;
            NODE *nextStmt;
        } stmt;
    } val;
};

NODE *next_decl(NODE *decls, NODE *decl); //variable,type or function declaration
NODE *makeDclNoType(char *identifier, NODE *expr);
NODE *makeDclNoExpr(char *identifier, char *type);
NODE *next_var(NODE *vars, NODE *var);
NODE *next_id(char *identifier);
NODE *next_arg(char *identifier);
NODE *makeIdentifier(char *identifier);
NODE *makeArray(int index, NODE *type);
NODE *makeSlice(NODE *type);
NODE *makeStruct(NODE *member);
NODE *next_member(NODE *members, NODE *member);
*/
// NODE *makeSTATEMENT_read(char *identifier);
// NODE *makeSTATEMENT_print(NODE *expr);
// NODE *makeSTATEMENT_assign(char *identifier, NODE *expr);
// NODE *makeSTATEMENT_while(NODE *expr, NODE *stmts);
// NODE *makeSTATEMENT_if(NODE *expr, NODE *stmts);
// NODE *makeSTATEMENT_ifElse(NODE *expr, NODE *ifStmts, NODE *elseStmts);
// NODE *makeEXP_identifier(char *identifier);
// NODE *makeEXP_intLiteral(int intLiteral);
// NODE *makeEXP_floatLiteral(float floatLiteral);
// NODE *makeEXP_boolLiteral(int boolLiteral);
// NODE *makeEXP_stringLiteral(char *stringLiteral);
// NODE *makeEXP_binary(Kind op, NODE *lhs, NODE *rhs); // binary expressions: addition, subtraction, multiplication, division, equalsequals, notequals, logical and, logical or
// NODE *makeEXP_not(NODE *expr);
// NODE *makeEXP_unaryminus(NODE *expr);

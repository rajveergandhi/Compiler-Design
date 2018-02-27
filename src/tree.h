#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

/* // will be used for future milestone
typedef enum {
    s_int,
    s_float,
    s_string,
    s_rune,
    s_bool,
} SymbolKind;
*/

typedef enum {
    k_program,
    k_package,
    k_dcl_var,
    k_idlist,
    k_dcl_type,
    k_array,
    k_slice,
    k_struct,
    k_function,
    k_function_signature,
    k_function_params,
    k_block,
    k_append,
    k_function_call,
    k_statementKindPrint,
    k_statementKindReturn,
    k_statementKindIf,
    k_statementKindFor,
    k_statementKindForCond,
    k_statementKindSwitch,
    k_statementKindSwitchCondition,
    k_statementKindSwitchCase,
    k_statementKindBreak,
    k_statementKindContinue,
    k_statementKindSimple,
    k_statementKindIncrement,
    k_statementKindAssign,
    k_statementKindShortDcl,
    k_expressionArrayIndex,
    k_expressionKindStructSelector,
    k_expressionKindIdentifier,
    k_expressionKindIntLiteral,
    k_expressionKindFloatLiteral,
    k_expressionKindStringLiteral,
    k_expressionKindRuneLiteral,
    k_expressionKindPlus,
    k_expressionKindMinus,
    k_expressionKindMult,
    k_expressionKindDiv,
    k_expressionKindMod,
    k_expressionKindLT,
    k_expressionKindLT_EQ,
    k_expressionKindGT,
    k_expressionKindGT_EQ,
    k_expressionKindEQ_EQ,
    k_expressionKindNotEquals,
    k_expressionKindShift_Right,
    k_expressionKindShift_Left,
    k_expressionKindAnd,
    k_expressionKindAMP_XOR,
    k_expressionKindOr,
    k_expressionKindXor,
    k_expressionKindLogicalAnd,
    k_expressionKindLogicalOr,
    k_expressionKindNotUnary,
    k_expressionKindPlusUnary,
    k_expressionKindMinusUnary,
    k_expressionKindXorUnary,
} Kind;

typedef struct NODE NODE;
struct NODE {
    int lineno;
    Kind kind;
    //SymbolKind s_kind; // will be used for future milestone
    union {
        NODE *next; // for use with topLevelDecls, which can be: funcDcl, varDcl, typeDcl
        char *package;
        struct { NODE *package; NODE *topLevelDecls; } program;
        struct { char *identifier; NODE *next; } idlist;
        struct { int intval; NODE *type; } typeArray;
        struct { NODE *type; } typeSlice;
        struct { NODE *idlist; NODE *type; NODE *next; } typeStruct;
        struct { NODE *params; NODE *type; } funcSign;
        struct { NODE *param_list; NODE *idlist; NODE *type; } funcParams;
        struct { char *identifier; NODE *signature; NODE *block; } funcDcl;
        struct { NODE *part1; NODE *part2; NODE *part3; } stmtForCondition;
        struct { NODE *simple; NODE *expr; } stmtSwitchCondition;
        struct { NODE *expr_list; NODE *statement_list; NODE *next; } stmtSwitchCase;
        struct {
            union {
                struct { NODE *stmts; } block;
                struct { NODE *simple; } stmtSimple;
                struct { NODE *expr; bool inc; } stmtInc;
                struct { NODE *LHS_expr_list; char *assign_op; NODE *RHS_expr_list; } stmtAssign;
                struct { NODE *LHS_expr_list; NODE *RHS_expr_list; } stmtShortDcl;
                struct { NODE *idlist; NODE *type; NODE *expr_list; NODE *next; } varDcl;
                struct { char *identifier; NODE *type; NODE *next; } typeDcl;
                struct { NODE *expr_list; bool println; } print;
                struct { NODE *expr; } stmtReturn;
                struct { NODE *simple; NODE *expr; NODE *stmts; NODE *elseBlock; } stmtIf;
                struct { NODE *condition; NODE *block; } stmtFor;
                struct { NODE *condition; NODE *caselist; } stmtSwitch;
            } type;
            NODE *next;
        } stmt;
        struct {
            union {
                char *identifier;
                char *runeLiteral;
                int intLiteral;
                float floatLiteral;
                struct { char *stringLiteral; bool interpreted; } stringLiteral;
                NODE *exp_unary;
                struct { NODE *lhs; NODE *rhs; } exp_binary;
                struct { char *identifier; NODE *expr; } expr_append;
                struct { NODE *expr; NODE *index; } arrayIndex;
                struct { NODE *expr; char *identifier; } structSelector;
                struct { NODE *id; NODE *args; } funcCall;
            } type;
            NODE *next;
        } expr;
    } val;
};

NODE *makePROGRAM(NODE *package, NODE *topLevelDecls);
NODE *makePACKAGE(char *package);
NODE *makeTOPLEVELDECLS(NODE *topLevelDecl, NODE *topLevelDecls);
NODE *makeDCL_var(NODE *idlist, NODE *type, NODE *expr_list); // type or expr_list (but not both) can be NULL
NODE *makeDCL_vars(NODE *varDcl, NODE *varDcls);
NODE *makeIDLIST(char *id, NODE *nextId); // nextId can be NULL
NODE *makeDCL_type(char *identifier, NODE *type);
NODE *makeDCL_types(NODE *type, NODE *types);
NODE *makeEXP_identifier(char *identifier);
NODE *makeSlice(NODE *type);
NODE *makeArray(int intval, NODE *type);
NODE *makeStruct(NODE *idlist, NODE *type);
NODE *makeStruct_members(NODE *member, NODE *members);
NODE *makeFUNCTION(char *identifier, NODE *signature, NODE *block);
NODE *makeFUNCTION_signature(NODE *params, NODE *type);
NODE *makeFUNCTION_parameterList(NODE *param_list, NODE *idlist, NODE *type);
NODE *makeBLOCK(NODE *statements);
NODE *makeSTATEMENTS(NODE *stmt, NODE *stmts);
NODE *makeSTATEMENT_print(NODE *expr_list, bool println); // bool println: true if println was called, false if print was called
NODE *makeSTATEMENT_return(NODE *stmtReturn);
NODE *makeSTATEMENT_if(NODE *simple, NODE *expr, NODE *stmts, NODE *elseBlock);
NODE *makeSTATEMENT_for(NODE *condition, NODE *block);
NODE *makeSTATEMENT_forCondition(NODE *part1, NODE *part2, NODE *part3);
NODE *makeSTATEMENT_switch(NODE *condition, NODE *caselist);
NODE *makeSTATEMENT_switchCondition(NODE *simple, NODE *expr);
NODE *makeSTATEMENT_switchCases(NODE *givenCase, NODE *cases);
NODE *makeSTATEMENT_switchCase(NODE *expr_list, NODE *statement_list); // a NULL expr_list means the case was DEFAULT
NODE *makeSTATEMENT_break();
NODE *makeSTATEMENT_continue();
NODE *makeSTATEMENT_simple(NODE *simple);
NODE *makeSTATEMENT_simpleIncrement(NODE *expr, bool inc); // inc: true means increment, false means decrement
NODE *makeSTATEMENT_assign(NODE *LHS_expr_list, char *assign_op, NODE *RHS_expr_list);
NODE *makeSTATEMENT_shortDcl(NODE *LHS_expr_list, NODE *RHS_expr_list);
NODE *makeEXPRLIST(NODE *expr, NODE *expr_list);
NODE *makeEXP_binary(Kind op, NODE *lhs, NODE *rhs);
NODE *makeEXP_unary(Kind op, NODE *expr);
NODE *makeAPPEND(char *identifier, NODE *expr);
NODE *makeEXPRESSION_arrayIndex(NODE *expr, NODE *index);
NODE *makeEXPRESSION_structSelector(NODE *expr, char *identifier);
NODE *makeEXP_identifier(char *identifier);
NODE *makeEXP_intLiteral(int intLiteral);
NODE *makeEXP_floatLiteral(float floatLiteral);
NODE *makeEXP_stringLiteral(char *stringLiteral, bool interpreted); // bool interpreted: true if interpreted string, false if raw string
NODE *makeEXP_runeLiteral(char *runeLiteral);
NODE *makeFUNCTIONCALL(NODE *id, NODE *args);

#endif /* !TREE_H */

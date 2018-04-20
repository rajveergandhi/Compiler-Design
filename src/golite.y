/* A parser for GoLite, with the specifications defined in the class's documentation */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

extern int yylineno;
extern PROGRAM *root;

int yylex();
void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
%}

%code requires
{
    #include "tree.h"
}

%locations
%error-verbose

%union {
    long int_val;
    double float_val;
    char *string_val;
    PROGRAM *program;
    PACKAGE *package;
    TOPLEVELDECL *topleveldecl;
    DCL *dcl;
    VARDCL *vardcl;
    IDLIST *idlist;
    TYPEDCL *typedcl;
    TYPE *type;
    STRUCT_TYPE *struct_type;
    FUNCDCL *funcdcl;
    FUNC_SIGNATURE *func_signature;
    PARAM_LIST *param_list;
    BLOCK *block;
    STATEMENTS *statements;
    STATEMENT *statement;
    ELSE_BLOCK *else_block;
    FOR_CONDITION *for_condition;
    SWITCH_CONDITION *switch_condition;
    SWITCH_CASELIST *switch_caselist;
    SIMPLE *simple;
    EXPRLIST *exprlist;
    EXPR *expr;
    OTHER_EXPR *other_expr;
}

%type <program> program
%type <package> package
%type <topleveldecl> topLevelDecl topLevelDecls
%type <dcl> dcl
%type <vardcl> varDcl varSpec varDclList
%type <idlist> idlist
%type <typedcl> typeDcl typeSpec typeDclList
%type <type> type
%type <struct_type> memberlist member
%type <funcdcl> funcDcl
%type <func_signature> signature
%type <param_list> parameter_list
%type <block> block
%type <statements> statement_list
%type <statement> statement print_stmt println_stmt return_stmt if_stmt for_stmt switch_stmt break_stmt continue_stmt
%type <else_block> else_block
%type <for_condition> for_condition
%type <switch_condition> switch_condition
%type <switch_caselist> caselist case
%type <simple> simple_stmt simple_stmt_no_semi
%type <exprlist> expr_list
%type <expr> expr
%type <other_expr> other_expressions
%type <string_val> assign_op

%token <string_val> tBREAK tDEFAULT tFUNC tINTERFACE tSELECT
%token <string_val> tCASE tDEFER tGO tMAP tSTRUCT
%token <string_val> tCHAN tELSE tGOTO tPACKAGE tSWITCH
%token <string_val> tCONST tFALLTHROUGH tIF tRANGE tTYPE
%token <string_val> tCONTINUE tFOR tIMPORT tRETURN tVAR
%token <string_val> tPRINT tPRINTLN tAPPEND tREAD
%token <string_val> tSEMICOLON tCOLON tCOMMA tPERIOD tELLIPSIS
%token <string_val> tASSIGN tMULT tDIV tPLUS tMINUS tAND tOR
%token <string_val> tMOD tXOR tNOT tOPEN_PAREN tCLOSE_PAREN
%token <string_val> tOPEN_BRACE tCLOSE_BRACE tOPEN_SQ tCLOSE_SQ tDECL
%token <string_val> tEQ_EQ tNOT_EQUALS tLOGICAL_AND tLOGICAL_OR tPLUS_EQ
%token <string_val> tAMP_EQ tMINUS_EQ tMOD_EQ tMULT_EQ tDIV_EQ
%token <string_val> tOR_EQ tLT tGT tLT_EQ tGT_EQ
%token <string_val> tXOR_EQ tARROW tSHIFT_LEFT tSHIFT_RIGHT tSHIFT_LEFT_EQ
%token <string_val> tSHIFT_RIGHT_EQ tINC tDEC tAMP_XOR tAMP_XOR_EQ
%token <int_val> tINTVAL
%token <float_val> tFLOATVAL
%token <string_val> tSTRINGVAL tRAWSTRVAL tIDENTIFIER tRUNEVAL

%right tASSIGN
%left tLOGICAL_OR
%left tLOGICAL_AND
%left tEQ_EQ tNOT_EQUALS tLT tGT tLT_EQ tGT_EQ
%left tPLUS tMINUS tOR tXOR
%left tMULT tDIV tMOD tSHIFT_LEFT tSHIFT_RIGHT tAND tAMP_XOR
%left UNARY

%start program

%%

program : package topLevelDecls {root = makePROGRAM($1,$2);}
        ;

package : tPACKAGE tIDENTIFIER tSEMICOLON {$$ = makePACKAGE($2);}
        ;

topLevelDecls : topLevelDecl topLevelDecls {$$ = makeTOPLEVELDECLS($1, $2);}
              | %empty {$$ = NULL;}
              ;

topLevelDecl : dcl {$$ = makeTOPLEVELDECL_dcl($1);}
             | funcDcl {$$ = makeTOPLEVELDECL_funcdcl($1);}
             ;

dcl : varDcl {$$ = makeDCLTYPE_var($1);}
    | typeDcl {$$ = makeDCLTYPE_type($1);}
    ;

varDcl : tVAR varSpec tSEMICOLON {$$ = $2;}
       | tVAR tOPEN_PAREN varDclList tCLOSE_PAREN tSEMICOLON {$$ = $3;}
       ;

varSpec : idlist type {$$ = makeDCL_var($1, $2, NULL);}
        | idlist tASSIGN expr_list {$$ = makeDCL_var($1, NULL, $3);}
        | idlist type tASSIGN expr_list {$$ = makeDCL_var($1, $2, $4);}
        ;

varDclList : varSpec tSEMICOLON varDclList {$$ = makeDCL_vars($1, $3);}
           | %empty {$$ = NULL;}
           ;

idlist : tIDENTIFIER {$$ = makeIDLIST($1, NULL);}
       | tIDENTIFIER tCOMMA idlist {$$ = makeIDLIST($1, $3);}
       ;

typeDcl : tTYPE typeSpec tSEMICOLON {$$ = $2;}
        | tTYPE tOPEN_PAREN typeDclList tCLOSE_PAREN tSEMICOLON {$$ = $3;}
        ;

typeSpec : tIDENTIFIER type {$$ = makeDCL_type($1, $2);}
         ;

type : tIDENTIFIER {$$ = makeTYPE_identifier($1);}
     | tOPEN_SQ tCLOSE_SQ type {$$ = makeTYPE_slice($3);}
     | tOPEN_SQ tINTVAL tCLOSE_SQ type {$$ = makeTYPE_array($2, $4);}
     | tSTRUCT tOPEN_BRACE memberlist tCLOSE_BRACE {$$ = makeTYPE_struct($3);}
     | tOPEN_PAREN type tCLOSE_PAREN {$$ = $2;}
     ;

memberlist : member memberlist {$$ = makeSTRUCTS($1, $2);}
           | %empty {$$ = NULL;}
           ;

member : idlist type tSEMICOLON {$$ = makeSTRUCT($1, $2);}
       ;

typeDclList : typeSpec tSEMICOLON typeDclList {$$ = makeDCL_types($1, $3);}
            | %empty  {$$ = NULL;}
            ;

funcDcl : tFUNC tIDENTIFIER signature block {$$ = makeFUNCTION($2, $3, $4);}
        ;

signature : tOPEN_PAREN parameter_list tCLOSE_PAREN {$$ = makeFUNCTION_signature($2, NULL);}
          | tOPEN_PAREN tCLOSE_PAREN {$$ = makeFUNCTION_signature(NULL, NULL);}
          | tOPEN_PAREN parameter_list tCLOSE_PAREN type {$$ = makeFUNCTION_signature($2, $4);}
          | tOPEN_PAREN tCLOSE_PAREN type {$$ = makeFUNCTION_signature(NULL, $3);}
          ;

parameter_list : idlist type tCOMMA parameter_list {$$ = makeFUNCTION_parameterList($1, $2, $4);}
               | idlist type {$$ = makeFUNCTION_parameterList($1, $2, NULL);}
               ;

block : tOPEN_BRACE statement_list tCLOSE_BRACE tSEMICOLON {$$ = makeBLOCK($2);}
      ;

statement_list : statement statement_list {$$ = makeSTATEMENTS($1, $2);}
               | %empty {$$ = NULL;}
               ;

statement : dcl {$$ = makeSTATEMENT_dcl($1);}
          | block {$$ = makeSTATEMENT_block($1);}
          | print_stmt {$$ = $1;}
          | println_stmt {$$ = $1;}
          | return_stmt {$$ = $1;}
          | if_stmt {$$ = $1;}
          | for_stmt {$$ = $1;}
          | switch_stmt {$$ = $1;}
          | break_stmt {$$ = $1;}
          | continue_stmt {$$ = $1;}
          | simple_stmt {$$ = makeSTATEMENT_simple($1);}
          ;

print_stmt : tPRINT tOPEN_PAREN expr_list tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_print($3);}
           | tPRINT tOPEN_PAREN tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_print(NULL);}
           ;

println_stmt : tPRINTLN tOPEN_PAREN expr_list tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_println($3);}
             | tPRINTLN tOPEN_PAREN tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_println(NULL);}
             ;

return_stmt : tRETURN expr tSEMICOLON {$$ = makeSTATEMENT_return($2);}
            | tRETURN tSEMICOLON {$$ = makeSTATEMENT_return(NULL);}
            ;

if_stmt : tIF simple_stmt expr block {$$ = makeSTATEMENT_if($2, $3, $4);}
        | tIF expr block {$$ = makeSTATEMENT_if(NULL, $2, $3);}
        | tIF simple_stmt expr tOPEN_BRACE statement_list tCLOSE_BRACE tELSE else_block {$$ = makeSTATEMENT_ifElse($2, $3, $5, $8);}
        | tIF expr tOPEN_BRACE statement_list tCLOSE_BRACE tELSE else_block {$$ = makeSTATEMENT_ifElse(NULL, $2, $4, $7);}
        ;

else_block : block {$$ = makeELSEBLOCK_block($1);}
           | if_stmt {$$ = makeELSEBLOCK_if($1);}
           ;

for_stmt : tFOR for_condition block {$$ = makeSTATEMENT_for($2, $3);}
         ;

for_condition : %empty {$$ = makeSTATEMENT_forCondition_infinite();}
              | expr {$$ = makeSTATEMENT_forCondition_while($1);}
              | simple_stmt_no_semi tSEMICOLON expr tSEMICOLON simple_stmt_no_semi {$$ = makeSTATEMENT_forCondition_threepart($1, $3, $5);}
              | simple_stmt_no_semi tSEMICOLON tSEMICOLON simple_stmt_no_semi {$$ = makeSTATEMENT_forCondition_threepart($1, NULL, $4);}
              ;

switch_stmt : tSWITCH switch_condition tOPEN_BRACE caselist tCLOSE_BRACE {$$ = makeSTATEMENT_switch($2, $4);}
            ;

switch_condition : simple_stmt {$$ = makeSTATEMENT_switchCondition($1, NULL);}
                 | simple_stmt expr {$$ = makeSTATEMENT_switchCondition($1, $2);}
                 | expr {$$ = makeSTATEMENT_switchCondition(NULL, $1);}
                 | %empty {$$ = makeSTATEMENT_switchCondition(NULL, NULL);}
                 ;

caselist : case caselist {$$ = makeSTATEMENT_switchCases($1, $2);}
         | %empty {$$ = NULL;}
         ;

case : tCASE expr_list tCOLON statement_list {$$ = makeSTATEMENT_switchCase($2, $4);}
     | tDEFAULT tCOLON statement_list {$$ = makeSTATEMENT_switchCaseDefault($3);}
     ;

break_stmt : tBREAK tSEMICOLON {$$ = makeSTATEMENT_break();}
           ;

continue_stmt : tCONTINUE tSEMICOLON {$$ = makeSTATEMENT_continue();}
              ;

simple_stmt : simple_stmt_no_semi tSEMICOLON {$$ = $1;}
            ;

simple_stmt_no_semi : expr {$$ = makeSIMPLE_expr($1);}
                    | expr tINC {$$ = makeSIMPLE_inc($1);}
                    | expr tDEC {$$ = makeSIMPLE_dec($1);}
                    | expr_list tASSIGN expr_list {$$ = makeSIMPLE_assignment($1, $2, $3);}
                    | expr assign_op expr {$$ = makeSIMPLE_OPassignment($1, $2, $3);}
                    | expr_list tDECL expr_list {$$ = makeSIMPLE_shortdcl($1, $3);}
                    | %empty {$$ = makeSIMPLE_empty();}
                    ;

expr_list : expr {$$ = makeEXPRLIST($1, NULL);}
          | expr tCOMMA expr_list {$$ = makeEXPRLIST($1, $3);}
          ;

expr : expr tPLUS expr {$$ = makeEXPR_binary(expressionKindPlus, $1, $3);}
     | expr tMINUS expr {$$ = makeEXPR_binary(expressionKindMinus, $1, $3);}
     | expr tMULT expr {$$ = makeEXPR_binary(expressionKindMult, $1, $3);}
     | expr tDIV expr {$$ = makeEXPR_binary(expressionKindDiv, $1, $3);}
     | expr tMOD expr {$$ = makeEXPR_binary(expressionKindMod, $1, $3);}
     | expr tLT expr {$$ = makeEXPR_binary(expressionKindLT, $1, $3);}
     | expr tLT_EQ expr {$$ = makeEXPR_binary(expressionKindLT_EQ, $1, $3);}
     | expr tGT expr {$$ = makeEXPR_binary(expressionKindGT, $1, $3);}
     | expr tGT_EQ expr {$$ = makeEXPR_binary(expressionKindGT_EQ, $1, $3);}
     | expr tEQ_EQ expr {$$ = makeEXPR_binary(expressionKindEQ_EQ, $1, $3);}
     | expr tNOT_EQUALS expr {$$ = makeEXPR_binary(expressionKindNotEquals, $1, $3);}
     | expr tSHIFT_RIGHT expr {$$ = makeEXPR_binary(expressionKindShift_Right, $1, $3);}
     | expr tSHIFT_LEFT expr {$$ = makeEXPR_binary(expressionKindShift_Left, $1, $3);}
     | expr tAND expr {$$ = makeEXPR_binary(expressionKindAnd, $1, $3);}
     | expr tAMP_XOR expr {$$ = makeEXPR_binary(expressionKindAMP_XOR, $1, $3);}
     | expr tOR expr {$$ = makeEXPR_binary(expressionKindOr, $1, $3);}
     | expr tXOR expr {$$ = makeEXPR_binary(expressionKindXor, $1, $3);}
     | expr tLOGICAL_AND expr {$$ = makeEXPR_binary(expressionKindLogicalAnd, $1, $3);}
     | expr tLOGICAL_OR expr {$$ = makeEXPR_binary(expressionKindLogicalOr, $1, $3);}
     | tPLUS expr %prec UNARY {$$ = makeEXPR_unary(expressionKindPlusUnary, $2);}
     | tMINUS expr %prec UNARY {$$ = makeEXPR_unary(expressionKindMinusUnary, $2);}
     | tNOT expr %prec UNARY {$$ = makeEXPR_unary(expressionKindNotUnary, $2);}
     | tXOR expr %prec UNARY {$$ = makeEXPR_unary(expressionKindXorUnary, $2);}
     | tAPPEND tOPEN_PAREN tIDENTIFIER tCOMMA expr tCLOSE_PAREN {$$ = makeEXPR_append($3, $5);}
     | tINTVAL {$$ = makeEXPR_intLiteral($1);}
     | tFLOATVAL {$$ = makeEXPR_floatLiteral($1);}
     | tSTRINGVAL {$$ = makeEXPR_stringLiteral($1, true);}
     | tRAWSTRVAL {$$ = makeEXPR_stringLiteral($1, false);}
     | tRUNEVAL {$$ = makeEXPR_runeLiteral($1);}
     | other_expressions {$$ = makeEXPR_other($1);}
     ;

other_expressions : tIDENTIFIER {$$ = makeEXPR_identifier($1);}
                  | tOPEN_PAREN expr tCLOSE_PAREN {$$ = makeEXPR_paren($2);}
                  | other_expressions tOPEN_PAREN expr_list tCLOSE_PAREN {$$ = makeEXPR_funcCall($1, $3);}
                  | other_expressions tOPEN_PAREN tCLOSE_PAREN {$$ = makeEXPR_funcCall($1, NULL);}
                  | other_expressions tOPEN_SQ expr tCLOSE_SQ {$$ = makeEXPR_index($1, $3);}
                  | other_expressions tPERIOD tIDENTIFIER {$$ = makeEXPR_structAccess($1, $3);}
                  ;

assign_op : tPLUS_EQ {$$ = $1;}
          | tMINUS_EQ {$$ = $1;}
          | tMULT_EQ {$$ = $1;}
          | tDIV_EQ {$$ = $1;}
          | tMOD_EQ {$$ = $1;}
          | tAMP_EQ {$$ = $1;}
          | tOR_EQ {$$ = $1;}
          | tXOR_EQ {$$ = $1;}
          | tSHIFT_LEFT_EQ {$$ = $1;}
          | tSHIFT_RIGHT_EQ {$$ = $1;}
          | tAMP_XOR_EQ {$$ = $1;}
          ;

%%

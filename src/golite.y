/* A parser for GoLite, with the specifications defined in the class's documentation */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

extern int yylineno;
extern NODE *root;

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
    int int_val;
    double float_val;
    char *string_val;
    NODE *node;
}

%type <node> program package topLevelDecls topLevelDecl dcl varDcl varSpec varDclList idlist
%type <node> typeDcl typeSpec type memberlist member typeDclList funcDcl signature parameter_list 
%type <node> block statement_list statement print_stmt println_stmt return_stmt if_stmt else_block for_stmt 
%type <node> for_condition condition switch_stmt switch_condition caselist case break_stmt continue_stmt simple_stmt 
%type <node> simple_stmt_no_semi assignment_stmt shortDcl expr_list expr append_expr other_expressions operand 
%type <node> function_call array_index
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

topLevelDecl : dcl {$$ = $1;}
             | funcDcl {$$ = $1;}
             ;

dcl : varDcl {$$ = $1;}
    | typeDcl {$$ = $1;}
    ;

varDcl : tVAR varSpec tSEMICOLON {$$ = $2;}
       | tVAR tOPEN_PAREN varDclList tCLOSE_PAREN tSEMICOLON {$$ = $3;}
       ;

varSpec : idlist type {$$ = makeDCL_var($1, $2, NULL);}
        | idlist tASSIGN expr_list {$$ = makeDCL_var($1, NULL, $3);}
        | idlist type tASSIGN expr_list {$$ = makeDCL_var($1, $2, $4);}
        ;

varDclList : varSpec tSEMICOLON varDclList {$$ = makeDCL_vars($1, $3);}
           | %empty {$$ = makeDCL_var(NULL, NULL, NULL);}
           ;

idlist : tIDENTIFIER {$$ = makeIDLIST($1, NULL);}
       | tIDENTIFIER tCOMMA idlist {$$ = makeIDLIST($1, $3);}
       ;

typeDcl : tTYPE typeSpec tSEMICOLON {$$ = $2;}
        | tTYPE tOPEN_PAREN typeDclList tCLOSE_PAREN tSEMICOLON {$$ = $3;}
        ;

typeSpec : tIDENTIFIER type {$$ = makeDCL_type($1, $2);}
         ;

type : tIDENTIFIER {$$ = makeEXP_identifier($1);}
     | tOPEN_SQ tCLOSE_SQ type {$$ = makeSlice($3);}
     | tOPEN_SQ tINTVAL tCLOSE_SQ type {$$ = makeArray($2, $4);}
     | tSTRUCT tOPEN_BRACE memberlist tCLOSE_BRACE {$$ = $3;}
     ;

memberlist : member memberlist {$$ = makeStruct_members($1, $2);}
           | %empty {$$ = makeStruct(NULL, NULL);}
           ;

member : idlist type tSEMICOLON {$$ = makeStruct($1, $2);}
       ;

typeDclList : typeSpec tSEMICOLON typeDclList {$$ = makeDCL_types($1, $3);}
            | %empty  {$$ = makeDCL_type(NULL, NULL);}
            ;

funcDcl : tFUNC tIDENTIFIER signature block {$$ = makeFUNCTION($2, $3, $4);}
        ;

signature : tOPEN_PAREN parameter_list tCLOSE_PAREN {$$ = makeFUNCTION_signature($2, NULL);}
          | tOPEN_PAREN tCLOSE_PAREN {$$ = makeFUNCTION_signature(NULL, NULL);}
          | tOPEN_PAREN parameter_list tCLOSE_PAREN type {$$ = makeFUNCTION_signature($2, $4);}
          | tOPEN_PAREN tCLOSE_PAREN type {$$ = makeFUNCTION_signature(NULL, $3);}
          | tOPEN_PAREN parameter_list tCLOSE_PAREN tOPEN_PAREN type tCLOSE_PAREN {$$ = makeFUNCTION_signature($2, $5);}
          | tOPEN_PAREN tCLOSE_PAREN tOPEN_PAREN type tCLOSE_PAREN {$$ = makeFUNCTION_signature(NULL, $4);}
          ;

parameter_list : idlist type tCOMMA parameter_list {$$ = makeFUNCTION_parameterList($1, $2, $4);}
               | idlist type {$$ = makeFUNCTION_parameterList($1, $2, NULL);}
               ;

block : tOPEN_BRACE statement_list tCLOSE_BRACE tSEMICOLON {$$ = makeBLOCK($2);}
      ;

statement_list : statement statement_list {$$ = makeSTATEMENTS($1, $2);}
               | %empty {$$ = NULL;}
               ;

statement : dcl {$$ = $1;}
          | block {$$ = $1;}
          | print_stmt {$$ = $1;}
          | println_stmt {$$ = $1;}
          | return_stmt {$$ = $1;}
          | if_stmt {$$ = $1;}
          | for_stmt {$$ = $1;}
          | switch_stmt {$$ = $1;}
          | break_stmt {$$ = $1;}
          | continue_stmt {$$ = $1;}
          | simple_stmt {$$ = $1;}
          ;

print_stmt : tPRINT tOPEN_PAREN expr_list tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_print($3, false);}
           | tPRINT tOPEN_PAREN tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_print(NULL, false);}
           ;

println_stmt : tPRINTLN tOPEN_PAREN expr_list tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_print($3, true);}
             | tPRINTLN tOPEN_PAREN tCLOSE_PAREN tSEMICOLON {$$ = makeSTATEMENT_print(NULL, true);}
             ;

return_stmt : tRETURN expr tSEMICOLON {$$ = makeSTATEMENT_return($2);}
            | tRETURN tSEMICOLON {$$ = makeSTATEMENT_return(NULL);}
            ;

if_stmt : tIF simple_stmt expr block {$$ = makeSTATEMENT_if($2, $3, $4, NULL);}
        | tIF expr block {$$ = makeSTATEMENT_if(NULL, $2, $3, NULL);}
        | tIF simple_stmt expr tOPEN_BRACE statement_list tCLOSE_BRACE tELSE else_block {$$ = makeSTATEMENT_if($2, $3, $5, $8);}
        | tIF expr tOPEN_BRACE statement_list tCLOSE_BRACE tELSE else_block {$$ = makeSTATEMENT_if(NULL, $2, $4, $7);}
        ;

else_block : block {$$ = $1;}
           | if_stmt {$$ = $1;}
           ;

for_stmt : tFOR for_condition block {$$ = makeSTATEMENT_for($2, $3);}
         ;

for_condition : condition {$$ = $1;}
              | simple_stmt_no_semi tSEMICOLON condition tSEMICOLON simple_stmt_no_semi {$$ = makeSTATEMENT_forCondition($1, $3, $5);}
              ;

condition : expr {$$ = $1;}
          | %empty {$$ = NULL;}
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
     | tDEFAULT tCOLON statement_list {$$ = makeSTATEMENT_switchCase(NULL, $3);}
     ;

break_stmt : tBREAK tSEMICOLON {$$ = makeSTATEMENT_break();}
           ;

continue_stmt : tCONTINUE tSEMICOLON {$$ = makeSTATEMENT_continue();}
              ;

simple_stmt : simple_stmt_no_semi tSEMICOLON {$$ = makeSTATEMENT_simple($1);}
            ;

simple_stmt_no_semi : expr {$$ = $1;}
                    | expr tINC {$$ = makeSTATEMENT_simpleIncrement($1, true);}
                    | expr tDEC {$$ = makeSTATEMENT_simpleIncrement($1, false);}
                    | assignment_stmt {$$ = $1;}
                    | shortDcl {$$ = $1;}
                    | %empty {$$ = NULL;}
                    ;

assignment_stmt : expr_list assign_op expr_list {$$ = makeSTATEMENT_assign($1, $2, $3);}
                ;

shortDcl : expr_list tDECL expr_list {$$ = makeSTATEMENT_shortDcl($1, $3);}
         ;

expr_list : expr {$$ = $1;}
          | expr tCOMMA expr_list {$$ = makeEXPRLIST($1, $3);}
          ;

expr : expr tPLUS expr {$$ = makeEXP_binary(k_expressionKindPlus, $1, $3);}
     | expr tMINUS expr {$$ = makeEXP_binary(k_expressionKindMinus, $1, $3);}
     | expr tMULT expr {$$ = makeEXP_binary(k_expressionKindMult, $1, $3);}
     | expr tDIV expr {$$ = makeEXP_binary(k_expressionKindDiv, $1, $3);}
     | expr tMOD expr {$$ = makeEXP_binary(k_expressionKindMod, $1, $3);}
     | expr tLT expr {$$ = makeEXP_binary(k_expressionKindLT, $1, $3);}
     | expr tLT_EQ expr {$$ = makeEXP_binary(k_expressionKindLT_EQ, $1, $3);}
     | expr tGT expr {$$ = makeEXP_binary(k_expressionKindGT, $1, $3);}
     | expr tGT_EQ expr {$$ = makeEXP_binary(k_expressionKindGT_EQ, $1, $3);}
     | expr tEQ_EQ expr {$$ = makeEXP_binary(k_expressionKindEQ_EQ, $1, $3);}
     | expr tNOT_EQUALS expr {$$ = makeEXP_binary(k_expressionKindNotEquals, $1, $3);}
     | expr tSHIFT_RIGHT expr {$$ = makeEXP_binary(k_expressionKindShift_Right, $1, $3);}
     | expr tSHIFT_LEFT expr {$$ = makeEXP_binary(k_expressionKindShift_Left, $1, $3);}
     | expr tAND expr {$$ = makeEXP_binary(k_expressionKindAnd, $1, $3);}
     | expr tAMP_XOR expr {$$ = makeEXP_binary(k_expressionKindAMP_XOR, $1, $3);}
     | expr tOR expr {$$ = makeEXP_binary(k_expressionKindOr, $1, $3);}
     | expr tXOR expr {$$ = makeEXP_binary(k_expressionKindXor, $1, $3);}
     | expr tLOGICAL_AND expr {$$ = makeEXP_binary(k_expressionKindLogicalAnd, $1, $3);}
     | expr tLOGICAL_OR expr {$$ = makeEXP_binary(k_expressionKindLogicalOr, $1, $3);}
     | tPLUS expr %prec UNARY {$$ = makeEXP_unary(k_expressionKindPlusUnary, $2);}
     | tMINUS expr %prec UNARY {$$ = makeEXP_unary(k_expressionKindMinusUnary, $2);}
     | tNOT expr %prec UNARY {$$ = makeEXP_unary(k_expressionKindNotUnary, $2);}
     | tXOR expr %prec UNARY {$$ = makeEXP_unary(k_expressionKindXorUnary, $2);}
     | append_expr {$$ = $1;}
     | other_expressions {$$ = $1;}
     ;

append_expr : tAPPEND tOPEN_PAREN tIDENTIFIER tCOMMA expr tCLOSE_PAREN {$$ = makeAPPEND($3, $5);}
            ;

other_expressions : function_call {$$ = $1;}
                  | operand {$$ = $1;}
                  | other_expressions array_index {$$ = makeEXPRESSION_arrayIndex($1, $2);}
                  | other_expressions tPERIOD tIDENTIFIER {$$ = makeEXPRESSION_structSelector($1, $3);}
                  ;

operand : tOPEN_PAREN expr tCLOSE_PAREN {$$ = $2;}
        | tIDENTIFIER {$$ = makeEXP_identifier($1);}
        | tINTVAL {$$ = makeEXP_intLiteral($1);}
        | tFLOATVAL {$$ = makeEXP_floatLiteral($1);}
        | tSTRINGVAL {$$ = makeEXP_stringLiteral($1, true);}
        | tRAWSTRVAL {$$ = makeEXP_stringLiteral($1, false);}
        | tRUNEVAL {$$ = makeEXP_runeLiteral($1);}
        ;

function_call : other_expressions tOPEN_PAREN expr_list tCLOSE_PAREN {$$ = makeFUNCTIONCALL($1, $3);}
              | other_expressions tOPEN_PAREN tCLOSE_PAREN {$$ = makeFUNCTIONCALL($1, NULL);}
              ;

array_index : tOPEN_SQ expr tCLOSE_SQ {$$ = $2;}
            ;

assign_op : tASSIGN {$$ = $1;}
          | tPLUS_EQ {$$ = $1;}
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

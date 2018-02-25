/* A parser for GoLite, with the specifications defined in the class's documentation */

%{
#include <stdio.h>
#include <stdlib.h>
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

%type <node> program package topLevelDecls topLevelDecl

%token tBREAK tDEFAULT tFUNC tINTERFACE tSELECT
%token tCASE tDEFER tGO tMAP tSTRUCT
%token tCHAN tELSE tGOTO tPACKAGE tSWITCH
%token tCONST tFALLTHROUGH tIF tRANGE tTYPE
%token tCONTINUE tFOR tIMPORT tRETURN tVAR
%token tPRINT tPRINTLN tAPPEND tREAD
%token tSEMICOLON tCOLON tCOMMA tPERIOD tELLIPSIS
%token tASSIGN tMULT tDIV tPLUS tMINUS tAND tOR
%token tMOD tXOR tNOT tOPEN_PAREN tCLOSE_PAREN
%token tOPEN_BRACE tCLOSE_BRACE tOPEN_SQ tCLOSE_SQ tDECL
%token tEQ_EQ tNOT_EQUALS tLOGICAL_AND tLOGICAL_OR tPLUS_EQ
%token tAMP_EQ tMINUS_EQ tMOD_EQ tMULT_EQ tDIV_EQ
%token tOR_EQ tLT tGT tLT_EQ tGT_EQ
%token tXOR_EQ tARROW tSHIFT_LEFT tSHIFT_RIGHT tSHIFT_LEFT_EQ
%token tSHIFT_RIGHT_EQ tINC tDEC tAMP_XOR tAMP_XOR_EQ
%token <int_val> tINTVAL
%token <float_val> tFLOATVAL
%token <string_val> tSTRINGVAL
%token <string_val> tRAWSTRVAL
%token <string_val> tIDENTIFIER
%token <string_val> tRUNEVAL

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

topLevelDecls : topLevelDecls topLevelDecl {$$ = makeTOPLEVELDECLS($1,$2);}
              | %empty {$$ = NULL;}
              ;

topLevelDecl : dcl {$$ = $1;}
             | funcDcl {$$ = $1;}
             ;

dcl : varDcl {$$ = $1;}
    | typeDcl {$$ = $1;}
    ;

varDcl : tVAR varSpec tSEMICOLON {$$ = makeDCL_var($2);}
       | tVAR tOPEN_PAREN varDclList tCLOSE_PAREN tSEMICOLON {$$ = makeDCL_varList($3);}
       ;

varSpec : idlist type {$$ = makeDCL_varNoAssign($1, $2);}
        | idlist tASSIGN expr_list {$$ = makeDCL_varNoType($1, $3);}
        | idlist type tASSIGN expr_list {$$ = makeDCL_varTypeAssign($1, $2, $4);}
        ;

varDclList : varDclList varSpec tSEMICOLON {$$ = makeDCL_nextVar($1, $2);}
           | %empty
           ;

idlist : tIDENTIFIER {$$ = makeIDENTIFIER($1);}
       | tIDENTIFIER tCOMMA idlist {$$ = makeIDENTIFIERLIST($1, $3);}
       ;

typeDcl : tTYPE typeSpec tSEMICOLON {$$ = makeDCL_type($2);}
        | tTYPE tOPEN_PAREN typeDclList tCLOSE_PAREN tSEMICOLON {$$ = makeDCL_typeList($3);}
        ;

typeSpec : tIDENTIFIER type {$$ = makeDCL_typeSpec($1, $2);}
         ;

type : tIDENTIFIER {$$ = makeIDENTIFIER($1);}
     | tOPEN_SQ tCLOSE_SQ type {$$ = makeArrayNoIndex($3);}
     | tOPEN_SQ tINTVAL tCLOSE_SQ type {$$ = makeArray($2, $4);}
     | tSTRUCT tOPEN_BRACE memberlist tCLOSE_BRACE {$$ = makeStruct($3);}
     ;

memberlist : memberlist member {$$ = makeStruct_nextMember($1, $2);}
           | %empty
           ;

member : idlist type tSEMICOLON {$$ = makeStruct_Member($1, $2);}
       ;

typeDclList : typeDclList typeSpec tSEMICOLON {$$ = makeDCL_nextType($1, $2);}
            | %empty
            ;

funcDcl : tFUNC tIDENTIFIER signature block {$$ = makeFUNCTION($2, $3, $4);}
        ;

signature : tOPEN_PAREN parameter_list tCLOSE_PAREN {$$ = makeFUNCTION_para($2);}
          | tOPEN_PAREN tCLOSE_PAREN {$$ = makeFUNCTION_empty();}
          | tOPEN_PAREN parameter_list tCLOSE_PAREN type {$$ = makeFUNCTION_paraType($2, $4);}
          | tOPEN_PAREN tCLOSE_PAREN type {$$ = makeFUNCTION_type($3);}
          | tOPEN_PAREN parameter_list tCLOSE_PAREN tOPEN_PAREN type tCLOSE_PAREN {$$ = makeFUNCTION_paraType($2, $5);}
          | tOPEN_PAREN tCLOSE_PAREN tOPEN_PAREN type tCLOSE_PAREN {$$ = makeFUNCTION_type($4);}
          ;

parameter_list : parameter_list tCOMMA idlist type {$$ = makeFUNCTION_ParaList($1, $3, $4);}
               | idlist type {$$ = makeFUNCTION_Para($1, $2);}
               ;

block : simple_block tSEMICOLON
      ;

simple_block : tOPEN_BRACE statement_list tCLOSE_BRACE
             ;

statement_list : statement_list statement
               | %empty
               ;

statement : dcl
          | block
          | print_stmt
          | println_stmt
          | return_stmt
          | if_stmt
          | for_stmt
          | switch_stmt
          | break_stmt
          | continue_stmt
          | simple_stmt
          ;

print_stmt : tPRINT tOPEN_PAREN expr_list tCLOSE_PAREN tSEMICOLON
           | tPRINT tOPEN_PAREN tCLOSE_PAREN tSEMICOLON
           ;

println_stmt : tPRINTLN tOPEN_PAREN expr_list tCLOSE_PAREN tSEMICOLON
             | tPRINTLN tOPEN_PAREN tCLOSE_PAREN tSEMICOLON
             ;

return_stmt : tRETURN expr tSEMICOLON
            | tRETURN tSEMICOLON
            ;

if_stmt : tIF if_condition block
        | tIF if_condition simple_block tELSE else_block
        ;

if_condition : simple_stmt expr
             | expr
             ;

else_block : block
           | if_stmt
           ;

for_stmt : tFOR for_condition block
         ;

for_condition : condition
              | simple_stmt_no_semi tSEMICOLON condition tSEMICOLON simple_stmt_no_semi
              ;

condition : expr
          | %empty
          ;

switch_stmt : tSWITCH switch_condition tOPEN_BRACE caselist tCLOSE_BRACE
            ;

switch_condition : simple_stmt
                 | simple_stmt expr
                 | expr
                 | %empty
                 ;

caselist : case caselist
         | %empty
         ;

case : tCASE expr_list tCOLON statement_list
     | tDEFAULT tCOLON statement_list
     ;

break_stmt : tBREAK tSEMICOLON
           ;

continue_stmt : tCONTINUE tSEMICOLON
              ;

simple_stmt : simple_stmt_no_semi tSEMICOLON
            ;

simple_stmt_no_semi : expr
                    | expr tINC
                    | expr tDEC
                    | assignment_stmt
                    | shortDcl
                    | %empty
                    ;

assignment_stmt : expr_list assign expr_list
                ;

shortDcl : expr_list tDECL expr_list
         ;

expr_list : expr
         | expr_list tCOMMA expr
         ;

expr : expr tPLUS expr
     | expr tMINUS expr
     | expr tMULT expr
     | expr tDIV expr
     | expr tMOD expr
     | expr tLT expr
     | expr tLT_EQ expr
     | expr tGT expr
     | expr tGT_EQ expr
     | expr tEQ_EQ expr
     | expr tNOT_EQUALS expr
     | expr tSHIFT_RIGHT expr
     | expr tSHIFT_LEFT expr
     | expr tAND expr
     | expr tAMP_XOR expr
     | expr tOR expr
     | expr tXOR expr
     | expr tLOGICAL_AND expr
     | expr tLOGICAL_OR expr
     | unary_op expr %prec UNARY
     | append_expr
     | other_expressions
     ;

unary_op : tPLUS
         | tMINUS
         | tNOT
         | tXOR
         ;

append_expr : tAPPEND tOPEN_PAREN tIDENTIFIER tCOMMA expr tCLOSE_PAREN
            ;

other_expressions : function_call
                  | operand
                  | other_expressions array_index
                  | other_expressions slice_range
                  | other_expressions struct_selector
                  ;

operand : tOPEN_PAREN expr tCLOSE_PAREN
        | tIDENTIFIER
        | tINTVAL
        | tFLOATVAL
        | tSTRINGVAL
        | tRUNEVAL
        | tRAWSTRVAL
        ;

function_call : other_expressions tOPEN_PAREN expr_list tCLOSE_PAREN
              | other_expressions tOPEN_PAREN tCLOSE_PAREN
              ;

array_index : tOPEN_SQ expr tCLOSE_SQ
            ;

slice_range : tOPEN_SQ expr tCOLON expr tCLOSE_SQ
            | tOPEN_SQ tCOLON expr tCLOSE_SQ
            | tOPEN_SQ expr tCOLON tCLOSE_SQ
            | tOPEN_SQ tCOLON tCLOSE_SQ
            | tOPEN_SQ expr tCOLON expr tCOLON expr tCLOSE_SQ
            | tOPEN_SQ tCOLON expr tCOLON expr tCLOSE_SQ
            ;

struct_selector : tPERIOD tIDENTIFIER
                ;

assign : tASSIGN
       | tPLUS_EQ
       | tMINUS_EQ
       | tMULT_EQ
       | tDIV_EQ
       | tMOD_EQ
       | tAMP_EQ
       | tOR_EQ
       | tXOR_EQ
       | tSHIFT_LEFT_EQ
       | tSHIFT_RIGHT_EQ
       | tAMP_XOR_EQ
       ;

%%

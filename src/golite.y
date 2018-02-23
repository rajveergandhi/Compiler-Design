/* A parser for GoLite, with the specifications defined in the class's documentation */

%{
#include<stdio.h>
#include<stdlib.h>

extern int yylineno;
int yylex();
void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
%}

%union {
    int int_val;
	double float_val;
	char *string_val;
    char *rune_val;
	char *ident;
}

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
%token tINT tFLOAT tSTRING tBOOL tRUNE
%token tUNARY
%token <int_val> tINTVAL
%token <float_val> tFLOATVAL
%token <string_val> tSTRINGVAL
%token <string_val> tRAWSTRVAL
%token <string_val> tIDENTIFIER
%token <rune_val> tRUNEVAL

%right tASSIGN
%left tLOGICAL_OR
%left tLOGICAL_AND
%left tEQ_EQ tNOT_EQUALS tLT tGT tLT_EQ tGT_EQ
%left tPLUS tMINUS tOR tXOR
%left tMULT tDIV tMOD tSHIFT_LEFT tSHIFT_RIGHT tAND tAMP_XOR
%left tUNARY

%error-verbose
%locations

%start program

%%

program : packages tSEMICOLON initial_dcls ;

packages : tPACKAGE tIDENTIFIER ;

initial_dcls : initial_dcls initial_dcl
             | %empty
             ;

initial_dcl : dcl
            | funcDcl
            ;

dcl : varDcl
    | typeDcl
    ;

varDcl : tVAR vars tSEMICOLON
       | tVAR tOPEN_PAREN varslist tCLOSE_PAREN tSEMICOLON
       ;

varslist : varslist vars tSEMICOLON
         | %empty
         ;

vars : idlist type tASSIGN exprlist
     | idlist tASSIGN exprlist
     | idlist type
     ;

idlist : id
       | id tCOMMA idlist
       ;

id : tIDENTIFIER
   | tINT
   | tFLOAT
   | tBOOL
   | tSTRING
   | tRUNE
   ;

arglist : tIDENTIFIER tCOMMA arglist
        | tIDENTIFIER
        ;

type : tINT
     | tFLOAT
     | tSTRING
     | tBOOL
     | tRUNE
     | tOPEN_SQ tCLOSE_SQ type
     | tOPEN_SQ tINTVAL tCLOSE_SQ type
     | tSTRUCT tOPEN_BRACE memberlist tCLOSE_BRACE
     | tIDENTIFIER
     ;

memberlist : memberlist member
           | %empty
           ;

member : idlist type tSEMICOLON
       ;

typeDcl : tTYPE types tSEMICOLON
        | tTYPE tOPEN_PAREN typeslist tCLOSE_PAREN tSEMICOLON
        ;

typeslist : typeslist types tSEMICOLON
          | %empty
          ;

types : tIDENTIFIER type ;

funcDcl : tFUNC tIDENTIFIER function
        ;

function : signature body ;

signature : parameters
          | parameters type
          | parameters tOPEN_PAREN type tCLOSE_PAREN
          ;

parameters : tOPEN_PAREN parameter_list tCLOSE_PAREN
           | tOPEN_PAREN tCLOSE_PAREN
           ;

parameter_list : parameter_list tCOMMA parameter
               | parameter
               ;

parameter : arglist type ;

body : block ;

block : simple_block tSEMICOLON ;

simple_block : tOPEN_BRACE statement_list tCLOSE_BRACE ;

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

print_stmt : tPRINT tOPEN_PAREN exprlist tCLOSE_PAREN tSEMICOLON
           | tPRINT tOPEN_PAREN tCLOSE_PAREN tSEMICOLON
           ;

println_stmt : tPRINTLN tOPEN_PAREN exprlist tCLOSE_PAREN tSEMICOLON
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

for_stmt : tFOR for_condition block ;

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

case : tCASE exprlist tCOLON statement_list
     | tDEFAULT tCOLON statement_list
     ;

break_stmt : tBREAK tSEMICOLON ;

continue_stmt : tCONTINUE tSEMICOLON ;

simple_stmt : simple_stmt_no_semi tSEMICOLON
            ;

simple_stmt_no_semi : expr
                    | expr tINC
                    | expr tDEC
                    | assignment_stmt
                    | shortDcl
                    | %empty
                    ;

assignment_stmt : exprlist assign exprlist ;

shortDcl : exprlist tDECL exprlist ;

exprlist : expr
         | exprlist tCOMMA expr
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
     | unary_op expr %prec tUNARY
     | append_expr
     | other_expressions
     ;

unary_op : tPLUS
         | tMINUS
         | tNOT
         | tXOR
         ;

append_expr : tAPPEND tOPEN_PAREN tIDENTIFIER tCOMMA expr tCLOSE_PAREN ;

other_expressions : function_call
                  | operand
                  | typecasting
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

function_call : other_expressions tOPEN_PAREN exprlist tCLOSE_PAREN
              | other_expressions tOPEN_PAREN tCLOSE_PAREN
              ;

typecasting : tINT tOPEN_PAREN expr tCLOSE_PAREN
            | tFLOAT tOPEN_PAREN expr tCLOSE_PAREN
            | tBOOL tOPEN_PAREN expr tCLOSE_PAREN
            | tRUNE tOPEN_PAREN expr tCLOSE_PAREN
            ;

array_index : tOPEN_SQ expr tCLOSE_SQ ;

slice_range : tOPEN_SQ expr tCOLON expr tCLOSE_SQ
            | tOPEN_SQ tCOLON expr tCLOSE_SQ
            | tOPEN_SQ expr tCOLON tCLOSE_SQ
            | tOPEN_SQ tCOLON tCLOSE_SQ
            | tOPEN_SQ expr tCOLON expr tCOLON expr tCLOSE_SQ
            | tOPEN_SQ tCOLON expr tCOLON expr tCLOSE_SQ
            ;

struct_selector : tPERIOD tIDENTIFIER ;

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

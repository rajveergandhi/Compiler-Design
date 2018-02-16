%{
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

extern int yylineno;
extern NODE *root;

int yylex();
void yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }
%}

%locations
%error-verbose

%code requires
{
    #include "tree.h"
}

%union {
    int int_val;
    float float_val;
    char *string_val;
    bool bool_val;
    NODE *node;
}

%type <node> program dcls dcl stmts stmt ifStmt expr
%type <string_val> types

%token <string_val> tSEMICOLON
%token <string_val> tCOLON
%token <string_val> tEQUALS
%token <string_val> tASTERISK
%token <string_val> tSLASH
%token <string_val> tPLUS
%token <string_val> tMINUS
%token <string_val> tOPENPAREN
%token <string_val> tCLOSEPAREN
%token <string_val> tOPENBRACE
%token <string_val> tCLOSEBRACE
%token <string_val> tEQUALSEQUALS
%token <string_val> tNOTEQUALS
%token <string_val> tLOGICALAND
%token <string_val> tLOGICALOR
%token <string_val> tNOT
%token <string_val> tVAR
%token <string_val> tWHILE
%token <string_val> tBOOLEAN
%token <string_val> tFLOAT
%token <string_val> tIF
%token <string_val> tELSE
%token <bool_val> tBOOLVAL
%token <string_val> tINT
%token <string_val> tPRINT
%token <string_val> tSTRING
%token <string_val> tREAD
%token <int_val> tINTVAL
%token <float_val> tFLOATVAL
%token <string_val> tSTRINGVAL
%token <string_val> tIDENTIFIER

%right tASSIGN
%left tLOGICALOR
%left tLOGICALAND
%left tEQUALSEQUALS tNOTEQUALS
%left tPLUS tMINUS
%left tASTERISK tSLASH
%left UNARYMINUS tNOT

%start program

%% 
program: dcls stmts {root = makePROGRAM($1,$2);}
       ;

dcls: dcl dcls {$$ = makeDCLS($1,$2);}
    | %empty { $$ = NULL; }
    ;

dcl: tVAR tIDENTIFIER tCOLON types tEQUALS expr tSEMICOLON {$$ = makeDCL($2,$4,$6);}
   ;

types: tBOOLEAN {$$ = $1;}
     | tINT {$$ = $1;}
     | tFLOAT {$$ = $1;}
     | tSTRING {$$ = $1;}
     ;

stmts: stmt stmts {$$ = makeSTMTS($1,$2);}
     | %empty { $$ = NULL; }
     ;

stmt: tREAD tIDENTIFIER tSEMICOLON {$$ = makeSTATEMENT_read($2);}
    | tPRINT expr tSEMICOLON {$$ = makeSTATEMENT_print($2);}
    | tIDENTIFIER tEQUALS expr tSEMICOLON {$$ = makeSTATEMENT_assign($1,$3);}
    | ifStmt {$$ = $1;}
    | tWHILE expr tOPENBRACE stmts tCLOSEBRACE {$$ = makeSTATEMENT_while($2,$4);}
    ;

ifStmt: tIF expr tOPENBRACE stmts tCLOSEBRACE {$$ = makeSTATEMENT_if($2,$4);}
      | tIF expr tOPENBRACE stmts tCLOSEBRACE tELSE tOPENBRACE stmts tCLOSEBRACE {$$ = makeSTATEMENT_ifElse($2,$4,$8);}
      ;

expr: tIDENTIFIER {$$ = makeEXP_identifier($1);}
    | tINTVAL {$$ = makeEXP_intLiteral($1);}
    | tFLOATVAL {$$ = makeEXP_floatLiteral($1);}
    | tBOOLVAL {$$ = makeEXP_boolLiteral($1);}
    | tSTRINGVAL {$$ = makeEXP_stringLiteral($1);}
    | expr tPLUS expr {$$ = makeEXP_binary(k_expressionKindAddition,$1,$3);}
    | expr tMINUS expr {$$ = makeEXP_binary(k_expressionKindSubtraction,$1,$3);}
    | expr tASTERISK expr {$$ = makeEXP_binary(k_expressionKindMultiplication,$1,$3);}
    | expr tSLASH expr {$$ = makeEXP_binary(k_expressionKindDivision,$1,$3);}
    | expr tEQUALSEQUALS expr {$$ = makeEXP_binary(k_expressionKindEqualsEquals,$1,$3);}
    | expr tNOTEQUALS expr {$$ = makeEXP_binary(k_expressionKindNotEquals,$1,$3);}
    | expr tLOGICALAND expr {$$ = makeEXP_binary(k_expressionKindLogicalAnd,$1,$3);}
    | expr tLOGICALOR expr {$$ = makeEXP_binary(k_expressionKindLogicalOr,$1,$3);}
    | tNOT expr {$$ = makeEXP_not($2);}
    | tOPENPAREN expr tCLOSEPAREN {$$ = $2;}
    | tMINUS expr %prec UNARYMINUS {$$ = makeEXP_unaryminus($2);}
    ;

%%

/* A scanner for GoLite, with the specifications defined in the class's documentation */

%{
#include <stdio.h>
#include <string.h>

#include "parser.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

extern int g_tokens;
%}

%option yylineno
%option noinput
%option nounput

DIGIT [0-9]
STRING_VALID_CHARS [ a-zA-Z0-9~@#$%\^&*\-+/`<>=_|'.,;:!?{}[\]()]|(\\[abfnrtv"\\])

%%

break        { if (g_tokens) printf("tBREAK\n"); return tBREAK; }
default      { if (g_tokens) printf("tDEFAULT\n"); return tDEFAULT; }
func         { if (g_tokens) printf("tFUNC\n"); return tFUNC; }
interface    { if (g_tokens) printf("tINTERFACE\n"); return tINTERFACE; }
select       { if (g_tokens) printf("tSELECT\n"); return tSELECT; }
case         { if (g_tokens) printf("tCASE\n"); return tCASE; }
defer        { if (g_tokens) printf("tDEFER\n"); return tDEFER; }
go           { if (g_tokens) printf("tGO\n"); return tGO; }
map          { if (g_tokens) printf("tMAP\n"); return tMAP; }
struct       { if (g_tokens) printf("tSTRUCT\n"); return tSTRUCT; }
chan         { if (g_tokens) printf("tCHAN\n"); return tCHAN; }
else         { if (g_tokens) printf("tELSE\n"); return tELSE; }
goto         { if (g_tokens) printf("tGOTO\n"); return tGOTO; }
package      { if (g_tokens) printf("tPACKAGE\n"); return tPACKAGE; }
switch       { if (g_tokens) printf("tSWITCH\n"); return tSWITCH; }
const        { if (g_tokens) printf("tCONST\n"); return tCONST; }
fallthrough  { if (g_tokens) printf("tFALLTHROUGH\n"); return tFALLTHROUGH; }
if           { if (g_tokens) printf("tIF\n"); return tIF; }
range        { if (g_tokens) printf("tRANGE\n"); return tRANGE; }
type         { if (g_tokens) printf("tTYPE\n"); return tTYPE; }
continue     { if (g_tokens) printf("tCONTINUE\n"); return tCONTINUE; }
for          { if (g_tokens) printf("tFOR\n"); return tFOR; }
import       { if (g_tokens) printf("tIMPORT\n"); return tIMPORT; }
return       { if (g_tokens) printf("tRETURN\n"); return tRETURN; }
var          { if (g_tokens) printf("tVAR\n"); return tVAR; }
print        { if (g_tokens) printf("tPRINT\n"); return tPRINT; }
println      { if (g_tokens) printf("tPRINTLN\n"); return tPRINTLN; }
append       { if (g_tokens) printf("tAPPEND\n"); return tAPPEND; }

[ \t\n\r]+   { /* whitespace is ignored */ }
"//".*$      { /* ignore comments */ }
";"          { if (g_tokens) printf("tSEMICOLON\n"); return tSEMICOLON; }
":"          { if (g_tokens) printf("tCOLON\n"); return tCOLON; }
"="          { if (g_tokens) printf("tEQUALS\n"); return tEQUALS; }
"*"          { if (g_tokens) printf("tASTERISK\n"); return tASTERISK; }
"/"          { if (g_tokens) printf("tSLASH\n"); return tSLASH; }
"+"          { if (g_tokens) printf("tPLUS\n"); return tPLUS; }
"-"          { if (g_tokens) printf("tMINUS\n"); return tMINUS; }
"("          { if (g_tokens) printf("tOPENPAREN\n"); return tOPENPAREN; }
")"          { if (g_tokens) printf("tCLOSEPAREN\n"); return tCLOSEPAREN; }
"{"          { if (g_tokens) printf("tOPENBRACE\n"); return tOPENBRACE; }
"}"          { if (g_tokens) printf("tCLOSEBRACE\n"); return tCLOSEBRACE; }
"=="         { if (g_tokens) printf("tEQUALSEQUALS\n"); return tEQUALSEQUALS; }
"!="         { if (g_tokens) printf("tNOTEQUALS\n"); return tNOTEQUALS; }
"&&"         { if (g_tokens) printf("tLOGICALAND\n"); return tLOGICALAND; }
"||"         { if (g_tokens) printf("tLOGICALOR\n"); return tLOGICALOR; }
"!"          { if (g_tokens) printf("tNOT\n"); return tNOT; }


int          { if (g_tokens) printf("tINT\n"); yylval.string_val = strdup(yytext); return tINT; }
float        { if (g_tokens) printf("tFLOAT\n"); yylval.string_val = strdup(yytext); return tFLOAT; }
string       { if (g_tokens) printf("tSTRING\n"); yylval.string_val = strdup(yytext); return tSTRING; }
boolean      { if (g_tokens) printf("tBOOLEAN\n"); yylval.string_val = strdup(yytext); return tBOOLEAN; }
var          { if (g_tokens) printf("tVAR\n"); return tVAR; }
else         { if (g_tokens) printf("tELSE\n"); return tELSE; }
while        { if (g_tokens) printf("tWHILE\n"); return tWHILE; }
if           { if (g_tokens) printf("tIF\n"); return tIF; }
print        { if (g_tokens) printf("tPRINT\n"); return tPRINT; }
read         { if (g_tokens) printf("tREAD\n"); return tREAD; }
TRUE|FALSE   { if (g_tokens) printf("tBOOLVAL(%s)\n", yytext); yylval.bool_val = strcmp(yytext, "TRUE") == 0 ? true : false; return tBOOLVAL; }


0|([1-9]{DIGIT}*)                   { if (g_tokens) printf("tINTVAL(%d)\n", atoi(yytext)); yylval.int_val = atoi(yytext); return tINTVAL; }
(0|([1-9]{DIGIT}*))"."{DIGIT}+      { if (g_tokens) printf("tFLOATVAL(%f)\n", atof(yytext)); yylval.float_val = atof(yytext); return tFLOATVAL; }
\"{STRING_VALID_CHARS}*\"           { if (g_tokens) printf("tSTRINGVAL(%s)\n", yytext); yylval.string_val = strdup(yytext); return tSTRINGVAL; }

[[:alpha:]_][[:alnum:]_]*           { if (g_tokens) printf("tIDENTIFIER(%s)\n", yytext); yylval.string_val = strdup(yytext); return tIDENTIFIER; }

{DIGIT}*                            { fprintf(stderr, "Error: (line %d) int starting with 0: '%s'\n", yylineno, yytext); exit(1); }
.                                   { fprintf(stderr, "Error: (line %d) unexpected character: '%s'\n", yylineno, yytext); exit(1); }

%%

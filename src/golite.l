/* A scanner for GoLite, with the specifications defined in the class's documentation */

%{
#include <stdio.h>
#include <string.h>

#include "parser.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;


extern int g_tokens;

int lastRead = 0;



int needsSemicolon(){
	switch(lastRead){
		case tCLOSE_PAREN:
		case tCLOSE_BRACE:
		case tCLOSE_SQ:
		case tRETURN:
		case tBREAK:
		case tCONTINUE:
		case tCONST:
		case tINT:
		case tFLOAT:
		case tBOOLEAN:
		case tSTRING:
		case tRUNE:
		case tINC:
		case tDEC:
		case tINTVAL:
		case tFLOATVAL:
		case tSTRINGVAL:
		case tRUNEVAL:
		case tRAWSTRVAL:
		case tFALLTHROUGH:
		case tIDENTIFIER:
			return 1;
		default:
			return 0;
	}
}



void formatRawString(){
	char *formattedStr = NULL;
	int pos = 0;
	while(yytext[pos] != '\0'){
		switch(yytext[pos]){
			case '\a':
				strcat(formattedStr,"\\a");
				break;
			case '\b':
				strcat(formattedStr,"\\b");
				break;
			case '\f':
				strcat(formattedStr,"\\f");
				break;
			case '\n':
				strcat(formattedStr,"\\n");
				break;
			case '\r':
				strcat(formattedStr,"\\r");
				break;
			case '\t':
				strcat(formattedStr,"\\t");
				break;
			case '\v':
				strcat(formattedStr,"\\v");
				break;
			case '\"':
				strcat(formattedStr,"\\\"");
				break;
			case '\\':
				strcat(formattedStr,"\\\\");
				formattedStr += yytext[++pos];
				break;
			default:
				formattedStr += yytext[pos];
				break;
		}
		pos++;
	}
	yytext = formattedStr;
}

%}

%x C_COMMENT
DIGIT [0-9]
OCTAL [0-7]
HEX [0-9A-Fa-f]
STRING_VALID_CHARS [ a-zA-Z0-9~@#$%\^&*\-+/`<>=_|'.,;:!?{}[\]()]|(\\[abfnrtv"\\])

%option yylineno
%option noinput
%option nounput

%%

"/*"		 	{ BEGIN(C_COMMENT); }
<C_COMMENT>. 	{ }
<C_COMMENT>"\n" { }
<C_COMMENT>"*/" { BEGIN(INITIAL); }



break        { if (g_tokens) printf("tBREAK\n"); lastRead = tBREAK; return tBREAK; }
default      { if (g_tokens) printf("tDEFAULT\n"); lastRead = tDEFAULT; return tDEFAULT; }
func         { if (g_tokens) printf("tFUNC\n"); lastRead = tFUNC; return tFUNC; }
interface    { if (g_tokens) printf("tINTERFACE\n"); lastRead = tINTERFACE; return tINTERFACE; }
select       { if (g_tokens) printf("tSELECT\n"); lastRead = tSELECT; return tSELECT; }
case         { if (g_tokens) printf("tCASE\n"); lastRead = tCASE; return tCASE; }
defer        { if (g_tokens) printf("tDEFER\n"); lastRead = tDEFER; return tDEFER; }
go           { if (g_tokens) printf("tGO\n"); lastRead = tGO; return tGO; }
map          { if (g_tokens) printf("tMAP\n"); lastRead = tMAP; return tMAP; }
struct       { if (g_tokens) printf("tSTRUCT\n"); lastRead = tSTRUCT; return tSTRUCT; }
chan         { if (g_tokens) printf("tCHAN\n"); lastRead = tCHAN; return tCHAN; }
else         { if (g_tokens) printf("tELSE\n"); lastRead = tELSE; return tELSE; }
goto         { if (g_tokens) printf("tGOTO\n"); lastRead = tGOTO; return tGOTO; }
package      { if (g_tokens) printf("tPACKAGE\n"); lastRead = tPACKAGE; return tPACKAGE; }
switch       { if (g_tokens) printf("tSWITCH\n"); lastRead = tSWITCH; return tSWITCH; }
const        { if (g_tokens) printf("tCONST\n"); lastRead = tCONST; return tCONST; }
fallthrough  { if (g_tokens) printf("tFALLTHROUGH\n"); lastRead = tFALLTHROUGH; return tFALLTHROUGH; }
if           { if (g_tokens) printf("tIF\n"); lastRead = tIF; return tIF; }
range        { if (g_tokens) printf("tRANGE\n"); lastRead = tRANGE; return tRANGE; }
type         { if (g_tokens) printf("tTYPE\n"); lastRead = tTYPE; return tTYPE; }
continue     { if (g_tokens) printf("tCONTINUE\n"); lastRead = tCONTINUE; return tCONTINUE; }
for          { if (g_tokens) printf("tFOR\n"); lastRead = tFOR; return tFOR; }
import       { if (g_tokens) printf("tIMPORT\n"); lastRead = tIMPORT; return tIMPORT; }
return       { if (g_tokens) printf("tRETURN\n"); lastRead = tRETURN; return tRETURN; }
var          { if (g_tokens) printf("tVAR\n"); lastRead = tVAR; return tVAR; }
print        { if (g_tokens) printf("tPRINT\n"); lastRead = tPRINT; return tPRINT; }
println      { if (g_tokens) printf("tPRINTLN\n"); lastRead = tPRINTLN; return tPRINTLN; }
append       { if (g_tokens) printf("tAPPEND\n"); lastRead = tAPPEND; return tAPPEND; }
read         { if (g_tokens) printf("tREAD\n"); lastRead = tREAD; return tREAD; }
\n 			 {if(needsSemicolon() == 1) {if (g_tokens) printf("tSEMICOLON\n"); lastRead = tSEMICOLON; return tSEMICOLON;}  }
[ \t]+   { /* whitespace is ignored */ }
"//"[^\r\n]*[\r\n<<EOF>>]      { }
";"          { if (g_tokens) printf("tSEMICOLON\n"); lastRead = tSEMICOLON; return tSEMICOLON; }
":"          { if (g_tokens) printf("tCOLON\n"); lastRead = tCOLON; return tCOLON; }
","          { if (g_tokens) printf("tCOMMA\n"); lastRead = tCOMMA; return tCOMMA; }
"."          { if (g_tokens) printf("tPERIOD\n"); lastRead = tPERIOD; return tPERIOD; }
"..."          { if (g_tokens) printf("tELLIPSIS\n"); lastRead = tELLIPSIS; return tELLIPSIS; }
"="          { if (g_tokens) printf("tASSIGN\n"); lastRead = tASSIGN; return tASSIGN; }
"*"          { if (g_tokens) printf("tMULT\n"); lastRead = tMULT; return tMULT; }
"/"          { if (g_tokens) printf("tDIV\n"); lastRead = tDIV; return tDIV; }
"+"          { if (g_tokens) printf("tPLUS\n"); lastRead = tPLUS; return tPLUS; }
"-"          { if (g_tokens) printf("tMINUS\n"); lastRead = tMINUS; return tMINUS; }
"%"          { if (g_tokens) printf("tMOD\n"); lastRead = tMOD; return tMOD; }
"&"			 { if (g_tokens) printf("tAND\n"); lastRead = tAND; return tAND; }
"|"			 { if (g_tokens) printf("tOR\n"); lastRead = tOR; return tOR; }
"^"          { if (g_tokens) printf("tXOR\n"); lastRead = tXOR; return tXOR; }
"!"          { if (g_tokens) printf("tNOT\n"); lastRead = tNOT; return tNOT; }
"("          { if (g_tokens) printf("tOPEN_PAREN\n"); lastRead = tOPEN_PAREN; return tOPEN_PAREN; }
")"          { if (g_tokens) printf("tCLOSE_PAREN\n"); lastRead = tCLOSE_PAREN; return tCLOSE_PAREN; }
"{"          { if (g_tokens) printf("tOPEN_BRACE\n"); lastRead = tOPEN_BRACE; return tOPEN_BRACE; }
"}"          { if (g_tokens) printf("tCLOSE_BRACE\n"); lastRead = tCLOSE_BRACE;return tCLOSE_BRACE; }
"["          { if (g_tokens) printf("tOPEN_SQ\n"); lastRead = tOPEN_SQ; return tOPEN_SQ; }
"]"          { if (g_tokens) printf("tCLOSE_SQ\n"); lastRead = tCLOSE_SQ; return tCLOSE_SQ; }
":="          { if (g_tokens) printf("tDECL\n"); lastRead = tDECL; return tDECL; }
"=="         { if (g_tokens) printf("tEQ_EQ\n"); lastRead = tEQ_EQ; return tEQ_EQ; }
"!="         { if (g_tokens) printf("tNOT_EQUALS\n"); lastRead = tNOT_EQUALS; return tNOT_EQUALS; }
"&&"         { if (g_tokens) printf("tLOGICAL_AND\n"); lastRead = tLOGICAL_AND; return tLOGICAL_AND; }
"||"         { if (g_tokens) printf("tLOGICAL_OR\n"); lastRead = tLOGICAL_OR; return tLOGICAL_OR; }
"+="          { if (g_tokens) printf("tPLUS_EQ\n"); lastRead = tPLUS_EQ; return tPLUS_EQ; }
"&="          { if (g_tokens) printf("tAMP_EQ\n"); lastRead = tAMP_EQ; return tAMP_EQ; }
"-="          { if (g_tokens) printf("tMINUS_EQ\n"); lastRead = tMINUS_EQ;return tMINUS_EQ; }
"%="          { if (g_tokens) printf("tMOD_EQ\n"); lastRead = tMOD_EQ; return tMOD_EQ; }
"*="          { if (g_tokens) printf("tMULT_EQ\n"); lastRead = tMULT_EQ; return tMULT_EQ; }
"/="          { if (g_tokens) printf("tDIV_EQ\n"); lastRead = tDIV_EQ; return tDIV_EQ; }
"|="          { if (g_tokens) printf("tOR_EQ\n"); lastRead = tOR_EQ; return tOR_EQ; }
"<"          { if (g_tokens) printf("tLT\n"); lastRead = tLT; return tLT; }
">"          { if (g_tokens) printf("tGT\n"); lastRead = tGT; return tGT; }
"<="          { if (g_tokens) printf("tLT_EQ\n"); lastRead = tLT_EQ; return tLT_EQ; }
">="          { if (g_tokens) printf("tGT_EQ\n"); lastRead = tGT_EQ; return tGT_EQ; }
"^="          { if (g_tokens) printf("tXOR_EQ\n"); lastRead = tXOR_EQ; return tXOR_EQ; }
"<-"          { if (g_tokens) printf("tDIR\n"); lastRead = tDIR; return tDIR; }
"<<"          { if (g_tokens) printf("tSHIFT_LEFT\n"); lastRead = tSHIFT_LEFT; return tSHIFT_LEFT; }
">>"          { if (g_tokens) printf("tSHIFT_RIGHT\n"); lastRead = tSHIFT_RIGHT; return tSHIFT_RIGHT; }
"<<="          { if (g_tokens) printf("tSHIFT_LEFT_EQ\n"); lastRead = tSHIFT_LEFT_EQ; return tSHIFT_LEFT_EQ; }
">>="          { if (g_tokens) printf("tSHIFT_RIGHT_EQ\n"); lastRead = tSHIFT_RIGHT_EQ; return tSHIFT_RIGHT_EQ; }
"++"          { if (g_tokens) printf("tINC\n"); lastRead = tINC; return tINC; }
"--"          { if (g_tokens) printf("tDEC\n"); lastRead = tDEC; return tDEC; }
"&^"          { if (g_tokens) printf("tAMP_XOR\n"); lastRead = tAMP_XOR; return tAMP_XOR; }
"&^="          { if (g_tokens) printf("tAMP_XOR_EQ\n"); lastRead = tAMP_XOR_EQ; return tAMP_XOR_EQ; }


int          { if (g_tokens) printf("tINT\n"); lastRead = tINT; return tINT; }
float64      { if (g_tokens) printf("tFLOAT\n"); lastRead = tFLOAT; return tFLOAT; }
string       { if (g_tokens) printf("tSTRING\n"); lastRead = tSTRING; return tSTRING; }
bool         { if (g_tokens) printf("tBOOLEAN\n"); lastRead = tBOOLEAN; return tBOOLEAN; }
rune		 { if (g_tokens) printf("tRUNE\n"); lastRead = tRUNE; return tRUNE;}




((0|[1-9]{DIGIT}*)|(0{OCTAL}+)|(0(x|X){HEX}+))                   { if (g_tokens) printf("tINTVAL(%d)\n", atoi(yytext)); lastRead = tINTVAL; return tINTVAL; }
({DIGIT}*)"."{DIGIT}*      			{ if (g_tokens) printf("tFLOATVAL(%f)\n", atof(yytext)); lastRead = tFLOATVAL; return tFLOATVAL; }
\"{STRING_VALID_CHARS}*\"           { if (g_tokens) printf("tSTRINGVAL(%s)\n", yytext); lastRead = tSTRINGVAL; return tSTRINGVAL; }
`(\\.|[^`])*`           { formatRawString(); if (g_tokens) printf("tRAWSTRVAL(%s)\n", yytext); lastRead = tRAWSTRVAL; return tRAWSTRVAL; }

[[:alpha:]_][[:alnum:]_]*           { if (g_tokens) printf("tIDENTIFIER(%s)\n", yytext); lastRead = tIDENTIFIER; return tIDENTIFIER; }

{DIGIT}*                            { fprintf(stderr, "Error: (line %d) int starting with 0: '%s'\n", yylineno, yytext); exit(1); }
.                                   { fprintf(stderr, "Error: (line %d) unexpected character: '%s'\n", yylineno, yytext); exit(1); }

%%

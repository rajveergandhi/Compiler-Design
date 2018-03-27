/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_GOLITE_TAB_H_INCLUDED
# define YY_YY_GOLITE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 17 "./src/golite.y" /* yacc.c:1915  */

    #include "tree.h"

#line 48 "golite.tab.h" /* yacc.c:1915  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tBREAK = 258,
    tDEFAULT = 259,
    tFUNC = 260,
    tINTERFACE = 261,
    tSELECT = 262,
    tCASE = 263,
    tDEFER = 264,
    tGO = 265,
    tMAP = 266,
    tSTRUCT = 267,
    tCHAN = 268,
    tELSE = 269,
    tGOTO = 270,
    tPACKAGE = 271,
    tSWITCH = 272,
    tCONST = 273,
    tFALLTHROUGH = 274,
    tIF = 275,
    tRANGE = 276,
    tTYPE = 277,
    tCONTINUE = 278,
    tFOR = 279,
    tIMPORT = 280,
    tRETURN = 281,
    tVAR = 282,
    tPRINT = 283,
    tPRINTLN = 284,
    tAPPEND = 285,
    tREAD = 286,
    tSEMICOLON = 287,
    tCOLON = 288,
    tCOMMA = 289,
    tPERIOD = 290,
    tELLIPSIS = 291,
    tASSIGN = 292,
    tMULT = 293,
    tDIV = 294,
    tPLUS = 295,
    tMINUS = 296,
    tAND = 297,
    tOR = 298,
    tMOD = 299,
    tXOR = 300,
    tNOT = 301,
    tOPEN_PAREN = 302,
    tCLOSE_PAREN = 303,
    tOPEN_BRACE = 304,
    tCLOSE_BRACE = 305,
    tOPEN_SQ = 306,
    tCLOSE_SQ = 307,
    tDECL = 308,
    tEQ_EQ = 309,
    tNOT_EQUALS = 310,
    tLOGICAL_AND = 311,
    tLOGICAL_OR = 312,
    tPLUS_EQ = 313,
    tAMP_EQ = 314,
    tMINUS_EQ = 315,
    tMOD_EQ = 316,
    tMULT_EQ = 317,
    tDIV_EQ = 318,
    tOR_EQ = 319,
    tLT = 320,
    tGT = 321,
    tLT_EQ = 322,
    tGT_EQ = 323,
    tXOR_EQ = 324,
    tARROW = 325,
    tSHIFT_LEFT = 326,
    tSHIFT_RIGHT = 327,
    tSHIFT_LEFT_EQ = 328,
    tSHIFT_RIGHT_EQ = 329,
    tINC = 330,
    tDEC = 331,
    tAMP_XOR = 332,
    tAMP_XOR_EQ = 333,
    tINTVAL = 334,
    tFLOATVAL = 335,
    tSTRINGVAL = 336,
    tRAWSTRVAL = 337,
    tIDENTIFIER = 338,
    tRUNEVAL = 339,
    UNARY = 340
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "./src/golite.y" /* yacc.c:1915  */

    int int_val;
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

#line 175 "golite.tab.h" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_GOLITE_TAB_H_INCLUDED  */

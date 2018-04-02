/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "./src/golite.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

extern int yylineno;
extern PROGRAM *root;

int yylex();
void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); exit(1); }

#line 79 "golite.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "golite.tab.h".  */
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
#line 17 "./src/golite.y" /* yacc.c:355  */

    #include "tree.h"

#line 113 "golite.tab.c" /* yacc.c:355  */

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
#line 24 "./src/golite.y" /* yacc.c:355  */

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

#line 240 "golite.tab.c" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 271 "golite.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   913

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  262

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   112,   115,   116,   119,   120,   123,   124,
     127,   128,   131,   132,   133,   136,   137,   140,   141,   144,
     145,   148,   151,   152,   153,   154,   155,   158,   159,   162,
     165,   166,   169,   172,   173,   174,   175,   178,   179,   182,
     185,   186,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   202,   203,   206,   207,   210,   211,   214,
     215,   216,   217,   220,   221,   224,   227,   228,   229,   230,
     233,   236,   237,   238,   239,   242,   243,   246,   247,   250,
     253,   256,   259,   260,   261,   262,   263,   264,   267,   268,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     303,   304,   305,   306,   307,   308,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tBREAK", "tDEFAULT", "tFUNC",
  "tINTERFACE", "tSELECT", "tCASE", "tDEFER", "tGO", "tMAP", "tSTRUCT",
  "tCHAN", "tELSE", "tGOTO", "tPACKAGE", "tSWITCH", "tCONST",
  "tFALLTHROUGH", "tIF", "tRANGE", "tTYPE", "tCONTINUE", "tFOR", "tIMPORT",
  "tRETURN", "tVAR", "tPRINT", "tPRINTLN", "tAPPEND", "tREAD",
  "tSEMICOLON", "tCOLON", "tCOMMA", "tPERIOD", "tELLIPSIS", "tASSIGN",
  "tMULT", "tDIV", "tPLUS", "tMINUS", "tAND", "tOR", "tMOD", "tXOR",
  "tNOT", "tOPEN_PAREN", "tCLOSE_PAREN", "tOPEN_BRACE", "tCLOSE_BRACE",
  "tOPEN_SQ", "tCLOSE_SQ", "tDECL", "tEQ_EQ", "tNOT_EQUALS",
  "tLOGICAL_AND", "tLOGICAL_OR", "tPLUS_EQ", "tAMP_EQ", "tMINUS_EQ",
  "tMOD_EQ", "tMULT_EQ", "tDIV_EQ", "tOR_EQ", "tLT", "tGT", "tLT_EQ",
  "tGT_EQ", "tXOR_EQ", "tARROW", "tSHIFT_LEFT", "tSHIFT_RIGHT",
  "tSHIFT_LEFT_EQ", "tSHIFT_RIGHT_EQ", "tINC", "tDEC", "tAMP_XOR",
  "tAMP_XOR_EQ", "tINTVAL", "tFLOATVAL", "tSTRINGVAL", "tRAWSTRVAL",
  "tIDENTIFIER", "tRUNEVAL", "UNARY", "$accept", "program", "package",
  "topLevelDecls", "topLevelDecl", "dcl", "varDcl", "varSpec",
  "varDclList", "idlist", "typeDcl", "typeSpec", "type", "memberlist",
  "member", "typeDclList", "funcDcl", "signature", "parameter_list",
  "block", "statement_list", "statement", "print_stmt", "println_stmt",
  "return_stmt", "if_stmt", "else_block", "for_stmt", "for_condition",
  "switch_stmt", "switch_condition", "caselist", "case", "break_stmt",
  "continue_stmt", "simple_stmt", "simple_stmt_no_semi", "expr_list",
  "expr", "other_expressions", "assign_op", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340
};
# endif

#define YYPACT_NINF -194

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-194)))

#define YYTABLE_NINF -89

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,   -65,    30,    15,    23,  -194,   -27,   -42,   -36,  -194,
      15,  -194,  -194,  -194,  -194,  -194,    13,   -18,    16,    36,
      14,    72,    75,    11,  -194,   -40,    53,    78,    71,    55,
      16,   -48,  -194,  -194,  -194,    86,    74,    14,  -194,   331,
      87,    16,    16,    79,   193,  -194,   -18,    94,    14,    80,
      16,    77,    14,    98,  -194,    85,   331,   331,   331,   331,
     331,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   580,    22,
     331,  -194,    99,    16,   105,   205,   343,   106,   205,   217,
      92,    95,    -7,  -194,    91,  -194,   103,   193,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,   113,   117,   535,
    -194,  -194,    16,   108,    14,  -194,  -194,    16,  -194,  -194,
      76,  -194,  -194,  -194,  -194,   620,   331,   331,   331,   331,
     331,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     331,   331,   331,   331,   331,   331,    81,    68,   331,  -194,
      14,  -194,  -194,   111,   331,   445,   331,   490,  -194,    53,
     123,   445,  -194,   363,   262,   274,   331,   129,  -194,  -194,
     331,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,   331,   130,  -194,  -194,  -194,   131,
    -194,  -194,  -194,  -194,   -32,   -32,  -194,   -32,  -194,   -32,
     836,   836,   828,   788,   836,   836,   836,   836,  -194,  -194,
    -194,  -194,  -194,   115,   660,  -194,    21,   780,   700,   193,
    -194,  -194,   286,  -194,   135,   122,   141,   126,  -194,  -194,
    -194,   780,  -194,   331,  -194,  -194,   142,   331,   128,    21,
     193,  -194,   133,   343,   404,  -194,   144,  -194,   147,   740,
     193,   148,  -194,  -194,   134,    20,  -194,   343,  -194,  -194,
    -194,  -194,   193,    40,     2,  -194,  -194,     2,  -194,  -194,
    -194,  -194
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     5,     0,     1,     0,     0,     0,     2,
       5,     6,     8,     9,     7,     3,     0,    31,     0,     0,
      16,    18,     0,     0,     4,     0,     0,     0,     0,     0,
       0,     0,    22,    21,    19,     0,     0,     0,    10,     0,
      12,    34,     0,     0,    41,    32,    31,     0,    28,     0,
       0,     0,    16,     0,    17,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   120,   118,    13,    88,   119,
       0,    36,    38,    33,     0,    74,    87,     0,    66,     0,
       0,     0,   120,    42,     0,    43,     0,    41,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     0,     0,    88,
      30,    20,     0,     0,    28,    26,    23,     0,    15,    11,
       0,   109,   110,   112,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,    35,    79,     0,    71,    73,     0,    88,    80,     0,
       0,    67,    58,     0,     0,     0,     0,     0,    40,    81,
       0,   126,   131,   127,   130,   128,   129,   132,   133,   134,
     135,    82,    83,   136,     0,     0,    25,    27,    24,     0,
     121,    89,    92,    93,    90,    91,   103,   105,    94,   106,
      99,   100,   107,   108,    95,    97,    96,    98,   102,   101,
     104,   125,   123,     0,     0,    37,    76,    72,     0,    41,
      60,    65,     0,    57,     0,     0,     0,     0,    86,    39,
      84,    85,    29,     0,   122,   124,     0,     0,     0,    76,
      41,    59,     0,    87,     0,    54,     0,    56,     0,     0,
      41,     0,    70,    75,     0,     0,    69,    87,    53,    55,
     113,    78,    41,     0,     0,    68,    77,     0,    63,    64,
      62,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,  -194,   175,  -194,    56,  -194,   178,   136,     1,
    -194,   182,    70,    88,  -194,   145,  -194,  -194,    54,   -26,
     -84,  -194,  -194,  -194,  -194,  -193,   -64,  -194,  -194,  -194,
    -194,   -34,  -194,  -194,  -194,    -5,   -76,   -20,   -43,  -194,
    -194
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,    10,    83,    12,    35,    36,    84,
      13,    27,    33,   103,   104,    28,    14,    26,    43,    85,
      86,    87,    88,    89,    90,    91,   260,    92,   149,    93,
     143,   228,   229,    94,    95,    96,    97,    98,    68,    69,
     174
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    99,   150,   158,    50,    17,   117,   118,    41,    23,
     121,    20,   123,   111,   112,   113,   114,   115,     4,    67,
       6,    23,    76,    29,     1,   226,    42,    37,    29,   227,
       5,    51,   145,   147,   254,   151,   153,     7,    54,   133,
     134,    18,     8,    21,    99,   135,   -18,    21,    39,   102,
     139,    44,   219,    23,   257,    15,    16,   136,    30,    11,
      25,   259,    31,    30,   259,    18,    11,    31,    34,   137,
     144,   146,   219,   138,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,    40,    32,   204,   181,    21,    55,    32,
      49,   207,    44,   208,    48,   102,    37,    38,    56,    57,
      46,    71,    72,    58,    59,    60,   202,   203,    52,    47,
     106,   210,    53,   211,    70,   232,   101,    73,   105,   107,
     109,   221,   110,   140,   215,   217,   218,   142,   148,   154,
     220,    42,   155,   141,   156,   159,   244,    61,    62,    63,
      64,    65,    66,   157,   160,   212,   251,   246,   176,   179,
     206,   219,   222,   224,   201,   223,    99,   235,   256,   234,
     236,   255,   175,   237,   238,   240,   248,   178,   242,   249,
     239,   252,   231,   245,   253,    24,    22,    99,   108,    19,
      99,   100,   177,   261,   205,   243,    74,    99,     0,     0,
       0,     0,     0,     0,    99,     0,     0,   241,     0,    99,
      75,     0,     0,    76,     0,     7,    77,    78,     0,    79,
       8,    80,    81,    55,     0,   -87,     0,     0,   258,     0,
       0,   258,     0,    56,    57,    55,     0,   -87,    58,    59,
      60,     0,    44,     0,     0,    56,    57,    55,     0,   152,
      58,    59,    60,     0,     0,     0,     0,    56,    57,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,     0,
       0,     0,    61,    62,    63,    64,    82,    66,     0,     0,
       0,     0,     0,     0,    61,    62,    63,    64,    82,    66,
       0,     0,    55,     0,     0,     0,    61,    62,    63,    64,
      65,    66,    56,    57,    55,     0,     0,    58,    59,    60,
     214,     0,     0,     0,    56,    57,    55,     0,   233,    58,
      59,    60,   216,     0,     0,     0,    56,    57,     0,     0,
       0,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,    61,    62,    63,    64,    65,    66,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    64,    65,    66,     0,
       0,    55,     0,     0,     0,    61,    62,    63,    64,    65,
      66,    56,    57,    55,     0,     0,    58,    59,    60,     0,
       0,     0,     0,    56,    57,     0,     0,     0,    58,    59,
      60,     0,     0,     0,     0,   213,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,     0,
      61,    62,    63,    64,    65,    66,     0,   125,   126,   127,
     128,     0,    61,    62,    63,    64,    82,    66,   129,   130,
     131,   132,     0,     0,   133,   134,   247,     0,     0,     0,
     135,     0,   117,   118,   119,   120,   121,   122,   123,   124,
       0,     0,     0,     0,     0,     0,     0,     0,   125,   126,
     127,   128,     0,     0,     0,     0,     0,     0,     0,   129,
     130,   131,   132,     0,     0,   133,   134,     0,     0,   116,
       0,   135,   -88,   117,   118,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,   161,   162,   163,   164,   165,   166,   167,
     129,   130,   131,   132,   168,     0,   133,   134,   169,   170,
     171,   172,   135,   173,   116,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,   209,
       0,     0,     0,     0,   125,   126,   127,   128,   161,   162,
     163,   164,   165,   166,   167,   129,   130,   131,   132,   168,
       0,   133,   134,   169,   170,   171,   172,   135,   173,   116,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,     0,     0,     0,     0,   125,
     126,   127,   128,   161,   162,   163,   164,   165,   166,   167,
     129,   130,   131,   132,   168,     0,   133,   134,   169,   170,
     171,   172,   135,   173,   116,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
       0,   133,   134,     0,     0,     0,     0,   135,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,   180,     0,
       0,     0,     0,     0,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
       0,   133,   134,     0,     0,     0,     0,   135,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,   225,     0,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
       0,   133,   134,     0,     0,     0,     0,   135,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,   230,
       0,     0,     0,     0,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
       0,   133,   134,     0,     0,     0,     0,   135,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,   250,     0,
       0,     0,     0,     0,   125,   126,   127,   128,     0,     0,
       0,     0,     0,     0,     0,   129,   130,   131,   132,     0,
       0,   133,   134,     0,     0,     0,     0,   135,   117,   118,
     119,   120,   121,   122,   123,   124,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,   125,   126,   127,   129,   130,   131,   132,     0,
       0,   133,   134,   129,   130,   131,   132,   135,     0,   133,
     134,     0,     0,     0,     0,   135,   117,   118,   119,   120,
     121,   122,   123,   124,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,     0,     0,   133,
     134,     0,     0,     0,     0,   135,     0,   133,   134,     0,
       0,     0,     0,   135
};

static const yytype_int16 yycheck[] =
{
      26,    44,    78,    87,    52,    47,    38,    39,    48,     8,
      42,    47,    44,    56,    57,    58,    59,    60,    83,    39,
       5,    20,    20,    12,    16,     4,    25,    34,    12,     8,
       0,    79,    75,    76,    14,    78,    79,    22,    37,    71,
      72,    83,    27,    83,    87,    77,    53,    83,    37,    48,
      70,    49,    32,    52,    14,    32,    83,    35,    47,     3,
      47,   254,    51,    47,   257,    83,    10,    51,    32,    47,
      75,    76,    32,    51,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,    23,    83,   138,   116,    83,    30,    83,
      30,   144,    49,   146,    49,   104,    34,    32,    40,    41,
      32,    41,    42,    45,    46,    47,    48,   137,    32,    48,
      50,   147,    48,   149,    37,   209,    32,    48,    48,    52,
      32,   174,    47,    34,   154,   155,   156,    32,    32,    47,
     160,   140,    47,    73,    53,    32,   230,    79,    80,    81,
      82,    83,    84,    50,    37,    32,   240,   233,    50,    83,
      49,    32,    32,    48,    83,    34,   209,    32,   252,   212,
      48,   247,   102,    32,    48,    33,    32,   107,    50,    32,
     223,    33,   208,    50,    50,    10,     8,   230,    52,     7,
     233,    46,   104,   257,   140,   229,     3,   240,    -1,    -1,
      -1,    -1,    -1,    -1,   247,    -1,    -1,   227,    -1,   252,
      17,    -1,    -1,    20,    -1,    22,    23,    24,    -1,    26,
      27,    28,    29,    30,    -1,    32,    -1,    -1,   254,    -1,
      -1,   257,    -1,    40,    41,    30,    -1,    32,    45,    46,
      47,    -1,    49,    -1,    -1,    40,    41,    30,    -1,    32,
      45,    46,    47,    -1,    -1,    -1,    -1,    40,    41,    -1,
      -1,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    80,    81,    82,    83,    84,
      -1,    -1,    30,    -1,    -1,    -1,    79,    80,    81,    82,
      83,    84,    40,    41,    30,    -1,    -1,    45,    46,    47,
      48,    -1,    -1,    -1,    40,    41,    30,    -1,    32,    45,
      46,    47,    48,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    80,    81,    82,    83,    84,    -1,
      -1,    30,    -1,    -1,    -1,    79,    80,    81,    82,    83,
      84,    40,    41,    30,    -1,    -1,    45,    46,    47,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,    46,
      47,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      79,    80,    81,    82,    83,    84,    -1,    54,    55,    56,
      57,    -1,    79,    80,    81,    82,    83,    84,    65,    66,
      67,    68,    -1,    -1,    71,    72,    32,    -1,    -1,    -1,
      77,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    34,
      -1,    77,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,    39,
      40,    41,    42,    43,    44,    45,    38,    39,    40,    41,
      42,    43,    44,    45,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    54,    55,    56,    65,    66,    67,    68,    -1,
      -1,    71,    72,    65,    66,    67,    68,    77,    -1,    71,
      72,    -1,    -1,    -1,    -1,    77,    38,    39,    40,    41,
      42,    43,    44,    45,    38,    39,    40,    41,    42,    43,
      44,    45,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    77,    -1,    71,    72,    -1,
      -1,    -1,    -1,    77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    87,    88,    83,     0,     5,    22,    27,    89,
      90,    91,    92,    96,   102,    32,    83,    47,    83,    97,
      47,    83,    93,    95,    89,    47,   103,    97,   101,    12,
      47,    51,    83,    98,    32,    93,    94,    34,    32,    37,
      98,    48,    95,   104,    49,   105,    32,    48,    49,    98,
      52,    79,    32,    48,    95,    30,    40,    41,    45,    46,
      47,    79,    80,    81,    82,    83,    84,   123,   124,   125,
      37,    98,    98,    48,     3,    17,    20,    23,    24,    26,
      28,    29,    83,    91,    95,   105,   106,   107,   108,   109,
     110,   111,   113,   115,   119,   120,   121,   122,   123,   124,
     101,    32,    95,    99,   100,    48,    98,    52,    94,    32,
      47,   124,   124,   124,   124,   124,    34,    38,    39,    40,
      41,    42,    43,    44,    45,    54,    55,    56,    57,    65,
      66,    67,    68,    71,    72,    77,    35,    47,    51,   123,
      34,    98,    32,   116,   121,   124,   121,   124,    32,   114,
     122,   124,    32,   124,    47,    47,    53,    50,   106,    32,
      37,    58,    59,    60,    61,    62,    63,    64,    69,    73,
      74,    75,    76,    78,   126,    98,    50,    99,    98,    83,
      48,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,    83,    48,   123,   124,   104,    49,   124,   124,    49,
     105,   105,    32,    32,    48,   123,    48,   123,   123,    32,
     123,   124,    32,    34,    48,    52,     4,     8,   117,   118,
      49,   105,   106,    32,   124,    32,    48,    32,    48,   124,
      33,   123,    50,   117,   106,    50,   122,    32,    32,    32,
      48,   106,    33,    50,    14,   122,   106,    14,   105,   111,
     112,   112
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    89,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    98,    98,    98,    98,    98,    99,    99,   100,
     101,   101,   102,   103,   103,   103,   103,   104,   104,   105,
     106,   106,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   111,   111,   112,   112,   113,   114,   114,   114,   114,
     115,   116,   116,   116,   116,   117,   117,   118,   118,   119,
     120,   121,   122,   122,   122,   122,   122,   122,   123,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   125,   125,   125,   125,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     0,     1,     1,     1,     1,
       3,     5,     2,     3,     4,     3,     0,     3,     1,     3,
       5,     2,     1,     3,     4,     4,     3,     2,     0,     3,
       3,     0,     4,     3,     2,     4,     3,     4,     2,     4,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     4,     5,     4,     3,     2,     4,
       3,     8,     7,     1,     1,     3,     0,     1,     5,     4,
       5,     1,     2,     1,     0,     2,     0,     4,     3,     2,
       2,     2,     2,     2,     3,     3,     3,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     6,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 109 "./src/golite.y" /* yacc.c:1661  */
    {root = makePROGRAM((yyvsp[-1].package),(yyvsp[0].topleveldecl));}
#line 1776 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 3:
#line 112 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.package) = makePACKAGE((yyvsp[-1].string_val));}
#line 1782 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 4:
#line 115 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.topleveldecl) = makeTOPLEVELDECLS((yyvsp[-1].topleveldecl), (yyvsp[0].topleveldecl));}
#line 1788 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 5:
#line 116 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.topleveldecl) = NULL;}
#line 1794 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 6:
#line 119 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.topleveldecl) = makeTOPLEVELDECL_dcl((yyvsp[0].dcl));}
#line 1800 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 7:
#line 120 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.topleveldecl) = makeTOPLEVELDECL_funcdcl((yyvsp[0].funcdcl));}
#line 1806 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 8:
#line 123 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.dcl) = makeDCLTYPE_var((yyvsp[0].vardcl));}
#line 1812 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 9:
#line 124 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.dcl) = makeDCLTYPE_type((yyvsp[0].typedcl));}
#line 1818 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 10:
#line 127 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = (yyvsp[-1].vardcl);}
#line 1824 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 11:
#line 128 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = (yyvsp[-2].vardcl);}
#line 1830 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 12:
#line 131 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = makeDCL_var((yyvsp[-1].idlist), (yyvsp[0].type), NULL);}
#line 1836 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 13:
#line 132 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = makeDCL_var((yyvsp[-2].idlist), NULL, (yyvsp[0].exprlist));}
#line 1842 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 14:
#line 133 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = makeDCL_var((yyvsp[-3].idlist), (yyvsp[-2].type), (yyvsp[0].exprlist));}
#line 1848 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 15:
#line 136 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = makeDCL_vars((yyvsp[-2].vardcl), (yyvsp[0].vardcl));}
#line 1854 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 16:
#line 137 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.vardcl) = NULL;}
#line 1860 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 17:
#line 140 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.idlist) = makeIDLIST((yyvsp[-2].string_val), (yyvsp[0].idlist));}
#line 1866 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 18:
#line 141 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.idlist) = makeIDLIST((yyvsp[0].string_val), NULL);}
#line 1872 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 19:
#line 144 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.typedcl) = (yyvsp[-1].typedcl);}
#line 1878 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 20:
#line 145 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.typedcl) = (yyvsp[-2].typedcl);}
#line 1884 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 21:
#line 148 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.typedcl) = makeDCL_type((yyvsp[-1].string_val), (yyvsp[0].type));}
#line 1890 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 22:
#line 151 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.type) = makeTYPE_identifier((yyvsp[0].string_val));}
#line 1896 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 23:
#line 152 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.type) = makeTYPE_slice((yyvsp[0].type));}
#line 1902 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 24:
#line 153 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.type) = makeTYPE_array((yyvsp[-2].int_val), (yyvsp[0].type));}
#line 1908 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 25:
#line 154 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.type) = makeTYPE_struct((yyvsp[-1].struct_type));}
#line 1914 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 26:
#line 155 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.type) = (yyvsp[-1].type);}
#line 1920 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 27:
#line 158 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.struct_type) = makeSTRUCTS((yyvsp[-1].struct_type), (yyvsp[0].struct_type));}
#line 1926 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 28:
#line 159 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.struct_type) = NULL;}
#line 1932 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 29:
#line 162 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.struct_type) = makeSTRUCT((yyvsp[-2].idlist), (yyvsp[-1].type));}
#line 1938 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 30:
#line 165 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.typedcl) = makeDCL_types((yyvsp[-2].typedcl), (yyvsp[0].typedcl));}
#line 1944 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 31:
#line 166 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.typedcl) = NULL;}
#line 1950 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 32:
#line 169 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.funcdcl) = makeFUNCTION((yyvsp[-2].string_val), (yyvsp[-1].func_signature), (yyvsp[0].block));}
#line 1956 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 33:
#line 172 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.func_signature) = makeFUNCTION_signature((yyvsp[-1].param_list), NULL);}
#line 1962 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 34:
#line 173 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.func_signature) = makeFUNCTION_signature(NULL, NULL);}
#line 1968 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 35:
#line 174 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.func_signature) = makeFUNCTION_signature((yyvsp[-2].param_list), (yyvsp[0].type));}
#line 1974 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 36:
#line 175 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.func_signature) = makeFUNCTION_signature(NULL, (yyvsp[0].type));}
#line 1980 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 37:
#line 178 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.param_list) = makeFUNCTION_parameterList((yyvsp[-3].idlist), (yyvsp[-2].type), (yyvsp[0].param_list));}
#line 1986 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 38:
#line 179 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.param_list) = makeFUNCTION_parameterList((yyvsp[-1].idlist), (yyvsp[0].type), NULL);}
#line 1992 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 39:
#line 182 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.block) = makeBLOCK((yyvsp[-2].statements));}
#line 1998 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 40:
#line 185 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statements) = makeSTATEMENTS((yyvsp[-1].statement), (yyvsp[0].statements));}
#line 2004 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 41:
#line 186 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statements) = NULL;}
#line 2010 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 42:
#line 189 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_dcl((yyvsp[0].dcl));}
#line 2016 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 43:
#line 190 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_block((yyvsp[0].block));}
#line 2022 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 44:
#line 191 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2028 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 45:
#line 192 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2034 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 46:
#line 193 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2040 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 47:
#line 194 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2046 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 48:
#line 195 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2052 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 49:
#line 196 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2058 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 50:
#line 197 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2064 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 51:
#line 198 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = (yyvsp[0].statement);}
#line 2070 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 52:
#line 199 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_simple((yyvsp[0].simple));}
#line 2076 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 53:
#line 202 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_print((yyvsp[-2].exprlist));}
#line 2082 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 54:
#line 203 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_print(NULL);}
#line 2088 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 55:
#line 206 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_println((yyvsp[-2].exprlist));}
#line 2094 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 56:
#line 207 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_println(NULL);}
#line 2100 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 57:
#line 210 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_return((yyvsp[-1].expr));}
#line 2106 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 58:
#line 211 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_return(NULL);}
#line 2112 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 59:
#line 214 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_if((yyvsp[-2].simple), (yyvsp[-1].expr), (yyvsp[0].block));}
#line 2118 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 60:
#line 215 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_if(NULL, (yyvsp[-1].expr), (yyvsp[0].block));}
#line 2124 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 61:
#line 216 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_ifElse((yyvsp[-6].simple), (yyvsp[-5].expr), (yyvsp[-3].statements), (yyvsp[0].else_block));}
#line 2130 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 62:
#line 217 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_ifElse(NULL, (yyvsp[-5].expr), (yyvsp[-3].statements), (yyvsp[0].else_block));}
#line 2136 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 63:
#line 220 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.else_block) = makeELSEBLOCK_block((yyvsp[0].block));}
#line 2142 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 64:
#line 221 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.else_block) = makeELSEBLOCK_if((yyvsp[0].statement));}
#line 2148 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 65:
#line 224 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_for((yyvsp[-1].for_condition), (yyvsp[0].block));}
#line 2154 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 66:
#line 227 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.for_condition) = makeSTATEMENT_forCondition_infinite();}
#line 2160 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 67:
#line 228 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.for_condition) = makeSTATEMENT_forCondition_while((yyvsp[0].expr));}
#line 2166 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 68:
#line 229 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.for_condition) = makeSTATEMENT_forCondition_threepart((yyvsp[-4].simple), (yyvsp[-2].expr), (yyvsp[0].simple));}
#line 2172 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 69:
#line 230 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.for_condition) = makeSTATEMENT_forCondition_threepart((yyvsp[-3].simple), NULL, (yyvsp[0].simple));}
#line 2178 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 70:
#line 233 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_switch((yyvsp[-3].switch_condition), (yyvsp[-1].switch_caselist));}
#line 2184 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 71:
#line 236 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_condition) = makeSTATEMENT_switchCondition((yyvsp[0].simple), NULL);}
#line 2190 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 72:
#line 237 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_condition) = makeSTATEMENT_switchCondition((yyvsp[-1].simple), (yyvsp[0].expr));}
#line 2196 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 73:
#line 238 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_condition) = makeSTATEMENT_switchCondition(NULL, (yyvsp[0].expr));}
#line 2202 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 74:
#line 239 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_condition) = makeSTATEMENT_switchCondition(NULL, NULL);}
#line 2208 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 75:
#line 242 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_caselist) = makeSTATEMENT_switchCases((yyvsp[-1].switch_caselist), (yyvsp[0].switch_caselist));}
#line 2214 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 76:
#line 243 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_caselist) = NULL;}
#line 2220 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 77:
#line 246 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_caselist) = makeSTATEMENT_switchCase((yyvsp[-2].exprlist), (yyvsp[0].statements));}
#line 2226 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 78:
#line 247 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.switch_caselist) = makeSTATEMENT_switchCaseDefault((yyvsp[0].statements));}
#line 2232 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 79:
#line 250 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_break();}
#line 2238 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 80:
#line 253 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.statement) = makeSTATEMENT_continue();}
#line 2244 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 81:
#line 256 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = (yyvsp[-1].simple);}
#line 2250 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 82:
#line 259 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = makeSIMPLE_inc((yyvsp[-1].expr));}
#line 2256 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 83:
#line 260 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = makeSIMPLE_dec((yyvsp[-1].expr));}
#line 2262 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 84:
#line 261 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = makeSIMPLE_assignment((yyvsp[-2].exprlist), (yyvsp[-1].string_val), (yyvsp[0].exprlist));}
#line 2268 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 85:
#line 262 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = makeSIMPLE_OPassignment((yyvsp[-2].expr), (yyvsp[-1].string_val), (yyvsp[0].expr));}
#line 2274 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 86:
#line 263 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = makeSIMPLE_shortdcl((yyvsp[-2].idlist), (yyvsp[0].exprlist));}
#line 2280 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 87:
#line 264 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.simple) = makeSIMPLE_empty();}
#line 2286 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 88:
#line 267 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.exprlist) = makeEXPRLIST((yyvsp[0].expr), NULL);}
#line 2292 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 89:
#line 268 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.exprlist) = makeEXPRLIST((yyvsp[-2].expr), (yyvsp[0].exprlist));}
#line 2298 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 90:
#line 271 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindPlus, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2304 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 91:
#line 272 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindMinus, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2310 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 92:
#line 273 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindMult, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2316 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 93:
#line 274 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindDiv, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2322 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 94:
#line 275 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindMod, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2328 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 95:
#line 276 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindLT, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2334 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 96:
#line 277 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindLT_EQ, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2340 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 97:
#line 278 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindGT, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2346 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 98:
#line 279 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindGT_EQ, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2352 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 99:
#line 280 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindEQ_EQ, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2358 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 100:
#line 281 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindNotEquals, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2364 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 101:
#line 282 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindShift_Right, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2370 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 102:
#line 283 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindShift_Left, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2376 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 103:
#line 284 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindAnd, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2382 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 104:
#line 285 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindAMP_XOR, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2388 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 105:
#line 286 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindOr, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2394 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 106:
#line 287 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindXor, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2400 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 107:
#line 288 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindLogicalAnd, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2406 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 108:
#line 289 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_binary(expressionKindLogicalOr, (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2412 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 109:
#line 290 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_unary(expressionKindPlusUnary, (yyvsp[0].expr));}
#line 2418 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 110:
#line 291 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_unary(expressionKindMinusUnary, (yyvsp[0].expr));}
#line 2424 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 111:
#line 292 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_unary(expressionKindNotUnary, (yyvsp[0].expr));}
#line 2430 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 112:
#line 293 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_unary(expressionKindXorUnary, (yyvsp[0].expr));}
#line 2436 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 113:
#line 294 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_append((yyvsp[-3].string_val), (yyvsp[-1].expr));}
#line 2442 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 114:
#line 295 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_intLiteral((yyvsp[0].int_val));}
#line 2448 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 115:
#line 296 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_floatLiteral((yyvsp[0].float_val));}
#line 2454 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 116:
#line 297 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_stringLiteral((yyvsp[0].string_val), true);}
#line 2460 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 117:
#line 298 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_stringLiteral((yyvsp[0].string_val), false);}
#line 2466 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 118:
#line 299 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_runeLiteral((yyvsp[0].string_val));}
#line 2472 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 119:
#line 300 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.expr) = makeEXPR_other((yyvsp[0].other_expr));}
#line 2478 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 120:
#line 303 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.other_expr) = makeEXPR_identifier((yyvsp[0].string_val));}
#line 2484 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 121:
#line 304 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.other_expr) = makeEXPR_paren((yyvsp[-1].expr));}
#line 2490 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 122:
#line 305 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.other_expr) = makeEXPR_funcCall((yyvsp[-3].other_expr), (yyvsp[-1].exprlist));}
#line 2496 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 123:
#line 306 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.other_expr) = makeEXPR_funcCall((yyvsp[-2].other_expr), NULL);}
#line 2502 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 124:
#line 307 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.other_expr) = makeEXPR_index((yyvsp[-3].other_expr), (yyvsp[-1].expr));}
#line 2508 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 125:
#line 308 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.other_expr) = makeEXPR_structAccess((yyvsp[-2].other_expr), (yyvsp[0].string_val));}
#line 2514 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 126:
#line 311 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2520 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 127:
#line 312 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2526 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 128:
#line 313 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2532 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 129:
#line 314 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2538 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 130:
#line 315 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2544 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 131:
#line 316 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2550 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 132:
#line 317 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2556 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 133:
#line 318 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2562 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 134:
#line 319 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2568 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 135:
#line 320 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2574 "golite.tab.c" /* yacc.c:1661  */
    break;

  case 136:
#line 321 "./src/golite.y" /* yacc.c:1661  */
    {(yyval.string_val) = (yyvsp[0].string_val);}
#line 2580 "golite.tab.c" /* yacc.c:1661  */
    break;


#line 2584 "golite.tab.c" /* yacc.c:1661  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 324 "./src/golite.y" /* yacc.c:1906  */


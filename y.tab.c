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

#include<stdio.h>
#include<stdlib.h>

extern int yylineno;
int yylex();
void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); }

#line 75 "y.tab.c" /* yacc.c:339  */

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
    tINT = 334,
    tFLOAT = 335,
    tSTRING = 336,
    tBOOLEAN = 337,
    tRUNE = 338,
    tUNARY = 339,
    tINTVAL = 340,
    tFLOATVAL = 341,
    tSTRINGVAL = 342,
    tRAWSTRVAL = 343,
    tIDENTIFIER = 344,
    tRUNEVAL = 345
  };
#endif
/* Tokens.  */
#define tBREAK 258
#define tDEFAULT 259
#define tFUNC 260
#define tINTERFACE 261
#define tSELECT 262
#define tCASE 263
#define tDEFER 264
#define tGO 265
#define tMAP 266
#define tSTRUCT 267
#define tCHAN 268
#define tELSE 269
#define tGOTO 270
#define tPACKAGE 271
#define tSWITCH 272
#define tCONST 273
#define tFALLTHROUGH 274
#define tIF 275
#define tRANGE 276
#define tTYPE 277
#define tCONTINUE 278
#define tFOR 279
#define tIMPORT 280
#define tRETURN 281
#define tVAR 282
#define tPRINT 283
#define tPRINTLN 284
#define tAPPEND 285
#define tREAD 286
#define tSEMICOLON 287
#define tCOLON 288
#define tCOMMA 289
#define tPERIOD 290
#define tELLIPSIS 291
#define tASSIGN 292
#define tMULT 293
#define tDIV 294
#define tPLUS 295
#define tMINUS 296
#define tAND 297
#define tOR 298
#define tMOD 299
#define tXOR 300
#define tNOT 301
#define tOPEN_PAREN 302
#define tCLOSE_PAREN 303
#define tOPEN_BRACE 304
#define tCLOSE_BRACE 305
#define tOPEN_SQ 306
#define tCLOSE_SQ 307
#define tDECL 308
#define tEQ_EQ 309
#define tNOT_EQUALS 310
#define tLOGICAL_AND 311
#define tLOGICAL_OR 312
#define tPLUS_EQ 313
#define tAMP_EQ 314
#define tMINUS_EQ 315
#define tMOD_EQ 316
#define tMULT_EQ 317
#define tDIV_EQ 318
#define tOR_EQ 319
#define tLT 320
#define tGT 321
#define tLT_EQ 322
#define tGT_EQ 323
#define tXOR_EQ 324
#define tARROW 325
#define tSHIFT_LEFT 326
#define tSHIFT_RIGHT 327
#define tSHIFT_LEFT_EQ 328
#define tSHIFT_RIGHT_EQ 329
#define tINC 330
#define tDEC 331
#define tAMP_XOR 332
#define tAMP_XOR_EQ 333
#define tINT 334
#define tFLOAT 335
#define tSTRING 336
#define tBOOLEAN 337
#define tRUNE 338
#define tUNARY 339
#define tINTVAL 340
#define tFLOATVAL 341
#define tSTRINGVAL 342
#define tRAWSTRVAL 343
#define tIDENTIFIER 344
#define tRUNEVAL 345

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "./src/golite.y" /* yacc.c:355  */

    int int_val;
	double float_val;
	char *string_val;
    char *rune_val;
	char *ident;

#line 300 "y.tab.c" /* yacc.c:355  */
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



/* Copy the second part of user declarations.  */

#line 331 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   1214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  91
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  292

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   345

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
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    61,    63,    64,    67,    68,    71,    72,
      75,    76,    79,    80,    83,    84,    85,    88,    89,    92,
      93,    94,    95,    96,    97,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   111,   112,   115,   117,   118,   121,
     122,   125,   127,   130,   132,   133,   136,   137,   140,   141,
     144,   146,   148,   150,   152,   153,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   169,   170,   173,
     174,   177,   178,   181,   182,   185,   186,   189,   190,   193,
     195,   196,   199,   200,   203,   205,   206,   207,   208,   211,
     213,   213,   215,   217,   219,   221,   222,   223,   224,   225,
     228,   230,   232,   233,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   260,   261,   262,   263,
     266,   268,   269,   270,   271,   272,   273,   276,   277,   278,
     279,   280,   281,   282,   285,   286,   289,   290,   291,   292,
     295,   297,   298,   299,   300,   301,   302,   305,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318
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
  "tAMP_XOR_EQ", "tINT", "tFLOAT", "tSTRING", "tBOOLEAN", "tRUNE",
  "tUNARY", "tINTVAL", "tFLOATVAL", "tSTRINGVAL", "tRAWSTRVAL",
  "tIDENTIFIER", "tRUNEVAL", "$accept", "program", "packages",
  "initial_dcls", "initial_dcl", "dcl", "varDcl", "varslist", "vars",
  "idlist", "id", "type", "memberlist", "member", "typeDcl", "typeslist",
  "types", "funcDcl", "function", "signature", "parameters",
  "parameter_list", "parameter", "body", "block", "simple_block",
  "statement_list", "statement", "print_stmt", "println_stmt",
  "return_stmt", "if_stmt", "if_condition", "else_block", "for_stmt",
  "for_condition", "condition", "switch_stmt", "switch_condition",
  "caselist", "case", "break_stmt", "continue_stmt", "simple_stmt",
  "simple_stmt_no_semi", "assignment_stmt", "shortDcl", "exprlist", "expr",
  "unary_op", "append_expr", "other_expressions", "operand",
  "function_call", "typecasting", "array_index", "slice_range",
  "struct_selector", "assign", YY_NULLPTR
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345
};
# endif

#define YYPACT_NINF -143

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-143)))

#define YYTABLE_NINF -96

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,   -70,    32,     2,  -143,  -143,  -143,     8,   -47,   -23,
      20,  -143,  -143,  -143,  -143,  -143,    29,  -143,   105,    48,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,    51,    86,    47,
     185,  -143,    37,   105,   -19,    55,   -42,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,   225,  -143,   392,    60,    39,
    -143,   105,   -28,  -143,  -143,  -143,  -143,    75,  -143,    76,
      84,  -143,   105,    61,    92,    93,    79,  -143,  -143,  -143,
    -143,   392,    80,    83,    85,    87,  -143,  -143,  -143,  -143,
      49,  -143,   101,  1081,   392,  -143,    88,  -143,  -143,  -143,
    -143,   392,  -143,  -143,    39,  -143,    65,  -143,  -143,  -143,
      81,  -143,   105,  -143,  -143,    54,   801,   392,   392,   392,
     392,    57,   211,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,  -143,   230,  -143,  -143,   101,  -143,   106,
     392,   392,   108,   392,   291,   102,   110,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
     126,  -143,  -143,   760,   451,  -143,   105,  -143,  -143,   125,
    -143,   841,   881,   921,   961,  -143,  -143,   -27,  1081,  -143,
    -143,   159,   159,  -143,   159,  -143,   159,  1137,  1137,  1129,
    1089,  1137,  1137,  1137,  1137,  -143,  -143,  -143,   303,   655,
    -143,   122,   392,   492,    37,   392,   533,  -143,    37,  -143,
     142,   574,  -143,   615,   316,   367,  -143,  -143,   392,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
     392,  -143,  -143,  -143,   392,  -143,  -143,  -143,  -143,  -143,
    -143,   695,   379,  -143,    10,  1081,  -143,    -9,  1081,  -143,
     392,  -143,   145,   -17,   146,   -12,   101,   101,    30,   392,
    -143,  -143,   735,  -143,   392,   129,   147,   -16,   150,  1081,
    -143,   151,  -143,   157,  -143,  1001,   392,  -143,   101,  -143,
    -143,  -143,  -143,  -143,   392,  -143,  -143,  -143,  1041,   199,
    -143,  -143
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,     5,     2,     0,     0,
       0,     4,     6,     8,     9,     7,     0,    40,     0,     0,
      13,    20,    21,    23,    22,    24,    19,     0,     0,    17,
       0,    42,     0,    44,     0,     0,     0,    25,    26,    27,
      28,    29,    33,    41,    37,     0,    10,     0,    16,     0,
      47,     0,     0,    49,    55,    43,    51,     0,    45,     0,
       0,    35,     0,     0,     0,     0,     0,   126,   127,   129,
     128,     0,     0,     0,     0,     0,   139,   140,   141,   143,
     138,   142,    15,   102,     0,   124,   125,   131,   132,   133,
     136,     0,    18,    50,     0,    46,     0,    52,    38,    39,
       0,    30,     0,    11,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,     0,   134,   135,    14,    48,     0,
      88,     0,     0,    83,     0,     0,     0,    53,    56,    57,
      54,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       0,    98,    99,     0,   102,    32,     0,    34,    31,     0,
     137,     0,     0,     0,     0,   157,   145,     0,   103,   106,
     107,   104,   105,   117,   119,   108,   120,   113,   114,   121,
     122,   109,   111,   110,   112,   116,   115,   118,     0,     0,
      92,     0,    85,   102,     0,     0,   102,    93,     0,    80,
       0,   102,    72,     0,     0,     0,    94,   158,     0,   159,
     164,   160,   163,   161,   162,   165,   166,   167,   168,   169,
       0,    96,    97,    36,     0,   146,   147,   148,   149,   144,
     154,     0,     0,   150,     0,    86,    73,     0,    75,    79,
      83,    71,     0,     0,     0,     0,   101,   100,     0,     0,
     152,   153,     0,    91,     0,     0,     0,     0,     0,    82,
      68,     0,    70,     0,   130,     0,     0,   151,    90,    84,
      55,    77,    78,    74,     0,    67,    69,   156,     0,    89,
      81,   155
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,  -143,  -143,  -143,   184,  -143,  -143,   154,   -21,
    -143,   -25,  -143,  -143,  -143,  -143,   161,  -143,  -143,  -143,
    -143,  -143,   111,  -143,   -32,    -4,   -76,  -143,  -143,  -143,
    -143,   -61,  -143,  -143,  -143,  -143,   -41,  -143,  -143,  -143,
    -143,  -143,  -143,  -129,  -142,  -143,  -143,   -22,   -69,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,    11,   148,    13,    45,    27,    28,
      29,    43,   100,   167,    14,    34,    19,    15,    31,    32,
      33,    52,    53,    55,   149,    57,    96,   150,   151,   152,
     153,   154,   204,   283,   155,   208,   209,   156,   201,   265,
     266,   157,   158,   159,   160,   161,   162,   163,    83,    84,
      85,    86,    87,    88,    89,   135,   136,    90,   230
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,   210,   106,    48,   141,   267,    94,   113,    58,    51,
      62,   202,   205,     8,   263,   133,     1,   113,   264,     4,
      95,   239,   113,    97,    17,    82,    93,   164,    92,    59,
       9,   271,     5,    54,     6,    10,   273,   101,   171,   172,
     173,   174,    16,    63,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   113,   199,    18,    20,   139,   137,
      18,   203,   206,    51,   211,   213,    30,   168,   274,   166,
      44,    49,   140,    46,   111,   141,    54,     9,   142,   143,
     177,   144,    10,   145,   146,    66,   112,    91,    35,    21,
      22,    23,    24,    25,    61,    67,    68,    97,    98,    26,
      69,    70,    71,   102,    54,   147,    99,    35,    21,    22,
      23,    24,    25,    47,   103,   104,   105,   107,    26,   241,
     108,   165,   109,   245,   110,   113,   248,    36,   200,   134,
     207,   233,   290,   169,    72,    73,   175,    74,    75,   214,
      76,    77,    78,    79,    80,    81,    36,   215,   216,   234,
      21,    22,    23,    24,    25,    37,    38,    39,    40,    41,
      26,   244,   246,   262,   250,    42,   249,   270,   272,   279,
     280,   269,   284,   285,    37,    38,    39,    40,    41,   286,
     275,    12,   253,   255,    42,    60,   256,   114,   115,    65,
     247,   118,   139,   120,   289,   138,   282,   288,   257,   268,
       0,     0,   258,     0,     0,   164,   140,     0,     0,   141,
     164,     9,   142,   143,     0,   144,    10,   145,   146,    66,
     130,   131,     0,    50,     0,   281,   132,     0,     0,    67,
      68,    66,   278,     0,    69,    70,    71,     0,    54,     0,
       0,    67,    68,     0,     0,     0,    69,    70,    71,   176,
      66,     0,     0,   198,    21,    22,    23,    24,    25,     0,
      67,    68,     0,    64,    26,    69,    70,    71,    72,    73,
       0,    74,    75,     0,    76,    77,    78,    79,    80,    81,
      72,    73,     0,    74,    75,     0,    76,    77,    78,    79,
      80,    81,     0,     0,    21,    22,    23,    24,    25,    72,
      73,     0,    74,    75,    26,    76,    77,    78,    79,    80,
      81,    66,     0,   212,     0,     0,     0,     0,     0,     0,
       0,    67,    68,    66,     0,     0,    69,    70,    71,     0,
       0,     0,     0,    67,    68,     0,    66,     0,    69,    70,
      71,     0,     0,     0,     0,   240,    67,    68,     0,     0,
       0,    69,    70,    71,   252,     0,     0,     0,     0,     0,
      72,    73,     0,    74,    75,     0,    76,    77,    78,    79,
      80,    81,    72,    73,     0,    74,    75,     0,    76,    77,
      78,    79,    80,    81,     0,    72,    73,    66,    74,    75,
       0,    76,    77,    78,    79,    80,    81,    67,    68,    66,
       0,     0,    69,    70,    71,   254,     0,     0,     0,    67,
      68,     0,    66,     0,    69,    70,    71,     0,     0,     0,
       0,   261,    67,    68,     0,     0,     0,    69,    70,    71,
       0,     0,     0,     0,     0,     0,    72,    73,     0,    74,
      75,     0,    76,    77,    78,    79,    80,    81,    72,    73,
       0,    74,    75,     0,    76,    77,    78,    79,    80,    81,
       0,    72,    73,     0,    74,    75,     0,    76,    77,    78,
      79,    80,    81,   -95,     0,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
     -95,     0,     0,     0,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,   -95,     0,   231,   232,   132,     0,
     114,   115,   116,   117,   118,   119,   120,   121,     0,     0,
       0,   -87,     0,     0,     0,     0,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,     0,     0,   130,   131,   -95,     0,   231,   232,   132,
       0,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,   -76,     0,     0,     0,     0,   122,   123,   124,
     125,     0,     0,     0,     0,     0,     0,     0,   126,   127,
     128,   129,     0,     0,   130,   131,   -95,     0,   231,   232,
     132,     0,   114,   115,   116,   117,   118,   119,   120,   121,
       0,     0,     0,   -82,     0,     0,     0,     0,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,   126,
     127,   128,   129,     0,     0,   130,   131,   251,     0,   231,
     232,   132,     0,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,     0,     0,   130,   131,   242,     0,
       0,     0,   132,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,   243,     0,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,     0,     0,   130,   131,   259,     0,
       0,     0,   132,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,   260,     0,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,     0,     0,   130,   131,   276,     0,
       0,     0,   132,   114,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,     0,     0,   277,     0,   122,
     123,   124,   125,     0,   113,     0,     0,   217,     0,     0,
     126,   127,   128,   129,     0,     0,   130,   131,     0,     0,
       0,     0,   132,   218,     0,     0,     0,     0,   219,   220,
     221,   222,   223,   224,   225,     0,     0,     0,     0,   226,
       0,     0,     0,   227,   228,     0,     0,     0,   229,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   170,
       0,     0,     0,     0,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   235,
       0,     0,     0,     0,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   236,
       0,     0,     0,     0,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   237,
       0,     0,     0,     0,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,   238,
       0,     0,     0,     0,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,   287,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,   291,     0,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,   130,   131,     0,     0,     0,     0,   132,   114,
     115,   116,   117,   118,   119,   120,   121,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,   122,   123,   124,   126,   127,   128,   129,
       0,     0,   130,   131,   126,   127,   128,   129,   132,     0,
     130,   131,     0,     0,     0,     0,   132,   114,   115,   116,
     117,   118,   119,   120,   121,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   127,   128,   129,     0,     0,
     130,   131,     0,     0,     0,     0,   132,     0,   130,   131,
       0,     0,     0,     0,   132
};

static const yytype_int16 yycheck[] =
{
      32,   143,    71,    28,    20,    14,    34,    34,    33,    30,
      52,   140,   141,     5,     4,    84,    16,    34,     8,    89,
      48,    48,    34,    32,    47,    47,    51,    96,    49,    48,
      22,    48,     0,    49,    32,    27,    48,    62,   107,   108,
     109,   110,    89,    85,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,    34,   134,    89,    47,     3,    91,
      89,   140,   141,    94,   143,   144,    47,   102,    48,   100,
      32,    34,    17,    32,    35,    20,    49,    22,    23,    24,
     112,    26,    27,    28,    29,    30,    47,    37,    12,    79,
      80,    81,    82,    83,    49,    40,    41,    32,    32,    89,
      45,    46,    47,    52,    49,    50,    32,    12,    79,    80,
      81,    82,    83,    37,    32,    32,    47,    47,    89,   198,
      47,    50,    47,   202,    47,    34,   205,    51,    32,    51,
      32,   166,   284,    89,    79,    80,    89,    82,    83,    47,
      85,    86,    87,    88,    89,    90,    51,    47,    32,    34,
      79,    80,    81,    82,    83,    79,    80,    81,    82,    83,
      89,    49,   204,   242,    32,    89,   208,    32,    32,    50,
      33,   250,    32,    32,    79,    80,    81,    82,    83,    32,
     259,     7,   214,   215,    89,    34,   218,    38,    39,    45,
     204,    42,     3,    44,   280,    94,   267,   276,   230,   250,
      -1,    -1,   234,    -1,    -1,   284,    17,    -1,    -1,    20,
     289,    22,    23,    24,    -1,    26,    27,    28,    29,    30,
      71,    72,    -1,    48,    -1,   267,    77,    -1,    -1,    40,
      41,    30,   264,    -1,    45,    46,    47,    -1,    49,    -1,
      -1,    40,    41,    -1,    -1,    -1,    45,    46,    47,    48,
      30,    -1,    -1,    33,    79,    80,    81,    82,    83,    -1,
      40,    41,    -1,    48,    89,    45,    46,    47,    79,    80,
      -1,    82,    83,    -1,    85,    86,    87,    88,    89,    90,
      79,    80,    -1,    82,    83,    -1,    85,    86,    87,    88,
      89,    90,    -1,    -1,    79,    80,    81,    82,    83,    79,
      80,    -1,    82,    83,    89,    85,    86,    87,    88,    89,
      90,    30,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    30,    -1,    -1,    45,    46,    47,    -1,
      -1,    -1,    -1,    40,    41,    -1,    30,    -1,    45,    46,
      47,    -1,    -1,    -1,    -1,    52,    40,    41,    -1,    -1,
      -1,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      79,    80,    -1,    82,    83,    -1,    85,    86,    87,    88,
      89,    90,    79,    80,    -1,    82,    83,    -1,    85,    86,
      87,    88,    89,    90,    -1,    79,    80,    30,    82,    83,
      -1,    85,    86,    87,    88,    89,    90,    40,    41,    30,
      -1,    -1,    45,    46,    47,    48,    -1,    -1,    -1,    40,
      41,    -1,    30,    -1,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    40,    41,    -1,    -1,    -1,    45,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    -1,    82,
      83,    -1,    85,    86,    87,    88,    89,    90,    79,    80,
      -1,    82,    83,    -1,    85,    86,    87,    88,    89,    90,
      -1,    79,    80,    -1,    82,    83,    -1,    85,    86,    87,
      88,    89,    90,    32,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    32,    -1,    75,    76,    77,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    71,    72,    32,    -1,    75,    76,    77,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    -1,    -1,    71,    72,    32,    -1,    75,    76,
      77,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    71,    72,    32,    -1,    75,
      76,    77,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    71,    72,    33,    -1,
      -1,    -1,    77,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    71,    72,    33,    -1,
      -1,    -1,    77,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    71,    72,    33,    -1,
      -1,    -1,    77,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,
      55,    56,    57,    -1,    34,    -1,    -1,    37,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    53,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    78,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    38,
      39,    40,    41,    42,    43,    44,    45,    38,    39,    40,
      41,    42,    43,    44,    45,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    54,    55,    56,    65,    66,    67,    68,
      -1,    -1,    71,    72,    65,    66,    67,    68,    77,    -1,
      71,    72,    -1,    -1,    -1,    -1,    77,    38,    39,    40,
      41,    42,    43,    44,    45,    38,    39,    40,    41,    42,
      43,    44,    45,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    71,    72,
      -1,    -1,    -1,    -1,    77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    92,    93,    89,     0,    32,    94,     5,    22,
      27,    95,    96,    97,   105,   108,    89,    47,    89,   107,
      47,    79,    80,    81,    82,    83,    89,    99,   100,   101,
      47,   109,   110,   111,   106,    12,    51,    79,    80,    81,
      82,    83,    89,   102,    32,    98,    32,    37,   102,    34,
      48,   100,   112,   113,    49,   114,   115,   116,   102,    48,
     107,    49,    52,    85,    48,    99,    30,    40,    41,    45,
      46,    47,    79,    80,    82,    83,    85,    86,    87,    88,
      89,    90,   138,   139,   140,   141,   142,   143,   144,   145,
     148,    37,   100,   102,    34,    48,   117,    32,    32,    32,
     103,   102,    52,    32,    32,    47,   139,    47,    47,    47,
      47,    35,    47,    34,    38,    39,    40,    41,    42,    43,
      44,    45,    54,    55,    56,    57,    65,    66,    67,    68,
      71,    72,    77,   139,    51,   146,   147,   138,   113,     3,
      17,    20,    23,    24,    26,    28,    29,    50,    96,   115,
     118,   119,   120,   121,   122,   125,   128,   132,   133,   134,
     135,   136,   137,   138,   139,    50,   100,   104,   102,    89,
      48,   139,   139,   139,   139,    89,    48,   138,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,    33,   139,
      32,   129,   134,   139,   123,   134,   139,    32,   126,   127,
     135,   139,    32,   139,    47,    47,    32,    37,    53,    58,
      59,    60,    61,    62,    63,    64,    69,    73,    74,    78,
     149,    75,    76,   102,    34,    48,    48,    48,    48,    48,
      52,   139,    33,    52,    49,   139,   115,   116,   139,   115,
      32,    32,    48,   138,    48,   138,   138,   138,   138,    33,
      52,    52,   139,     4,     8,   130,   131,    14,   127,   139,
      32,    48,    32,    48,    48,   139,    33,    52,   138,    50,
      33,   115,   122,   124,    32,    32,    32,    52,   139,   117,
     135,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    91,    92,    93,    94,    94,    95,    95,    96,    96,
      97,    97,    98,    98,    99,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   101,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   104,   105,   105,   106,
     106,   107,   108,   109,   110,   110,   111,   111,   112,   112,
     113,   114,   115,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   125,
     126,   126,   127,   127,   128,   129,   129,   129,   129,   130,
     131,   131,   132,   133,   134,   135,   135,   135,   135,   135,
     136,   137,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   140,   140,   140,   140,
     141,   142,   142,   142,   142,   142,   142,   143,   143,   143,
     143,   143,   143,   143,   144,   144,   145,   145,   145,   145,
     146,   147,   147,   147,   147,   147,   147,   148,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     0,     1,     1,     1,     1,
       3,     5,     3,     0,     4,     3,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     4,     1,     2,     0,     2,     3,     5,     3,
       0,     2,     3,     2,     1,     2,     3,     2,     3,     1,
       2,     1,     2,     3,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     4,     5,
       4,     3,     2,     3,     5,     2,     1,     1,     1,     3,
       1,     5,     1,     0,     5,     1,     2,     1,     0,     3,
       2,     1,     2,     2,     2,     1,     2,     2,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       6,     1,     1,     1,     2,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     4,     4,     4,
       3,     5,     4,     4,     3,     7,     6,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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
      
#line 1920 "y.tab.c" /* yacc.c:1661  */
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
#line 321 "./src/golite.y" /* yacc.c:1906  */


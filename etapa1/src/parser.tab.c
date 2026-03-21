/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_PR_INT = 258,
     TK_PR_FLOAT = 259,
     TK_PR_BOOL = 260,
     TK_PR_CHAR = 261,
     TK_PR_IF = 262,
     TK_PR_ELSE = 263,
     TK_PR_WHILE = 264,
     TK_PR_FOR = 265,
     TK_PR_RETURN = 266,
     TK_PR_VOID = 267,
     TK_PR_ARRAY = 268,
     TK_PR_OF = 269,
     TK_PR_LET = 270,
     TK_PR_FUN = 271,
     TK_PR_DO = 272,
     TK_PR_PRINT = 273,
     TK_PR_READ = 274,
     TK_LIT_TRUE = 275,
     TK_LIT_FALSE = 276,
     TK_OC_LE = 277,
     TK_OC_GE = 278,
     TK_OC_EQ = 279,
     TK_OC_NE = 280,
     TK_OC_AND = 281,
     TK_OC_OR = 282,
     TK_OC_ARROW = 283,
     TK_OC_ASSIGN = 284,
     TK_OC_PLUSEQ = 285,
     TK_OC_MINUSEQ = 286,
     TK_ERROR = 287,
     TK_ID = 288,
     TK_LIT_INT = 289,
     TK_LIT_FLOAT = 290,
     TK_LIT_CHAR = 291,
     TK_LIT_STRING = 292,
     UMINUS = 293
   };
#endif
/* Tokens.  */
#define TK_PR_INT 258
#define TK_PR_FLOAT 259
#define TK_PR_BOOL 260
#define TK_PR_CHAR 261
#define TK_PR_IF 262
#define TK_PR_ELSE 263
#define TK_PR_WHILE 264
#define TK_PR_FOR 265
#define TK_PR_RETURN 266
#define TK_PR_VOID 267
#define TK_PR_ARRAY 268
#define TK_PR_OF 269
#define TK_PR_LET 270
#define TK_PR_FUN 271
#define TK_PR_DO 272
#define TK_PR_PRINT 273
#define TK_PR_READ 274
#define TK_LIT_TRUE 275
#define TK_LIT_FALSE 276
#define TK_OC_LE 277
#define TK_OC_GE 278
#define TK_OC_EQ 279
#define TK_OC_NE 280
#define TK_OC_AND 281
#define TK_OC_OR 282
#define TK_OC_ARROW 283
#define TK_OC_ASSIGN 284
#define TK_OC_PLUSEQ 285
#define TK_OC_MINUSEQ 286
#define TK_ERROR 287
#define TK_ID 288
#define TK_LIT_INT 289
#define TK_LIT_FLOAT 290
#define TK_LIT_CHAR 291
#define TK_LIT_STRING 292
#define UMINUS 293




/* Copy the first part of user declarations.  */
#line 38 "src/parser.y"

/* -----------------------------------------------------------------------
 * Seção de cabeçalho C — incluída no início de parser.tab.c
 * ----------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

/* Declarações externas do scanner */
extern int   yylex(void);
extern int   yylineno;
extern char *yytext;

/* Tabela de símbolos global — definida em main.c */
extern symtab_t *global_symtab;

/* Raiz da AST — preenchida pela regra do símbolo inicial */
ast_node_t *ast_root = NULL;

/* Função de erro do bison */
void yyerror(const char *msg)
{
    fprintf(stderr, "[ERRO SINTÁTICO] linha %d: %s (token: '%s')\n",
            yylineno, msg, yytext);
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 70 "src/parser.y"
{
    char        *sval;   /* string (lexemas de ID, LIT_INT, LIT_FLOAT, etc.) */
    ast_node_t  *node;   /* nó da AST */
    int          ival;   /* inteiro (usado para armazenar yylineno) */
}
/* Line 193 of yacc.c.  */
#line 207 "src/parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 220 "src/parser.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   323

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    44,     2,     2,
      48,    49,    42,    40,    50,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    51,
      38,     2,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,     2,     2,     2,     2,
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
      35,    36,    37,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      25,    26,    28,    30,    34,    37,    41,    48,    50,    52,
      54,    56,    58,    62,    65,    67,    70,    73,    75,    77,
      79,    81,    83,    85,    87,    89,    91,    93,    98,   102,
     106,   110,   116,   124,   131,   141,   144,   147,   150,   155,
     159,   163,   167,   171,   175,   179,   183,   187,   191,   195,
     199,   203,   207,   210,   213,   217,   222,   227,   231,   233,
     235,   236,   238,   240,   242,   247,   251,   253,   255,   257,
     259,   261
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    -1,    -1,    58,    -1,    57,    58,
      -1,    59,    -1,    63,    -1,    64,    -1,    16,    65,    33,
      48,    60,    49,    66,    -1,    -1,    61,    -1,    62,    -1,
      61,    50,    62,    -1,    65,    33,    -1,    65,    33,    51,
      -1,    13,    34,    14,    65,    33,    51,    -1,     3,    -1,
       4,    -1,     5,    -1,     6,    -1,    12,    -1,    52,    67,
      53,    -1,    52,    53,    -1,    68,    -1,    67,    68,    -1,
      69,    51,    -1,    70,    -1,    72,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    71,    -1,    73,    -1,    74,
      -1,    75,    -1,    15,    33,    29,    80,    -1,    83,    29,
      80,    -1,    83,    30,    80,    -1,    83,    31,    80,    -1,
       7,    48,    80,    49,    66,    -1,     7,    48,    80,    49,
      66,     8,    66,    -1,     9,    48,    80,    49,    17,    66,
      -1,    10,    48,    72,    51,    80,    51,    72,    49,    66,
      -1,    11,    80,    -1,    18,    80,    -1,    19,    83,    -1,
      33,    48,    81,    49,    -1,    80,    40,    80,    -1,    80,
      41,    80,    -1,    80,    42,    80,    -1,    80,    43,    80,
      -1,    80,    44,    80,    -1,    80,    38,    80,    -1,    80,
      39,    80,    -1,    80,    22,    80,    -1,    80,    23,    80,
      -1,    80,    24,    80,    -1,    80,    25,    80,    -1,    80,
      26,    80,    -1,    80,    27,    80,    -1,    45,    80,    -1,
      41,    80,    -1,    48,    80,    49,    -1,    33,    48,    81,
      49,    -1,    33,    47,    80,    54,    -1,    33,    28,    33,
      -1,    33,    -1,    84,    -1,    -1,    82,    -1,    80,    -1,
      33,    -1,    33,    47,    80,    54,    -1,    33,    28,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,    20,
      -1,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   136,   136,   143,   151,   153,   158,   159,   160,   166,
     178,   179,   183,   184,   189,   200,   211,   223,   224,   225,
     226,   227,   232,   237,   246,   248,   254,   255,   260,   261,
     262,   263,   264,   265,   270,   271,   272,   277,   290,   296,
     302,   312,   318,   329,   340,   352,   361,   370,   379,   390,
     391,   392,   393,   394,   397,   398,   399,   400,   401,   402,
     411,   419,   426,   433,   440,   443,   451,   459,   468,   475,
     480,   481,   495,   502,   507,   513,   524,   525,   526,   527,
     528,   529
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_PR_INT", "TK_PR_FLOAT", "TK_PR_BOOL",
  "TK_PR_CHAR", "TK_PR_IF", "TK_PR_ELSE", "TK_PR_WHILE", "TK_PR_FOR",
  "TK_PR_RETURN", "TK_PR_VOID", "TK_PR_ARRAY", "TK_PR_OF", "TK_PR_LET",
  "TK_PR_FUN", "TK_PR_DO", "TK_PR_PRINT", "TK_PR_READ", "TK_LIT_TRUE",
  "TK_LIT_FALSE", "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE",
  "TK_OC_AND", "TK_OC_OR", "TK_OC_ARROW", "TK_OC_ASSIGN", "TK_OC_PLUSEQ",
  "TK_OC_MINUSEQ", "TK_ERROR", "TK_ID", "TK_LIT_INT", "TK_LIT_FLOAT",
  "TK_LIT_CHAR", "TK_LIT_STRING", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "UMINUS", "'['", "'('", "')'", "','", "';'", "'{'", "'}'",
  "']'", "$accept", "program", "toplevel_list", "toplevel_decl",
  "fun_decl", "param_list", "param_list_ne", "param", "var_decl",
  "array_decl", "type_spec", "block", "stmt_list", "stmt", "simple_stmt",
  "compound_stmt", "var_local", "assign_stmt", "if_stmt", "while_stmt",
  "for_stmt", "return_stmt", "print_stmt", "read_stmt", "call_stmt",
  "expr", "expr_list", "expr_list_ne", "lvalue", "literal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    60,    62,
      43,    45,    42,    47,    37,    33,   293,    91,    40,    41,
      44,    59,   123,   125,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    57,    57,    58,    58,    58,    59,
      60,    60,    61,    61,    62,    63,    64,    65,    65,    65,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    71,    72,    72,
      72,    73,    73,    74,    75,    76,    77,    78,    79,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    83,    83,    83,    84,    84,    84,    84,
      84,    84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     7,
       0,     1,     1,     3,     2,     3,     6,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       3,     5,     7,     6,     9,     2,     2,     2,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     4,     4,     3,     1,     1,
       0,     1,     1,     1,     4,     3,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    17,    18,    19,    20,    21,     0,     0,     0,     2,
       4,     6,     7,     8,     0,     0,     0,     1,     5,     0,
       0,     0,    15,     0,    10,     0,     0,    11,    12,     0,
      16,     0,     0,    14,     0,     9,    13,     0,     0,     0,
       0,     0,     0,     0,    73,    23,     0,    24,     0,    27,
      33,    28,    34,    35,    36,    29,    30,    31,    32,     0,
       0,     0,     0,    80,    81,    68,    76,    77,    78,    79,
       0,     0,     0,    45,    69,     0,    46,    73,    47,     0,
       0,    70,    22,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    63,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,    72,     0,    71,    38,    39,    40,     0,
       0,     0,    67,     0,     0,    64,    56,    57,    58,    59,
      60,    61,    54,    55,    49,    50,    51,    52,    53,    37,
      74,    48,    41,     0,     0,    66,    65,     0,    43,     0,
      42,     0,     0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    26,    27,    28,    12,    13,
      14,    35,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,   113,   114,   115,    59,    74
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -110
static const yytype_int16 yypact[] =
{
     307,  -110,  -110,  -110,  -110,  -110,   -32,    91,     5,   307,
    -110,  -110,  -110,  -110,   -24,    -1,   -19,  -110,  -110,   -34,
      91,   -29,  -110,     9,    91,   -28,   -20,    -6,  -110,    12,
    -110,     0,    91,  -110,    -3,  -110,  -110,     1,     3,     8,
     124,    24,   124,    40,    -8,  -110,    65,  -110,    30,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,    -4,
     124,   124,    40,  -110,  -110,     7,  -110,  -110,  -110,  -110,
     124,   124,   124,   235,  -110,    56,   235,   -10,  -110,    53,
     124,   124,  -110,  -110,  -110,   124,   124,   124,   151,   179,
      48,    67,   124,   124,  -110,  -110,   207,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,  -110,    66,   235,    52,  -110,   235,   235,   235,     0,
      85,   124,  -110,    89,    68,  -110,    81,    81,   144,   144,
     265,   242,    81,    81,    35,    35,  -110,  -110,  -110,   235,
    -110,  -110,   111,     0,   112,  -110,  -110,     0,  -110,    40,
    -110,    77,     0,  -110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,   131,  -110,  -110,  -110,   109,  -110,  -110,
       4,  -109,  -110,    96,  -110,  -110,  -110,   -62,  -110,  -110,
    -110,  -110,  -110,  -110,  -110,   -39,    54,  -110,   103,  -110
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      90,    73,    15,    76,    37,    17,    38,    39,    40,    19,
     142,    16,    41,    20,    21,    42,    43,    22,    79,    24,
      79,    88,    89,    30,    23,    85,    86,    87,    29,    31,
      44,    94,    95,    96,   148,    91,    29,    80,   150,    80,
      81,   112,    25,   153,    32,    33,   116,   117,   118,    60,
      45,    61,    34,   123,    92,    93,    62,    75,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,    37,    77,    38,    39,    40,   107,   108,   109,
      41,    84,   144,    42,    43,   110,   111,   151,    97,    98,
      99,   100,   101,   102,     1,     2,     3,     4,    44,   121,
     122,   141,   143,     5,   103,   104,   105,   106,   107,   108,
     109,    97,    98,    99,   100,   101,   102,   146,    82,   147,
     140,   105,   106,   107,   108,   109,   152,   103,   104,   105,
     106,   107,   108,   109,    97,    98,    99,   100,   101,   102,
      18,    36,    83,   145,    63,    64,    78,   124,     0,     0,
     103,   104,   105,   106,   107,   108,   109,    65,    66,    67,
      68,    69,     0,   149,     0,    70,    97,    98,     0,    71,
       0,     0,    72,    97,    98,    99,   100,   101,   102,     0,
       0,     0,   103,   104,   105,   106,   107,   108,   109,   103,
     104,   105,   106,   107,   108,   109,     0,     0,     0,     0,
     119,    97,    98,    99,   100,   101,   102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,   105,
     106,   107,   108,   109,     0,     0,     0,     0,   120,    97,
      98,    99,   100,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   103,   104,   105,   106,   107,
     108,   109,     0,     0,     0,     0,   125,    97,    98,    99,
     100,   101,   102,     0,    97,    98,    99,   100,   101,     0,
       0,     0,     0,   103,   104,   105,   106,   107,   108,   109,
     103,   104,   105,   106,   107,   108,   109,    97,    98,    99,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,   105,   106,   107,   108,   109,
       1,     2,     3,     4,     0,     0,     0,     0,     0,     5,
       6,     0,     0,     7
};

static const yytype_int16 yycheck[] =
{
      62,    40,    34,    42,     7,     0,     9,    10,    11,    33,
     119,     7,    15,    14,    33,    18,    19,    51,    28,    48,
      28,    60,    61,    51,    20,    29,    30,    31,    24,    49,
      33,    70,    71,    72,   143,    28,    32,    47,   147,    47,
      48,    80,    33,   152,    50,    33,    85,    86,    87,    48,
      53,    48,    52,    92,    47,    48,    48,    33,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     7,    33,     9,    10,    11,    42,    43,    44,
      15,    51,   121,    18,    19,    29,    33,   149,    22,    23,
      24,    25,    26,    27,     3,     4,     5,     6,    33,    51,
      33,    49,    17,    12,    38,    39,    40,    41,    42,    43,
      44,    22,    23,    24,    25,    26,    27,    49,    53,     8,
      54,    40,    41,    42,    43,    44,    49,    38,    39,    40,
      41,    42,    43,    44,    22,    23,    24,    25,    26,    27,
       9,    32,    46,    54,    20,    21,    43,    93,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    33,    34,    35,
      36,    37,    -1,    51,    -1,    41,    22,    23,    -1,    45,
      -1,    -1,    48,    22,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    22,    23,    24,
      25,    26,    27,    -1,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      38,    39,    40,    41,    42,    43,    44,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    12,
      13,    -1,    -1,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    12,    13,    16,    56,    57,
      58,    59,    63,    64,    65,    34,    65,     0,    58,    33,
      14,    33,    51,    65,    48,    33,    60,    61,    62,    65,
      51,    49,    50,    33,    52,    66,    62,     7,     9,    10,
      11,    15,    18,    19,    33,    53,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    83,
      48,    48,    48,    20,    21,    33,    34,    35,    36,    37,
      41,    45,    48,    80,    84,    33,    80,    33,    83,    28,
      47,    48,    53,    68,    51,    29,    30,    31,    80,    80,
      72,    28,    47,    48,    80,    80,    80,    22,    23,    24,
      25,    26,    27,    38,    39,    40,    41,    42,    43,    44,
      29,    33,    80,    80,    81,    82,    80,    80,    80,    49,
      49,    51,    33,    80,    81,    49,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      54,    49,    66,    17,    80,    54,    49,     8,    66,    51,
      66,    72,    49,    66
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 137 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_PROGRAM, NULL, 1);
            (yyval.node)->children[0] = (yyvsp[(1) - (1)].node);
            ast_root = (yyval.node);
        ;}
    break;

  case 3:
#line 143 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_PROGRAM, NULL, 1);
            ast_root = (yyval.node);
        ;}
    break;

  case 4:
#line 152 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 5:
#line 154 "src/parser.y"
    { (yyval.node) = ast_append((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 6:
#line 158 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 7:
#line 159 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 8:
#line 160 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 9:
#line 167 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_FUN_DECL, (yyvsp[(3) - (7)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (7)].node);   /* tipo de retorno */
            (yyval.node)->children[1] = (yyvsp[(5) - (7)].node);   /* lista de parâmetros (pode ser NULL) */
            (yyval.node)->children[2] = (yyvsp[(7) - (7)].node);   /* corpo (bloco) */
            free((yyvsp[(3) - (7)].sval));
        ;}
    break;

  case 10:
#line 178 "src/parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 11:
#line 179 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node);   ;}
    break;

  case 12:
#line 183 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 13:
#line 184 "src/parser.y"
    { (yyval.node) = ast_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 14:
#line 190 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_PARAM, (yyvsp[(2) - (2)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(1) - (2)].node);
            free((yyvsp[(2) - (2)].sval));
        ;}
    break;

  case 15:
#line 201 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_VAR_DECL, (yyvsp[(2) - (3)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(1) - (3)].node);
            free((yyvsp[(2) - (3)].sval));
        ;}
    break;

  case 16:
#line 212 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_ARRAY_DECL, (yyvsp[(5) - (6)].sval), yylineno);
            (yyval.node)->children[0] = ast_new(AST_LIT_INT, (yyvsp[(2) - (6)].sval), yylineno);  /* tamanho */
            (yyval.node)->children[1] = (yyvsp[(4) - (6)].node);                                    /* tipo base */
            free((yyvsp[(2) - (6)].sval));
            free((yyvsp[(5) - (6)].sval));
        ;}
    break;

  case 17:
#line 223 "src/parser.y"
    { (yyval.node) = ast_new(AST_SYMBOL, "int",   yylineno); ;}
    break;

  case 18:
#line 224 "src/parser.y"
    { (yyval.node) = ast_new(AST_SYMBOL, "float", yylineno); ;}
    break;

  case 19:
#line 225 "src/parser.y"
    { (yyval.node) = ast_new(AST_SYMBOL, "bool",  yylineno); ;}
    break;

  case 20:
#line 226 "src/parser.y"
    { (yyval.node) = ast_new(AST_SYMBOL, "char",  yylineno); ;}
    break;

  case 21:
#line 227 "src/parser.y"
    { (yyval.node) = ast_new(AST_SYMBOL, "void",  yylineno); ;}
    break;

  case 22:
#line 233 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_BLOCK, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (3)].node);
        ;}
    break;

  case 23:
#line 238 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_BLOCK, NULL, yylineno);
        ;}
    break;

  case 24:
#line 247 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 25:
#line 249 "src/parser.y"
    { (yyval.node) = ast_append((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 26:
#line 254 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 27:
#line 255 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 28:
#line 260 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 29:
#line 261 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 30:
#line 262 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 31:
#line 263 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 32:
#line 264 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 33:
#line 265 "src/parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 34:
#line 270 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 35:
#line 271 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 36:
#line 272 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 37:
#line 278 "src/parser.y"
    {
            /* Por simplicidade na Etapa 1, não cria nó separado.
             * O nome é inserido na tabela de símbolos automaticamente
             * pelo scanner. Na Etapa 2 você criará o nó VAR_DECL aqui. */
            symtab_insert(global_symtab, (yyvsp[(2) - (4)].sval), yylineno);
            ast_free((yyvsp[(4) - (4)].node));  /* descarta expr por ora */
            free((yyvsp[(2) - (4)].sval));
        ;}
    break;

  case 38:
#line 291 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_ASSIGN, ":=", yylineno);
            (yyval.node)->children[0] = (yyvsp[(1) - (3)].node);
            (yyval.node)->children[1] = (yyvsp[(3) - (3)].node);
        ;}
    break;

  case 39:
#line 297 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_ASSIGN, "+=", yylineno);
            (yyval.node)->children[0] = (yyvsp[(1) - (3)].node);
            (yyval.node)->children[1] = (yyvsp[(3) - (3)].node);
        ;}
    break;

  case 40:
#line 303 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_ASSIGN, "-=", yylineno);
            (yyval.node)->children[0] = (yyvsp[(1) - (3)].node);
            (yyval.node)->children[1] = (yyvsp[(3) - (3)].node);
        ;}
    break;

  case 41:
#line 313 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_IF, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (5)].node);  /* condição */
            (yyval.node)->children[1] = (yyvsp[(5) - (5)].node);  /* bloco then */
        ;}
    break;

  case 42:
#line 319 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_IF, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (7)].node);  /* condição */
            (yyval.node)->children[1] = (yyvsp[(5) - (7)].node);  /* bloco then */
            (yyval.node)->children[2] = (yyvsp[(7) - (7)].node);  /* bloco else */
        ;}
    break;

  case 43:
#line 330 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_WHILE, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (6)].node);  /* condição */
            (yyval.node)->children[1] = (yyvsp[(6) - (6)].node);  /* corpo */
        ;}
    break;

  case 44:
#line 341 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_FOR, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (9)].node);  /* init (assign) */
            (yyval.node)->children[1] = (yyvsp[(5) - (9)].node);  /* cond  (expr)   */
            (yyval.node)->children[2] = (yyvsp[(7) - (9)].node);  /* step (assign) */
            (yyval.node)->children[3] = (yyvsp[(9) - (9)].node);  /* corpo */
        ;}
    break;

  case 45:
#line 353 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_RETURN, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (2)].node);
        ;}
    break;

  case 46:
#line 362 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_PRINT, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (2)].node);
        ;}
    break;

  case 47:
#line 371 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_READ, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (2)].node);
        ;}
    break;

  case 48:
#line 380 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_CALL, (yyvsp[(1) - (4)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (4)].node);
            free((yyvsp[(1) - (4)].sval));
        ;}
    break;

  case 49:
#line 390 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "+",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 50:
#line 391 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "-",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 51:
#line 392 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "*",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 52:
#line 393 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "/",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 53:
#line 394 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "%",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 54:
#line 397 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "<",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 55:
#line 398 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, ">",  yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 56:
#line 399 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "<=", yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 57:
#line 400 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, ">=", yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 58:
#line 401 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "==", yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 59:
#line 402 "src/parser.y"
    { (yyval.node) = ast_new(AST_EXPR_BINARY, "!=", yylineno); (yyval.node)->children[0]=(yyvsp[(1) - (3)].node); (yyval.node)->children[1]=(yyvsp[(3) - (3)].node); ;}
    break;

  case 60:
#line 412 "src/parser.y"
    {
            /* TODO-C-1: substitua NULL pelo nó correto */
            (yyval.node) = NULL;  /* <-- INCOMPLETO: crie o nó AST_EXPR_BINARY aqui */
            /* Dica: $$ = ast_new(AST_EXPR_BINARY, "&&", yylineno);
             *        $$->children[0] = $1;
             *        $$->children[1] = $3;          */
        ;}
    break;

  case 61:
#line 420 "src/parser.y"
    {
            /* TODO-C-2: substitua NULL pelo nó correto */
            (yyval.node) = NULL;  /* <-- INCOMPLETO: crie o nó AST_EXPR_BINARY aqui */
        ;}
    break;

  case 62:
#line 427 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_UNARY, "!", yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (2)].node);
        ;}
    break;

  case 63:
#line 434 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_UNARY, "-", yylineno);
            (yyval.node)->children[0] = (yyvsp[(2) - (2)].node);
        ;}
    break;

  case 64:
#line 440 "src/parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 65:
#line 444 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_CALL, (yyvsp[(1) - (4)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (4)].node);
            free((yyvsp[(1) - (4)].sval));
        ;}
    break;

  case 66:
#line 452 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_INDEX, (yyvsp[(1) - (4)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (4)].node);
            free((yyvsp[(1) - (4)].sval));
        ;}
    break;

  case 67:
#line 460 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_ARROW, (yyvsp[(1) - (3)].sval), yylineno);
            (yyval.node)->children[0] = ast_new(AST_SYMBOL, (yyvsp[(3) - (3)].sval), yylineno);
            free((yyvsp[(1) - (3)].sval));
            free((yyvsp[(3) - (3)].sval));
        ;}
    break;

  case 68:
#line 469 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_SYMBOL, (yyvsp[(1) - (1)].sval), yylineno);
            free((yyvsp[(1) - (1)].sval));
        ;}
    break;

  case 69:
#line 475 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 70:
#line 480 "src/parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 71:
#line 481 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node);   ;}
    break;

  case 72:
#line 496 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 73:
#line 503 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_SYMBOL, (yyvsp[(1) - (1)].sval), yylineno);
            free((yyvsp[(1) - (1)].sval));
        ;}
    break;

  case 74:
#line 508 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_INDEX, (yyvsp[(1) - (4)].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[(3) - (4)].node);
            free((yyvsp[(1) - (4)].sval));
        ;}
    break;

  case 75:
#line 514 "src/parser.y"
    {
            (yyval.node) = ast_new(AST_EXPR_ARROW, (yyvsp[(1) - (3)].sval), yylineno);
            (yyval.node)->children[0] = ast_new(AST_SYMBOL, (yyvsp[(3) - (3)].sval), yylineno);
            free((yyvsp[(1) - (3)].sval));
            free((yyvsp[(3) - (3)].sval));
        ;}
    break;

  case 76:
#line 524 "src/parser.y"
    { (yyval.node) = ast_new(AST_LIT_INT,    (yyvsp[(1) - (1)].sval), yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 77:
#line 525 "src/parser.y"
    { (yyval.node) = ast_new(AST_LIT_FLOAT,  (yyvsp[(1) - (1)].sval), yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 78:
#line 526 "src/parser.y"
    { (yyval.node) = ast_new(AST_LIT_CHAR,   (yyvsp[(1) - (1)].sval), yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 79:
#line 527 "src/parser.y"
    { (yyval.node) = ast_new(AST_LIT_STRING,  (yyvsp[(1) - (1)].sval), yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 80:
#line 528 "src/parser.y"
    { (yyval.node) = ast_new(AST_LIT_BOOL,   "true",  yylineno); ;}
    break;

  case 81:
#line 529 "src/parser.y"
    { (yyval.node) = ast_new(AST_LIT_BOOL,   "false", yylineno); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2118 "src/parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 532 "src/parser.y"



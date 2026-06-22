/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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

/* Converte nome de tipo para sym_datatype_t */
static sym_datatype_t str_to_datatype(const char *tname)
{
    if (!tname)             return SYM_TYPE_UNKNOWN;
    if (strcmp(tname, "int")   == 0) return SYM_TYPE_INT;
    if (strcmp(tname, "float") == 0) return SYM_TYPE_FLOAT;
    if (strcmp(tname, "char")  == 0) return SYM_TYPE_CHAR;
    if (strcmp(tname, "bool")  == 0) return SYM_TYPE_BOOL;
    if (strcmp(tname, "void")  == 0) return SYM_TYPE_VOID;
    return SYM_TYPE_UNKNOWN;
}

#line 112 "src/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_PR_INT = 3,                  /* TK_PR_INT  */
  YYSYMBOL_TK_PR_FLOAT = 4,                /* TK_PR_FLOAT  */
  YYSYMBOL_TK_PR_BOOL = 5,                 /* TK_PR_BOOL  */
  YYSYMBOL_TK_PR_CHAR = 6,                 /* TK_PR_CHAR  */
  YYSYMBOL_TK_PR_IF = 7,                   /* TK_PR_IF  */
  YYSYMBOL_TK_PR_ELSE = 8,                 /* TK_PR_ELSE  */
  YYSYMBOL_TK_PR_WHILE = 9,                /* TK_PR_WHILE  */
  YYSYMBOL_TK_PR_FOR = 10,                 /* TK_PR_FOR  */
  YYSYMBOL_TK_PR_RETURN = 11,              /* TK_PR_RETURN  */
  YYSYMBOL_TK_PR_VOID = 12,                /* TK_PR_VOID  */
  YYSYMBOL_TK_PR_ARRAY = 13,               /* TK_PR_ARRAY  */
  YYSYMBOL_TK_PR_OF = 14,                  /* TK_PR_OF  */
  YYSYMBOL_TK_PR_LET = 15,                 /* TK_PR_LET  */
  YYSYMBOL_TK_PR_FUN = 16,                 /* TK_PR_FUN  */
  YYSYMBOL_TK_PR_DO = 17,                  /* TK_PR_DO  */
  YYSYMBOL_TK_PR_PRINT = 18,               /* TK_PR_PRINT  */
  YYSYMBOL_TK_PR_READ = 19,                /* TK_PR_READ  */
  YYSYMBOL_TK_LIT_TRUE = 20,               /* TK_LIT_TRUE  */
  YYSYMBOL_TK_LIT_FALSE = 21,              /* TK_LIT_FALSE  */
  YYSYMBOL_TK_OC_LE = 22,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 23,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 24,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 25,                  /* TK_OC_NE  */
  YYSYMBOL_TK_OC_AND = 26,                 /* TK_OC_AND  */
  YYSYMBOL_TK_OC_OR = 27,                  /* TK_OC_OR  */
  YYSYMBOL_TK_OC_ARROW = 28,               /* TK_OC_ARROW  */
  YYSYMBOL_TK_OC_ASSIGN = 29,              /* TK_OC_ASSIGN  */
  YYSYMBOL_TK_OC_PLUSEQ = 30,              /* TK_OC_PLUSEQ  */
  YYSYMBOL_TK_OC_MINUSEQ = 31,             /* TK_OC_MINUSEQ  */
  YYSYMBOL_TK_ERROR = 32,                  /* TK_ERROR  */
  YYSYMBOL_TK_ID = 33,                     /* TK_ID  */
  YYSYMBOL_TK_LIT_INT = 34,                /* TK_LIT_INT  */
  YYSYMBOL_TK_LIT_FLOAT = 35,              /* TK_LIT_FLOAT  */
  YYSYMBOL_TK_LIT_CHAR = 36,               /* TK_LIT_CHAR  */
  YYSYMBOL_TK_LIT_STRING = 37,             /* TK_LIT_STRING  */
  YYSYMBOL_38_ = 38,                       /* '<'  */
  YYSYMBOL_39_ = 39,                       /* '>'  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_44_ = 44,                       /* '%'  */
  YYSYMBOL_45_ = 45,                       /* '!'  */
  YYSYMBOL_UMINUS = 46,                    /* UMINUS  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ')'  */
  YYSYMBOL_50_ = 50,                       /* ','  */
  YYSYMBOL_51_ = 51,                       /* ';'  */
  YYSYMBOL_52_ = 52,                       /* '{'  */
  YYSYMBOL_53_ = 53,                       /* '}'  */
  YYSYMBOL_54_ = 54,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_toplevel_list = 57,             /* toplevel_list  */
  YYSYMBOL_toplevel_decl = 58,             /* toplevel_decl  */
  YYSYMBOL_fun_decl = 59,                  /* fun_decl  */
  YYSYMBOL_param_list = 60,                /* param_list  */
  YYSYMBOL_param_list_ne = 61,             /* param_list_ne  */
  YYSYMBOL_param = 62,                     /* param  */
  YYSYMBOL_var_decl = 63,                  /* var_decl  */
  YYSYMBOL_array_decl = 64,                /* array_decl  */
  YYSYMBOL_type_spec = 65,                 /* type_spec  */
  YYSYMBOL_block = 66,                     /* block  */
  YYSYMBOL_stmt_list = 67,                 /* stmt_list  */
  YYSYMBOL_stmt = 68,                      /* stmt  */
  YYSYMBOL_simple_stmt = 69,               /* simple_stmt  */
  YYSYMBOL_compound_stmt = 70,             /* compound_stmt  */
  YYSYMBOL_var_local = 71,                 /* var_local  */
  YYSYMBOL_assign_stmt = 72,               /* assign_stmt  */
  YYSYMBOL_if_stmt = 73,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 74,                /* while_stmt  */
  YYSYMBOL_for_stmt = 75,                  /* for_stmt  */
  YYSYMBOL_return_stmt = 76,               /* return_stmt  */
  YYSYMBOL_print_stmt = 77,                /* print_stmt  */
  YYSYMBOL_read_stmt = 78,                 /* read_stmt  */
  YYSYMBOL_call_stmt = 79,                 /* call_stmt  */
  YYSYMBOL_expr = 80,                      /* expr  */
  YYSYMBOL_expr_list = 81,                 /* expr_list  */
  YYSYMBOL_expr_list_ne = 82,              /* expr_list_ne  */
  YYSYMBOL_lvalue = 83,                    /* lvalue  */
  YYSYMBOL_literal = 84                    /* literal  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   155,   163,   165,   170,   171,   172,   178,
     190,   191,   195,   196,   201,   212,   228,   246,   247,   248,
     249,   250,   255,   260,   269,   271,   277,   278,   283,   284,
     285,   286,   287,   288,   293,   294,   295,   300,   311,   317,
     323,   333,   339,   350,   361,   373,   382,   391,   400,   411,
     412,   413,   414,   415,   418,   419,   420,   421,   422,   423,
     432,   438,   446,   453,   460,   463,   471,   479,   488,   495,
     500,   501,   515,   517,   523,   528,   534,   545,   546,   547,
     548,   549,   550
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_PR_INT",
  "TK_PR_FLOAT", "TK_PR_BOOL", "TK_PR_CHAR", "TK_PR_IF", "TK_PR_ELSE",
  "TK_PR_WHILE", "TK_PR_FOR", "TK_PR_RETURN", "TK_PR_VOID", "TK_PR_ARRAY",
  "TK_PR_OF", "TK_PR_LET", "TK_PR_FUN", "TK_PR_DO", "TK_PR_PRINT",
  "TK_PR_READ", "TK_LIT_TRUE", "TK_LIT_FALSE", "TK_OC_LE", "TK_OC_GE",
  "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR", "TK_OC_ARROW",
  "TK_OC_ASSIGN", "TK_OC_PLUSEQ", "TK_OC_MINUSEQ", "TK_ERROR", "TK_ID",
  "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_CHAR", "TK_LIT_STRING", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "UMINUS", "'['", "'('",
  "')'", "','", "';'", "'{'", "'}'", "']'", "$accept", "program",
  "toplevel_list", "toplevel_decl", "fun_decl", "param_list",
  "param_list_ne", "param", "var_decl", "array_decl", "type_spec", "block",
  "stmt_list", "stmt", "simple_stmt", "compound_stmt", "var_local",
  "assign_stmt", "if_stmt", "while_stmt", "for_stmt", "return_stmt",
  "print_stmt", "read_stmt", "call_stmt", "expr", "expr_list",
  "expr_list_ne", "lvalue", "literal", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     317,  -112,  -112,  -112,  -112,  -112,   -22,   160,    10,   317,
    -112,  -112,  -112,  -112,   -20,     3,   -14,  -112,  -112,   -26,
     160,   -21,  -112,    -5,   160,    -9,    -8,   -11,  -112,    11,
    -112,    -2,   160,  -112,    -4,  -112,  -112,     0,     8,    32,
     134,    18,   134,    39,   -24,  -112,    64,  -112,    38,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,    24,
     134,   134,    39,  -112,  -112,   -12,  -112,  -112,  -112,  -112,
     134,   134,   134,   245,  -112,    70,   245,   -10,  -112,    65,
     134,   134,  -112,  -112,  -112,   134,   134,   134,   161,   189,
      49,    68,   134,   134,  -112,  -112,   217,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,  -112,    69,   245,    54,    55,   245,   245,   245,    -2,
      87,   134,  -112,   102,    57,  -112,    44,    44,   151,   151,
     275,   252,    44,    44,    34,    34,  -112,  -112,  -112,   245,
    -112,  -112,   134,   106,    -2,   109,  -112,  -112,   245,    -2,
    -112,    39,  -112,    66,    -2,  -112
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    17,    18,    19,    20,    21,     0,     0,     0,     2,
       4,     6,     7,     8,     0,     0,     0,     1,     5,     0,
       0,     0,    15,     0,    10,     0,     0,    11,    12,     0,
      16,     0,     0,    14,     0,     9,    13,     0,     0,     0,
       0,     0,     0,     0,    74,    23,     0,    24,     0,    27,
      33,    28,    34,    35,    36,    29,    30,    31,    32,     0,
       0,     0,     0,    81,    82,    68,    77,    78,    79,    80,
       0,     0,     0,    45,    69,     0,    46,    74,    47,     0,
       0,    70,    22,    25,    26,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    63,    62,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,    72,     0,    71,    38,    39,    40,     0,
       0,     0,    67,     0,     0,    64,    56,    57,    58,    59,
      60,    61,    54,    55,    49,    50,    51,    52,    53,    37,
      75,    48,     0,    41,     0,     0,    66,    65,    73,     0,
      43,     0,    42,     0,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -112,  -112,  -112,   107,  -112,  -112,  -112,    86,  -112,  -112,
       2,  -111,  -112,    73,  -112,  -112,  -112,   -61,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,   -40,    27,  -112,    78,  -112
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    26,    27,    28,    12,    13,
      14,    35,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,   113,   114,   115,    59,    74
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,    90,    76,    37,    79,    38,    39,    40,   143,    16,
      17,    41,    15,    19,    42,    43,    91,    20,    79,    21,
      88,    89,    23,    80,    81,    22,    29,    24,    25,    44,
      94,    95,    96,   150,    29,    92,    93,    80,   152,    32,
     112,    31,    30,   155,    33,   116,   117,   118,    60,    45,
      34,    75,   123,    85,    86,    87,    61,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,    37,    77,    38,    39,    40,   107,   108,   109,    41,
      62,   145,    42,    43,   105,   106,   107,   108,   109,    84,
     153,    97,    98,    99,   100,   101,   102,    44,   111,   110,
     121,   122,   148,   141,   144,   142,   147,   103,   104,   105,
     106,   107,   108,   109,   149,   154,    18,    82,    36,    83,
     124,    78,     0,   140,    97,    98,    99,   100,   101,   102,
       0,    97,    98,    99,   100,   101,   102,     0,     0,     0,
     103,   104,   105,   106,   107,   108,   109,   103,   104,   105,
     106,   107,   108,   109,    63,    64,   146,     0,     0,     0,
     151,     0,     0,     1,     2,     3,     4,    65,    66,    67,
      68,    69,     5,    97,    98,    70,     0,     0,     0,    71,
       0,     0,    72,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,     0,     0,     0,   103,
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
      40,    62,    42,     7,    28,     9,    10,    11,   119,     7,
       0,    15,    34,    33,    18,    19,    28,    14,    28,    33,
      60,    61,    20,    47,    48,    51,    24,    48,    33,    33,
      70,    71,    72,   144,    32,    47,    48,    47,   149,    50,
      80,    49,    51,   154,    33,    85,    86,    87,    48,    53,
      52,    33,    92,    29,    30,    31,    48,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     7,    33,     9,    10,    11,    42,    43,    44,    15,
      48,   121,    18,    19,    40,    41,    42,    43,    44,    51,
     151,    22,    23,    24,    25,    26,    27,    33,    33,    29,
      51,    33,   142,    49,    17,    50,    49,    38,    39,    40,
      41,    42,    43,    44,     8,    49,     9,    53,    32,    46,
      93,    43,    -1,    54,    22,    23,    24,    25,    26,    27,
      -1,    22,    23,    24,    25,    26,    27,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    38,    39,    40,
      41,    42,    43,    44,    20,    21,    54,    -1,    -1,    -1,
      51,    -1,    -1,     3,     4,     5,     6,    33,    34,    35,
      36,    37,    12,    22,    23,    41,    -1,    -1,    -1,    45,
      -1,    -1,    48,    22,    23,    24,    25,    26,    27,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    38,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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
      54,    49,    50,    66,    17,    80,    54,    49,    80,     8,
      66,    51,    66,    72,    49,    66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    56,    57,    57,    58,    58,    58,    59,
      60,    60,    61,    61,    62,    63,    64,    65,    65,    65,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    71,    72,    72,
      72,    73,    73,    74,    75,    76,    77,    78,    79,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    82,    83,    83,    83,    84,    84,    84,
      84,    84,    84
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     7,
       0,     1,     1,     3,     2,     3,     6,     1,     1,     1,
       1,     1,     3,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       3,     5,     7,     6,     9,     2,     2,     2,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     4,     4,     3,     1,     1,
       0,     1,     1,     3,     1,     4,     3,     1,     1,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: toplevel_list  */
#line 149 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_PROGRAM, NULL, 1);
            (yyval.node)->children[0] = (yyvsp[0].node);
            ast_root = (yyval.node);
        }
#line 1330 "src/parser.tab.c"
    break;

  case 3: /* program: %empty  */
#line 155 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_PROGRAM, NULL, 1);
            ast_root = (yyval.node);
        }
#line 1339 "src/parser.tab.c"
    break;

  case 4: /* toplevel_list: toplevel_decl  */
#line 164 "src/parser.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1345 "src/parser.tab.c"
    break;

  case 5: /* toplevel_list: toplevel_list toplevel_decl  */
#line 166 "src/parser.y"
        { (yyval.node) = ast_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1351 "src/parser.tab.c"
    break;

  case 6: /* toplevel_decl: fun_decl  */
#line 170 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1357 "src/parser.tab.c"
    break;

  case 7: /* toplevel_decl: var_decl  */
#line 171 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1363 "src/parser.tab.c"
    break;

  case 8: /* toplevel_decl: array_decl  */
#line 172 "src/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1369 "src/parser.tab.c"
    break;

  case 9: /* fun_decl: TK_PR_FUN type_spec TK_ID '(' param_list ')' block  */
#line 179 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_FUN_DECL, (yyvsp[-4].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-5].node);   /* tipo de retorno */
            (yyval.node)->children[1] = (yyvsp[-2].node);   /* lista de parâmetros (pode ser NULL) */
            (yyval.node)->children[2] = (yyvsp[0].node);   /* corpo (bloco) */
            free((yyvsp[-4].sval));
        }
#line 1381 "src/parser.tab.c"
    break;

  case 10: /* param_list: %empty  */
#line 190 "src/parser.y"
                        { (yyval.node) = NULL; }
#line 1387 "src/parser.tab.c"
    break;

  case 11: /* param_list: param_list_ne  */
#line 191 "src/parser.y"
                        { (yyval.node) = (yyvsp[0].node);   }
#line 1393 "src/parser.tab.c"
    break;

  case 12: /* param_list_ne: param  */
#line 195 "src/parser.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1399 "src/parser.tab.c"
    break;

  case 13: /* param_list_ne: param_list_ne ',' param  */
#line 196 "src/parser.y"
                                    { (yyval.node) = ast_append((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1405 "src/parser.tab.c"
    break;

  case 14: /* param: type_spec TK_ID  */
#line 202 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_PARAM, (yyvsp[0].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-1].node);
            free((yyvsp[0].sval));
        }
#line 1415 "src/parser.tab.c"
    break;

  case 15: /* var_decl: type_spec TK_ID ';'  */
#line 213 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_VAR_DECL, (yyvsp[-1].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);
            sym_entry_t *_e = symtab_lookup(global_symtab, (yyvsp[-1].sval));
            if (_e) {
                _e->nature   = SYM_VAR;
                _e->datatype = str_to_datatype((yyvsp[-2].node)->value);
            }
            free((yyvsp[-1].sval));
        }
#line 1430 "src/parser.tab.c"
    break;

  case 16: /* array_decl: TK_PR_ARRAY TK_LIT_INT TK_PR_OF type_spec TK_ID ';'  */
#line 229 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_ARRAY_DECL, (yyvsp[-1].sval), yylineno);
            (yyval.node)->children[0] = ast_new(AST_LIT_INT, (yyvsp[-4].sval), yylineno);  /* tamanho */
            (yyval.node)->children[1] = (yyvsp[-2].node);                                    /* tipo base */
            sym_entry_t *_ea = symtab_lookup(global_symtab, (yyvsp[-1].sval));
            if (_ea) {
                _ea->nature     = SYM_ARRAY;
                _ea->datatype   = str_to_datatype((yyvsp[-2].node)->value);
                _ea->array_size = atoi((yyvsp[-4].sval));
            }
            free((yyvsp[-4].sval));
            free((yyvsp[-1].sval));
        }
#line 1448 "src/parser.tab.c"
    break;

  case 17: /* type_spec: TK_PR_INT  */
#line 246 "src/parser.y"
                   { (yyval.node) = ast_new(AST_SYMBOL, "int",   yylineno); }
#line 1454 "src/parser.tab.c"
    break;

  case 18: /* type_spec: TK_PR_FLOAT  */
#line 247 "src/parser.y"
                   { (yyval.node) = ast_new(AST_SYMBOL, "float", yylineno); }
#line 1460 "src/parser.tab.c"
    break;

  case 19: /* type_spec: TK_PR_BOOL  */
#line 248 "src/parser.y"
                   { (yyval.node) = ast_new(AST_SYMBOL, "bool",  yylineno); }
#line 1466 "src/parser.tab.c"
    break;

  case 20: /* type_spec: TK_PR_CHAR  */
#line 249 "src/parser.y"
                   { (yyval.node) = ast_new(AST_SYMBOL, "char",  yylineno); }
#line 1472 "src/parser.tab.c"
    break;

  case 21: /* type_spec: TK_PR_VOID  */
#line 250 "src/parser.y"
                   { (yyval.node) = ast_new(AST_SYMBOL, "void",  yylineno); }
#line 1478 "src/parser.tab.c"
    break;

  case 22: /* block: '{' stmt_list '}'  */
#line 256 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_BLOCK, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[-1].node);
        }
#line 1487 "src/parser.tab.c"
    break;

  case 23: /* block: '{' '}'  */
#line 261 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_BLOCK, NULL, yylineno);
        }
#line 1495 "src/parser.tab.c"
    break;

  case 24: /* stmt_list: stmt  */
#line 270 "src/parser.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1501 "src/parser.tab.c"
    break;

  case 25: /* stmt_list: stmt_list stmt  */
#line 272 "src/parser.y"
        { (yyval.node) = ast_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1507 "src/parser.tab.c"
    break;

  case 26: /* stmt: simple_stmt ';'  */
#line 277 "src/parser.y"
                      { (yyval.node) = (yyvsp[-1].node); }
#line 1513 "src/parser.tab.c"
    break;

  case 27: /* stmt: compound_stmt  */
#line 278 "src/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1519 "src/parser.tab.c"
    break;

  case 28: /* simple_stmt: assign_stmt  */
#line 283 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1525 "src/parser.tab.c"
    break;

  case 29: /* simple_stmt: return_stmt  */
#line 284 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1531 "src/parser.tab.c"
    break;

  case 30: /* simple_stmt: print_stmt  */
#line 285 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1537 "src/parser.tab.c"
    break;

  case 31: /* simple_stmt: read_stmt  */
#line 286 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1543 "src/parser.tab.c"
    break;

  case 32: /* simple_stmt: call_stmt  */
#line 287 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1549 "src/parser.tab.c"
    break;

  case 33: /* simple_stmt: var_local  */
#line 288 "src/parser.y"
                   { (yyval.node) = (yyvsp[0].node);   }
#line 1555 "src/parser.tab.c"
    break;

  case 34: /* compound_stmt: if_stmt  */
#line 293 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1561 "src/parser.tab.c"
    break;

  case 35: /* compound_stmt: while_stmt  */
#line 294 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1567 "src/parser.tab.c"
    break;

  case 36: /* compound_stmt: for_stmt  */
#line 295 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1573 "src/parser.tab.c"
    break;

  case 37: /* var_local: TK_PR_LET TK_ID TK_OC_ASSIGN expr  */
#line 301 "src/parser.y"
        {
            symtab_insert(global_symtab, (yyvsp[-2].sval), yylineno);
            (yyval.node) = ast_new(AST_VAR_DECL, (yyvsp[-2].sval), yylineno);
            (yyval.node)->children[1] = (yyvsp[0].node);
            free((yyvsp[-2].sval));
        }
#line 1584 "src/parser.tab.c"
    break;

  case 38: /* assign_stmt: lvalue TK_OC_ASSIGN expr  */
#line 312 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_ASSIGN, ":=", yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);
            (yyval.node)->children[1] = (yyvsp[0].node);
        }
#line 1594 "src/parser.tab.c"
    break;

  case 39: /* assign_stmt: lvalue TK_OC_PLUSEQ expr  */
#line 318 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_ASSIGN, "+=", yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);
            (yyval.node)->children[1] = (yyvsp[0].node);
        }
#line 1604 "src/parser.tab.c"
    break;

  case 40: /* assign_stmt: lvalue TK_OC_MINUSEQ expr  */
#line 324 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_ASSIGN, "-=", yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);
            (yyval.node)->children[1] = (yyvsp[0].node);
        }
#line 1614 "src/parser.tab.c"
    break;

  case 41: /* if_stmt: TK_PR_IF '(' expr ')' block  */
#line 334 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_IF, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);  /* condição */
            (yyval.node)->children[1] = (yyvsp[0].node);  /* bloco then */
        }
#line 1624 "src/parser.tab.c"
    break;

  case 42: /* if_stmt: TK_PR_IF '(' expr ')' block TK_PR_ELSE block  */
#line 340 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_IF, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[-4].node);  /* condição */
            (yyval.node)->children[1] = (yyvsp[-2].node);  /* bloco then */
            (yyval.node)->children[2] = (yyvsp[0].node);  /* bloco else */
        }
#line 1635 "src/parser.tab.c"
    break;

  case 43: /* while_stmt: TK_PR_WHILE '(' expr ')' TK_PR_DO block  */
#line 351 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_WHILE, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[-3].node);  /* condição */
            (yyval.node)->children[1] = (yyvsp[0].node);  /* corpo */
        }
#line 1645 "src/parser.tab.c"
    break;

  case 44: /* for_stmt: TK_PR_FOR '(' assign_stmt ';' expr ';' assign_stmt ')' block  */
#line 362 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_FOR, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[-6].node);  /* init (assign) */
            (yyval.node)->children[1] = (yyvsp[-4].node);  /* cond  (expr)   */
            (yyval.node)->children[2] = (yyvsp[-2].node);  /* step (assign) */
            (yyval.node)->children[3] = (yyvsp[0].node);  /* corpo */
        }
#line 1657 "src/parser.tab.c"
    break;

  case 45: /* return_stmt: TK_PR_RETURN expr  */
#line 374 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_RETURN, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[0].node);
        }
#line 1666 "src/parser.tab.c"
    break;

  case 46: /* print_stmt: TK_PR_PRINT expr  */
#line 383 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_PRINT, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[0].node);
        }
#line 1675 "src/parser.tab.c"
    break;

  case 47: /* read_stmt: TK_PR_READ lvalue  */
#line 392 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_READ, NULL, yylineno);
            (yyval.node)->children[0] = (yyvsp[0].node);
        }
#line 1684 "src/parser.tab.c"
    break;

  case 48: /* call_stmt: TK_ID '(' expr_list ')'  */
#line 401 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_CALL, (yyvsp[-3].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-1].node);
            free((yyvsp[-3].sval));
        }
#line 1694 "src/parser.tab.c"
    break;

  case 49: /* expr: expr '+' expr  */
#line 411 "src/parser.y"
                     { (yyval.node) = ast_new(AST_EXPR_BINARY, "+",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1700 "src/parser.tab.c"
    break;

  case 50: /* expr: expr '-' expr  */
#line 412 "src/parser.y"
                     { (yyval.node) = ast_new(AST_EXPR_BINARY, "-",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1706 "src/parser.tab.c"
    break;

  case 51: /* expr: expr '*' expr  */
#line 413 "src/parser.y"
                     { (yyval.node) = ast_new(AST_EXPR_BINARY, "*",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1712 "src/parser.tab.c"
    break;

  case 52: /* expr: expr '/' expr  */
#line 414 "src/parser.y"
                     { (yyval.node) = ast_new(AST_EXPR_BINARY, "/",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1718 "src/parser.tab.c"
    break;

  case 53: /* expr: expr '%' expr  */
#line 415 "src/parser.y"
                     { (yyval.node) = ast_new(AST_EXPR_BINARY, "%",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1724 "src/parser.tab.c"
    break;

  case 54: /* expr: expr '<' expr  */
#line 418 "src/parser.y"
                            { (yyval.node) = ast_new(AST_EXPR_BINARY, "<",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1730 "src/parser.tab.c"
    break;

  case 55: /* expr: expr '>' expr  */
#line 419 "src/parser.y"
                            { (yyval.node) = ast_new(AST_EXPR_BINARY, ">",  yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1736 "src/parser.tab.c"
    break;

  case 56: /* expr: expr TK_OC_LE expr  */
#line 420 "src/parser.y"
                            { (yyval.node) = ast_new(AST_EXPR_BINARY, "<=", yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1742 "src/parser.tab.c"
    break;

  case 57: /* expr: expr TK_OC_GE expr  */
#line 421 "src/parser.y"
                            { (yyval.node) = ast_new(AST_EXPR_BINARY, ">=", yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1748 "src/parser.tab.c"
    break;

  case 58: /* expr: expr TK_OC_EQ expr  */
#line 422 "src/parser.y"
                            { (yyval.node) = ast_new(AST_EXPR_BINARY, "==", yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1754 "src/parser.tab.c"
    break;

  case 59: /* expr: expr TK_OC_NE expr  */
#line 423 "src/parser.y"
                            { (yyval.node) = ast_new(AST_EXPR_BINARY, "!=", yylineno); (yyval.node)->children[0]=(yyvsp[-2].node); (yyval.node)->children[1]=(yyvsp[0].node); }
#line 1760 "src/parser.tab.c"
    break;

  case 60: /* expr: expr TK_OC_AND expr  */
#line 433 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_BINARY, "&&", yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);
            (yyval.node)->children[1] = (yyvsp[0].node);
        }
#line 1770 "src/parser.tab.c"
    break;

  case 61: /* expr: expr TK_OC_OR expr  */
#line 439 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_BINARY, "||", yylineno);
            (yyval.node)->children[0] = (yyvsp[-2].node);
            (yyval.node)->children[1] = (yyvsp[0].node);
        }
#line 1780 "src/parser.tab.c"
    break;

  case 62: /* expr: '!' expr  */
#line 447 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_UNARY, "!", yylineno);
            (yyval.node)->children[0] = (yyvsp[0].node);
        }
#line 1789 "src/parser.tab.c"
    break;

  case 63: /* expr: '-' expr  */
#line 454 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_UNARY, "-", yylineno);
            (yyval.node)->children[0] = (yyvsp[0].node);
        }
#line 1798 "src/parser.tab.c"
    break;

  case 64: /* expr: '(' expr ')'  */
#line 460 "src/parser.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 1804 "src/parser.tab.c"
    break;

  case 65: /* expr: TK_ID '(' expr_list ')'  */
#line 464 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_CALL, (yyvsp[-3].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-1].node);
            free((yyvsp[-3].sval));
        }
#line 1814 "src/parser.tab.c"
    break;

  case 66: /* expr: TK_ID '[' expr ']'  */
#line 472 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_INDEX, (yyvsp[-3].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-1].node);
            free((yyvsp[-3].sval));
        }
#line 1824 "src/parser.tab.c"
    break;

  case 67: /* expr: TK_ID TK_OC_ARROW TK_ID  */
#line 480 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_ARROW, (yyvsp[-2].sval), yylineno);
            (yyval.node)->children[0] = ast_new(AST_SYMBOL, (yyvsp[0].sval), yylineno);
            free((yyvsp[-2].sval));
            free((yyvsp[0].sval));
        }
#line 1835 "src/parser.tab.c"
    break;

  case 68: /* expr: TK_ID  */
#line 489 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_SYMBOL, (yyvsp[0].sval), yylineno);
            free((yyvsp[0].sval));
        }
#line 1844 "src/parser.tab.c"
    break;

  case 69: /* expr: literal  */
#line 495 "src/parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1850 "src/parser.tab.c"
    break;

  case 70: /* expr_list: %empty  */
#line 500 "src/parser.y"
                     { (yyval.node) = NULL; }
#line 1856 "src/parser.tab.c"
    break;

  case 71: /* expr_list: expr_list_ne  */
#line 501 "src/parser.y"
                     { (yyval.node) = (yyvsp[0].node);   }
#line 1862 "src/parser.tab.c"
    break;

  case 72: /* expr_list_ne: expr  */
#line 516 "src/parser.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1868 "src/parser.tab.c"
    break;

  case 73: /* expr_list_ne: expr_list_ne ',' expr  */
#line 518 "src/parser.y"
        { (yyval.node) = ast_append((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1874 "src/parser.tab.c"
    break;

  case 74: /* lvalue: TK_ID  */
#line 524 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_SYMBOL, (yyvsp[0].sval), yylineno);
            free((yyvsp[0].sval));
        }
#line 1883 "src/parser.tab.c"
    break;

  case 75: /* lvalue: TK_ID '[' expr ']'  */
#line 529 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_INDEX, (yyvsp[-3].sval), yylineno);
            (yyval.node)->children[0] = (yyvsp[-1].node);
            free((yyvsp[-3].sval));
        }
#line 1893 "src/parser.tab.c"
    break;

  case 76: /* lvalue: TK_ID TK_OC_ARROW TK_ID  */
#line 535 "src/parser.y"
        {
            (yyval.node) = ast_new(AST_EXPR_ARROW, (yyvsp[-2].sval), yylineno);
            (yyval.node)->children[0] = ast_new(AST_SYMBOL, (yyvsp[0].sval), yylineno);
            free((yyvsp[-2].sval));
            free((yyvsp[0].sval));
        }
#line 1904 "src/parser.tab.c"
    break;

  case 77: /* literal: TK_LIT_INT  */
#line 545 "src/parser.y"
                    { (yyval.node) = ast_new(AST_LIT_INT,    (yyvsp[0].sval), yylineno); free((yyvsp[0].sval)); }
#line 1910 "src/parser.tab.c"
    break;

  case 78: /* literal: TK_LIT_FLOAT  */
#line 546 "src/parser.y"
                    { (yyval.node) = ast_new(AST_LIT_FLOAT,  (yyvsp[0].sval), yylineno); free((yyvsp[0].sval)); }
#line 1916 "src/parser.tab.c"
    break;

  case 79: /* literal: TK_LIT_CHAR  */
#line 547 "src/parser.y"
                    { (yyval.node) = ast_new(AST_LIT_CHAR,   (yyvsp[0].sval), yylineno); free((yyvsp[0].sval)); }
#line 1922 "src/parser.tab.c"
    break;

  case 80: /* literal: TK_LIT_STRING  */
#line 548 "src/parser.y"
                    { (yyval.node) = ast_new(AST_LIT_STRING,  (yyvsp[0].sval), yylineno); free((yyvsp[0].sval)); }
#line 1928 "src/parser.tab.c"
    break;

  case 81: /* literal: TK_LIT_TRUE  */
#line 549 "src/parser.y"
                    { (yyval.node) = ast_new(AST_LIT_BOOL,   "true",  yylineno); }
#line 1934 "src/parser.tab.c"
    break;

  case 82: /* literal: TK_LIT_FALSE  */
#line 550 "src/parser.y"
                    { (yyval.node) = ast_new(AST_LIT_BOOL,   "false", yylineno); }
#line 1940 "src/parser.tab.c"
    break;


#line 1944 "src/parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 553 "src/parser.y"


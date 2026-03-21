/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 70 "src/parser.y"
{
    char        *sval;   /* string (lexemas de ID, LIT_INT, LIT_FLOAT, etc.) */
    ast_node_t  *node;   /* nó da AST */
    int          ival;   /* inteiro (usado para armazenar yylineno) */
}
/* Line 1529 of yacc.c.  */
#line 131 "src/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


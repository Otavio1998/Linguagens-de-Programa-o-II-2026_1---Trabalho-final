/*
 * scanner.l — Analisador Léxico da Linguagem LARA
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * =====================================================================
 * TAREFA DOS ALUNOS:
 *
 * (A) TODO-A [espaço em branco]:
 *     A regra  [ \n]+  abaixo ignora apenas espaço e newline.
 *     Edite a expressão regular para também ignorar '\t' e '\r'.
 *     Dica: use uma classe de caracteres [ \n\t\r].
 *
 * (B) TODO-B [número float com expoente]:
 *     A definição FLOAT só aceita ponto decimal, não aceita expoente.
 *     Estenda-a para também aceitar notação científica: 1.5e10, 2.3E-4.
 *     Formato do expoente: (e|E)(+|-)?{DIGIT}+  — deve ser OPCIONAL.
 * =====================================================================
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"        /* ast_node_t — necessário antes de parser.tab.h */
#include "parser.tab.h" /* tokens (gerados pelo bison) e YYSTYPE */
#include "symtab.h"

extern symtab_t *global_symtab;

#define LEX_ERROR(msg) \
    fprintf(stderr, "[ERRO LÉXICO] linha %d: %s: '%s'\n", yylineno, msg, yytext)
%}

%option noyywrap
%option yylineno

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ALNUM       [a-zA-Z0-9_]
ID          {LETTER}{ALNUM}*
INT         {DIGIT}+

/*
 * TODO-B: altere a definição de FLOAT abaixo para aceitar expoente opcional.
 * Versão atual: aceita  d*.d+  ou  d+.d*  (sem expoente).
 * Expoente a adicionar: (e|E)(+|-)?{DIGIT}+
 */
FLOAT       {DIGIT}*"."{DIGIT}+([eE][+-]?{DIGIT}+)?|{DIGIT}+"."{DIGIT}*([eE][+-]?{DIGIT}+)?

%%

[ \n\t\r]+ { /* espaço em branco ignorado */ }

"//".*      { }

"/*"        {
    int c, prev = 0;
    while ((c = input()) != EOF) {
        if (prev == '*' && c == '/') break;
        if (c == '\n') yylineno++;
        prev = c;
    }
    if (c == EOF)
        LEX_ERROR("comentário de bloco não fechado");
}

"int"       { return TK_PR_INT;    }
"float"     { return TK_PR_FLOAT;  }
"bool"      { return TK_PR_BOOL;   }
"char"      { return TK_PR_CHAR;   }
"if"        { return TK_PR_IF;     }
"else"      { return TK_PR_ELSE;   }
"while"     { return TK_PR_WHILE;  }
"for"       { return TK_PR_FOR;    }
"return"    { return TK_PR_RETURN; }
"void"      { return TK_PR_VOID;   }
"array"     { return TK_PR_ARRAY;  }
"of"        { return TK_PR_OF;     }
"let"       { return TK_PR_LET;    }
"fun"       { return TK_PR_FUN;    }
"do"        { return TK_PR_DO;     }
"print"     { return TK_PR_PRINT;  }
"read"      { return TK_PR_READ;   }
"true"      { return TK_LIT_TRUE;  }
"false"     { return TK_LIT_FALSE; }

{INT}       { yylval.sval = strdup(yytext); return TK_LIT_INT;    }
{FLOAT}     { yylval.sval = strdup(yytext); return TK_LIT_FLOAT;  }
'[^'\n]'    { yylval.sval = strdup(yytext); return TK_LIT_CHAR;   }
\"[^"\n]*\" { yylval.sval = strdup(yytext); return TK_LIT_STRING; }

{ID}        {
    symtab_insert(global_symtab, yytext, yylineno);
    yylval.sval = strdup(yytext);
    return TK_ID;
}

"<="    { return TK_OC_LE;     }
">="    { return TK_OC_GE;     }
"=="    { return TK_OC_EQ;     }
"!="    { return TK_OC_NE;     }
"&&"    { return TK_OC_AND;    }
"||"    { return TK_OC_OR;     }
"->"    { return TK_OC_ARROW;  }
":="    { return TK_OC_ASSIGN; }
"+="    { return TK_OC_PLUSEQ; }
"-="    { return TK_OC_MINUSEQ;}

[+\-*/%<>!=()\[\]{},;:.]   { return yytext[0]; }

.           {
    LEX_ERROR("caractere inválido");
    return TK_ERROR;
}

%%

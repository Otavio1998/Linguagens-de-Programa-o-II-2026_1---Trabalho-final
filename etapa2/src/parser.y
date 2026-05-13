/*
 * parser.y — Gramática da Linguagem LARA para o bison
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este arquivo define a gramática completa da linguagem LARA. Ele está
 * quase completo; algumas regras de produção estão INTENCIONALMENTE
 * incompletas e marcadas com TODO.
 *
 * =====================================================================
 * TAREFA DOS ALUNOS:
 *
 * (C) Regras de EXPRESSÃO BOOLEANA [TODO-C]:
 *     As regras para os operadores lógicos '&&' e '||' estão presentes
 *     mas as ações semânticas (construção de nó AST) estão incompletas.
 *     Você deve preencher as chamadas a ast_new() nas ações marcadas.
 *
 * (D) Regras de CHAMADA DE FUNÇÃO [TODO-D]:
 *     A regra para lista de argumentos está esqueleto. Você deve
 *     completá-la para suportar listas de zero ou mais argumentos
 *     separados por vírgula, construindo a lista via ast_append().
 *
 * Após completar (C) e (D), o parser deverá reconhecer e construir a
 * AST correta para 100% dos programas de teste fornecidos.
 * =====================================================================
 *
 * REFERÊNCIA RÁPIDA DO BISON:
 *   $1, $2, ...  — atributos dos símbolos do lado direito da regra
 *   $$           — atributo do símbolo do lado esquerdo (resultado)
 *   %prec TOKEN  — associa uma regra a uma precedência específica
 *   %left, %right, %nonassoc — declaram associatividade e precedência
 *   Maior precedência = declarado mais abaixo na lista %left/%right.
 *
 * COMO COMPILAR: use 'make' — o Makefile invoca bison e gcc.
 */

%{
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
%}

/* -----------------------------------------------------------------------
 * Declaração do tipo dos atributos semânticos (%union)
 * ----------------------------------------------------------------------- */
%union {
    char        *sval;   /* string (lexemas de ID, LIT_INT, LIT_FLOAT, etc.) */
    ast_node_t  *node;   /* nó da AST */
    int          ival;   /* inteiro (usado para armazenar yylineno) */
}

/* -----------------------------------------------------------------------
 * Tokens — devem corresponder 1-a-1 com tokens.h
 * ----------------------------------------------------------------------- */
%token TK_PR_INT TK_PR_FLOAT TK_PR_BOOL TK_PR_CHAR
%token TK_PR_IF TK_PR_ELSE TK_PR_WHILE TK_PR_FOR
%token TK_PR_RETURN TK_PR_VOID TK_PR_ARRAY TK_PR_OF
%token TK_PR_LET TK_PR_FUN TK_PR_DO TK_PR_PRINT TK_PR_READ
%token TK_LIT_TRUE TK_LIT_FALSE
%token TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%token TK_OC_AND TK_OC_OR TK_OC_ARROW TK_OC_ASSIGN
%token TK_OC_PLUSEQ TK_OC_MINUSEQ
%token TK_ERROR

/* Tokens com atributo semântico */
%token <sval> TK_ID
%token <sval> TK_LIT_INT
%token <sval> TK_LIT_FLOAT
%token <sval> TK_LIT_CHAR
%token <sval> TK_LIT_STRING

/* -----------------------------------------------------------------------
 * Tipos dos não-terminais
 * ----------------------------------------------------------------------- */
%type <node> program
%type <node> toplevel_list toplevel_decl
%type <node> fun_decl param_list param_list_ne param
%type <node> var_decl array_decl
%type <node> type_spec
%type <node> block stmt_list stmt simple_stmt compound_stmt var_local
%type <node> assign_stmt if_stmt while_stmt for_stmt
%type <node> return_stmt print_stmt read_stmt call_stmt
%type <node> expr expr_list expr_list_ne
%type <node> lvalue literal

/* -----------------------------------------------------------------------
 * Precedência e associatividade de operadores
 * (Ordem: menor precedência no topo → maior precedência no fundo)
 * ----------------------------------------------------------------------- */
%right TK_OC_ASSIGN TK_OC_PLUSEQ TK_OC_MINUSEQ
%left  TK_OC_OR
%left  TK_OC_AND
%left  TK_OC_EQ TK_OC_NE
%left  '<' '>' TK_OC_LE TK_OC_GE
%left  '+' '-'
%left  '*' '/' '%'
%right '!' UMINUS         /* operadores unários — precedência mais alta */
%left  '[' TK_OC_ARROW    /* indexação e acesso a campo */

/* -----------------------------------------------------------------------
 * Símbolo inicial da gramática
 * ----------------------------------------------------------------------- */
%start program

%%
/* =======================================================================
 * Regras de produção da gramática LARA
 * ======================================================================= */

/* ------- Programa (regra raiz) ------- */
program
    : toplevel_list
        {
            $$ = ast_new(AST_PROGRAM, NULL, 1);
            $$->children[0] = $1;
            ast_root = $$;
        }
    | /* programa vazio */
        {
            $$ = ast_new(AST_PROGRAM, NULL, 1);
            ast_root = $$;
        }
    ;

/* ------- Lista de declarações de topo-nível ------- */
toplevel_list
    : toplevel_decl
        { $$ = $1; }
    | toplevel_list toplevel_decl
        { $$ = ast_append($1, $2); }
    ;

toplevel_decl
    : fun_decl    { $$ = $1; }
    | var_decl    { $$ = $1; }
    | array_decl  { $$ = $1; }
    ;

/* ------- Declaração de função ------- */
/* Sintaxe LARA:  fun tipo nome ( params ) { corpo }  */
fun_decl
    : TK_PR_FUN type_spec TK_ID '(' param_list ')' block
        {
            $$ = ast_new(AST_FUN_DECL, $3, yylineno);
            $$->children[0] = $2;   /* tipo de retorno */
            $$->children[1] = $5;   /* lista de parâmetros (pode ser NULL) */
            $$->children[2] = $7;   /* corpo (bloco) */
            free($3);
        }
    ;

/* Lista de parâmetros (pode ser vazia) */
param_list
    : /* vazia */       { $$ = NULL; }
    | param_list_ne     { $$ = $1;   }
    ;

param_list_ne
    : param                         { $$ = $1; }
    | param_list_ne ',' param       { $$ = ast_append($1, $3); }
    ;

/* Parâmetro formal: tipo nome */
param
    : type_spec TK_ID
        {
            $$ = ast_new(AST_PARAM, $2, yylineno);
            $$->children[0] = $1;
            free($2);
        }
    ;

/* ------- Declaração de variável global ------- */
/* Sintaxe LARA:  tipo nome ;  (global)  */
var_decl
    : type_spec TK_ID ';'
        {
            $$ = ast_new(AST_VAR_DECL, $2, yylineno);
            $$->children[0] = $1;
            sym_entry_t *_e = symtab_lookup(global_symtab, $2);
            if (_e) {
                _e->nature   = SYM_VAR;
                _e->datatype = str_to_datatype($1->value);
            }
            free($2);
        }
    ;

/* ------- Declaração de array ------- */
/* Sintaxe LARA:  array INT_LIT of tipo nome ;  */
array_decl
    : TK_PR_ARRAY TK_LIT_INT TK_PR_OF type_spec TK_ID ';'
        {
            $$ = ast_new(AST_ARRAY_DECL, $5, yylineno);
            $$->children[0] = ast_new(AST_LIT_INT, $2, yylineno);  /* tamanho */
            $$->children[1] = $4;                                    /* tipo base */
            sym_entry_t *_ea = symtab_lookup(global_symtab, $5);
            if (_ea) {
                _ea->nature     = SYM_ARRAY;
                _ea->datatype   = str_to_datatype($4->value);
                _ea->array_size = atoi($2);
            }
            free($2);
            free($5);
        }
    ;

/* ------- Especificador de tipo ------- */
type_spec
    : TK_PR_INT    { $$ = ast_new(AST_SYMBOL, "int",   yylineno); }
    | TK_PR_FLOAT  { $$ = ast_new(AST_SYMBOL, "float", yylineno); }
    | TK_PR_BOOL   { $$ = ast_new(AST_SYMBOL, "bool",  yylineno); }
    | TK_PR_CHAR   { $$ = ast_new(AST_SYMBOL, "char",  yylineno); }
    | TK_PR_VOID   { $$ = ast_new(AST_SYMBOL, "void",  yylineno); }
    ;

/* ------- Bloco de comandos ------- */
block
    : '{' stmt_list '}'
        {
            $$ = ast_new(AST_BLOCK, NULL, yylineno);
            $$->children[0] = $2;
        }
    | '{' '}'
        {
            $$ = ast_new(AST_BLOCK, NULL, yylineno);
        }
    ;

/* Lista de comandos.
 * Comandos simples terminam com ';'; compostos (if/while/for) não precisam. */
stmt_list
    : stmt
        { $$ = $1; }
    | stmt_list stmt
        { $$ = ast_append($1, $2); }
    ;

/* ------- Comandos ------- */
stmt
    : simple_stmt ';' { $$ = $1; }   /* simples: requer ';' */
    | compound_stmt   { $$ = $1; }   /* composto: sem ';' obrigatório */
    ;

/* Comandos simples — terminam com ';' */
simple_stmt
    : assign_stmt  { $$ = $1; }
    | return_stmt  { $$ = $1; }
    | print_stmt   { $$ = $1; }
    | read_stmt    { $$ = $1; }
    | call_stmt    { $$ = $1; }
    | var_local    { $$ = $1;   }  /* declaração local */
    ;

/* Comandos compostos — NÃO terminam com ';' */
compound_stmt
    : if_stmt    { $$ = $1; }
    | while_stmt { $$ = $1; }
    | for_stmt   { $$ = $1; }
    ;

/* Declaração de variável local: let nome := expr */
var_local
    : TK_PR_LET TK_ID TK_OC_ASSIGN expr
        {
            symtab_insert(global_symtab, $2, yylineno);
            $$ = ast_new(AST_VAR_DECL, $2, yylineno);
            $$->children[1] = $4;
            free($2);
        }
    ;

/* Atribuição: lvalue := expr  ou  lvalue += expr  ou  lvalue -= expr */
assign_stmt
    : lvalue TK_OC_ASSIGN expr
        {
            $$ = ast_new(AST_ASSIGN, ":=", yylineno);
            $$->children[0] = $1;
            $$->children[1] = $3;
        }
    | lvalue TK_OC_PLUSEQ expr
        {
            $$ = ast_new(AST_ASSIGN, "+=", yylineno);
            $$->children[0] = $1;
            $$->children[1] = $3;
        }
    | lvalue TK_OC_MINUSEQ expr
        {
            $$ = ast_new(AST_ASSIGN, "-=", yylineno);
            $$->children[0] = $1;
            $$->children[1] = $3;
        }
    ;

/* if com else opcional */
if_stmt
    : TK_PR_IF '(' expr ')' block
        {
            $$ = ast_new(AST_IF, NULL, yylineno);
            $$->children[0] = $3;  /* condição */
            $$->children[1] = $5;  /* bloco then */
        }
    | TK_PR_IF '(' expr ')' block TK_PR_ELSE block
        {
            $$ = ast_new(AST_IF, NULL, yylineno);
            $$->children[0] = $3;  /* condição */
            $$->children[1] = $5;  /* bloco then */
            $$->children[2] = $7;  /* bloco else */
        }
    ;

/* while: while (expr) do block */
while_stmt
    : TK_PR_WHILE '(' expr ')' TK_PR_DO block
        {
            $$ = ast_new(AST_WHILE, NULL, yylineno);
            $$->children[0] = $3;  /* condição */
            $$->children[1] = $6;  /* corpo */
        }
    ;

/* for: for (init; cond; step) block
 * init e step são assign_stmt (ex: i := 0); cond é expr (ex: i < 5) */
for_stmt
    : TK_PR_FOR '(' assign_stmt ';' expr ';' assign_stmt ')' block
        {
            $$ = ast_new(AST_FOR, NULL, yylineno);
            $$->children[0] = $3;  /* init (assign) */
            $$->children[1] = $5;  /* cond  (expr)   */
            $$->children[2] = $7;  /* step (assign) */
            $$->children[3] = $9;  /* corpo */
        }
    ;

/* return */
return_stmt
    : TK_PR_RETURN expr
        {
            $$ = ast_new(AST_RETURN, NULL, yylineno);
            $$->children[0] = $2;
        }
    ;

/* print */
print_stmt
    : TK_PR_PRINT expr
        {
            $$ = ast_new(AST_PRINT, NULL, yylineno);
            $$->children[0] = $2;
        }
    ;

/* read */
read_stmt
    : TK_PR_READ lvalue
        {
            $$ = ast_new(AST_READ, NULL, yylineno);
            $$->children[0] = $2;
        }
    ;

/* chamada de função como comando */
call_stmt
    : TK_ID '(' expr_list ')'
        {
            $$ = ast_new(AST_CALL, $1, yylineno);
            $$->children[0] = $3;
            free($1);
        }
    ;

/* ------- Expressões ------- */
expr
    /* Operadores binários aritméticos */
    : expr '+' expr  { $$ = ast_new(AST_EXPR_BINARY, "+",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr '-' expr  { $$ = ast_new(AST_EXPR_BINARY, "-",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr '*' expr  { $$ = ast_new(AST_EXPR_BINARY, "*",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr '/' expr  { $$ = ast_new(AST_EXPR_BINARY, "/",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr '%' expr  { $$ = ast_new(AST_EXPR_BINARY, "%",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }

    /* Operadores relacionais */
    | expr '<' expr         { $$ = ast_new(AST_EXPR_BINARY, "<",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr '>' expr         { $$ = ast_new(AST_EXPR_BINARY, ">",  yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr TK_OC_LE expr    { $$ = ast_new(AST_EXPR_BINARY, "<=", yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr TK_OC_GE expr    { $$ = ast_new(AST_EXPR_BINARY, ">=", yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr TK_OC_EQ expr    { $$ = ast_new(AST_EXPR_BINARY, "==", yylineno); $$->children[0]=$1; $$->children[1]=$3; }
    | expr TK_OC_NE expr    { $$ = ast_new(AST_EXPR_BINARY, "!=", yylineno); $$->children[0]=$1; $$->children[1]=$3; }

    /* Operadores lógicos
     *
     * TODO-C: as ações semânticas abaixo estão INCOMPLETAS.
     * Complete as chamadas a ast_new() para criar o nó AST_EXPR_BINARY
     * com o operador correto ("&&" ou "||") e os dois filhos ($1 e $3).
     * Siga o mesmo padrão das regras relacionais acima.
     */
    | expr TK_OC_AND expr
        {
            $$ = ast_new(AST_EXPR_BINARY, "&&", yylineno);
            $$->children[0] = $1;
            $$->children[1] = $3;
        }
    | expr TK_OC_OR expr
        {
            $$ = ast_new(AST_EXPR_BINARY, "||", yylineno);
            $$->children[0] = $1;
            $$->children[1] = $3;
        }

    /* Operador unário de negação lógica */
    | '!' expr
        {
            $$ = ast_new(AST_EXPR_UNARY, "!", yylineno);
            $$->children[0] = $2;
        }

    /* Operador unário menos (negativo aritmético) */
    | '-' expr %prec UMINUS
        {
            $$ = ast_new(AST_EXPR_UNARY, "-", yylineno);
            $$->children[0] = $2;
        }

    /* Expressão entre parênteses */
    | '(' expr ')'  { $$ = $2; }

    /* Chamada de função como expressão */
    | TK_ID '(' expr_list ')'
        {
            $$ = ast_new(AST_EXPR_CALL, $1, yylineno);
            $$->children[0] = $3;
            free($1);
        }

    /* Indexação de array: v[i] */
    | TK_ID '[' expr ']'
        {
            $$ = ast_new(AST_EXPR_INDEX, $1, yylineno);
            $$->children[0] = $3;
            free($1);
        }

    /* Acesso de campo via ponteiro: p->campo */
    | TK_ID TK_OC_ARROW TK_ID
        {
            $$ = ast_new(AST_EXPR_ARROW, $1, yylineno);
            $$->children[0] = ast_new(AST_SYMBOL, $3, yylineno);
            free($1);
            free($3);
        }

    /* Identificador simples */
    | TK_ID
        {
            $$ = ast_new(AST_SYMBOL, $1, yylineno);
            free($1);
        }

    /* Literais */
    | literal { $$ = $1; }
    ;

/* ------- Lista de argumentos de chamada de função ------- */
expr_list
    : /* vazia */    { $$ = NULL; }
    | expr_list_ne   { $$ = $1;   }
    ;

/*
 * TODO-D: a regra abaixo está INCOMPLETA.
 * Atualmente ela só reconhece uma única expressão.
 * Você deve adicionar uma regra para uma lista de expressões
 * separadas por vírgula, usando ast_append() para encadear os nós.
 *
 * Formato esperado: expr  |  expr_list_ne ',' expr
 *
 * Siga o mesmo padrão de param_list_ne acima.
 */
expr_list_ne
    : expr
        { $$ = $1; }
    | expr_list_ne ',' expr
        { $$ = ast_append($1, $3); }
    ;

/* ------- lvalue (lado esquerdo de atribuição) ------- */
lvalue
    : TK_ID
        {
            $$ = ast_new(AST_SYMBOL, $1, yylineno);
            free($1);
        }
    | TK_ID '[' expr ']'
        {
            $$ = ast_new(AST_EXPR_INDEX, $1, yylineno);
            $$->children[0] = $3;
            free($1);
        }
    | TK_ID TK_OC_ARROW TK_ID
        {
            $$ = ast_new(AST_EXPR_ARROW, $1, yylineno);
            $$->children[0] = ast_new(AST_SYMBOL, $3, yylineno);
            free($1);
            free($3);
        }
    ;

/* ------- Literais ------- */
literal
    : TK_LIT_INT    { $$ = ast_new(AST_LIT_INT,    $1, yylineno); free($1); }
    | TK_LIT_FLOAT  { $$ = ast_new(AST_LIT_FLOAT,  $1, yylineno); free($1); }
    | TK_LIT_CHAR   { $$ = ast_new(AST_LIT_CHAR,   $1, yylineno); free($1); }
    | TK_LIT_STRING { $$ = ast_new(AST_LIT_STRING,  $1, yylineno); free($1); }
    | TK_LIT_TRUE   { $$ = ast_new(AST_LIT_BOOL,   "true",  yylineno); }
    | TK_LIT_FALSE  { $$ = ast_new(AST_LIT_BOOL,   "false", yylineno); }
    ;

%%

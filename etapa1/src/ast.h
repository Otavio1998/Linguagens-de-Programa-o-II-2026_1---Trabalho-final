/*
 * ast.h — Interface da Árvore de Sintaxe Abstrata (AST)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * A AST é a principal estrutura de dados produzida pelo frontend do compilador.
 * Cada nó representa uma construção da linguagem LARA: expressão, comando,
 * declaração, função, etc. Os nós folha representam tokens (identificadores,
 * literais). Os nós internos representam operações ou estruturas compostas.
 *
 * ESTRUTURA DO NÓ:
 *   - type     : tipo do nó (enum ast_node_type)
 *   - value    : lexema associado (apenas para folhas; NULL nos demais)
 *   - children : array de ponteiros para filhos (até MAX_CHILDREN)
 *   - lineno   : linha do programa-fonte onde este nó foi criado
 *   - next     : próximo nó em uma lista (para listas de comandos,
 *                parâmetros, declarações — ver nota abaixo)
 *
 * NOTA SOBRE LISTAS:
 *   Em LARA, sempre que a gramática admite uma lista (lista de comandos,
 *   lista de parâmetros, lista de argumentos), a lista é representada
 *   como uma cadeia ligada via o campo 'next'. O primeiro nó da lista
 *   é o primeiro elemento; next aponta para o restante da lista.
 *   Isso simplifica a geração de código iterativa sobre listas.
 */

#ifndef AST_H
#define AST_H

#include <stdio.h>

/* Número máximo de filhos por nó. Suficiente para a maioria das
 * construções de LARA. Nós com aridade variável usam o campo 'next'. */
#define AST_MAX_CHILDREN 4

/* -----------------------------------------------------------------------
 * Enumeração dos tipos de nó da AST
 * ----------------------------------------------------------------------- */
typedef enum {
    /* --- Programa e declarações de topo-nível --- */
    AST_PROGRAM,        /* raiz da AST — lista de declarações */
    AST_FUN_DECL,       /* declaração de função: fun tipo nome(params) { body } */
    AST_VAR_DECL,       /* declaração de variável global ou local: let x := expr */
    AST_ARRAY_DECL,     /* declaração de array: array N of tipo nome */
    AST_PARAM,          /* parâmetro formal de função */

    /* --- Comandos (statements) --- */
    AST_BLOCK,          /* bloco de comandos: { cmd ; cmd ; ... } */
    AST_ASSIGN,         /* atribuição: lvalue := expr */
    AST_IF,             /* condicional: if (expr) bloco [else bloco] */
    AST_WHILE,          /* laço: while (expr) do bloco */
    AST_FOR,            /* laço: for (init; cond; step) bloco */
    AST_RETURN,         /* retorno: return expr */
    AST_PRINT,          /* saída: print expr */
    AST_READ,           /* entrada: read lvalue */
    AST_CALL,           /* chamada de função como comando */

    /* --- Expressões --- */
    AST_EXPR_CALL,      /* chamada de função como expressão: f(args) */
    AST_EXPR_INDEX,     /* indexação de array: v[i] */
    AST_EXPR_ARROW,     /* acesso de campo: p->campo */
    AST_EXPR_UNARY,     /* operador unário: !, - */
    AST_EXPR_BINARY,    /* operador binário: +, -, *, /, %, <, >, <=, >=, ==, !=, &&, || */

    /* --- Folhas (terminais) --- */
    AST_SYMBOL,         /* identificador (variável ou função) */
    AST_LIT_INT,        /* literal inteiro */
    AST_LIT_FLOAT,      /* literal float */
    AST_LIT_CHAR,       /* literal char */
    AST_LIT_STRING,     /* literal string */
    AST_LIT_BOOL,       /* literal bool: true ou false */

    AST_NODE_TYPES_COUNT  /* sentinela — não usar como tipo */
} ast_node_type_t;

/* -----------------------------------------------------------------------
 * Estrutura de um nó da AST
 * ----------------------------------------------------------------------- */
typedef struct ast_node {
    ast_node_type_t     type;
    char               *value;                      /* lexema (folhas) ou operador (AST_EXPR_BINARY/UNARY) */
    int                 lineno;                     /* linha no arquivo-fonte */
    struct ast_node    *children[AST_MAX_CHILDREN]; /* filhos */
    struct ast_node    *next;                       /* próximo em lista */
} ast_node_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * ast_new — cria um novo nó da AST.
 *
 * Parâmetros:
 *   type   : tipo do nó (enum acima)
 *   value  : string associada (será duplicada via strdup). Pode ser NULL.
 *   lineno : número de linha do programa-fonte (use yylineno do flex)
 *
 * Retorna: ponteiro para o novo nó, ou NULL em caso de falha de alocação.
 *
 * NOTA: internamente usa calloc — todos os filhos e next iniciam em NULL.
 */
ast_node_t *ast_new(ast_node_type_t type, const char *value, int lineno);

/*
 * ast_add_child — adiciona um filho ao nó pai na posição indicada.
 *
 * Parâmetros:
 *   parent : nó pai
 *   index  : posição do filho (0..AST_MAX_CHILDREN-1)
 *   child  : nó filho (pode ser NULL)
 *
 * Não faz nada se parent == NULL ou index fora do intervalo.
 */
void ast_add_child(ast_node_t *parent, int index, ast_node_t *child);

/*
 * ast_append — encadeia 'node' ao final da lista começando em 'list'.
 *
 * Use para construir listas de comandos, parâmetros, argumentos, etc.
 * Retorna 'list' se list != NULL (cabeça permanece a mesma),
 * ou 'node' se list == NULL (node passa a ser a cabeça da lista).
 */
ast_node_t *ast_append(ast_node_t *list, ast_node_t *node);

/*
 * ast_print — imprime a AST em formato indentado legível por humanos.
 *
 * Parâmetros:
 *   root   : raiz da AST (ou NULL para imprimir nada)
 *   indent : nível de indentação inicial (passe 0 na chamada raiz)
 *   out    : arquivo de saída (passe stdout para imprimir na tela)
 */
void ast_print(const ast_node_t *root, int indent, FILE *out);

/*
 * ast_free — libera recursivamente toda a memória da AST.
 *
 * Parâmetros:
 *   root : raiz da AST (ou NULL, que é ignorado)
 */
void ast_free(ast_node_t *root);

/*
 * ast_type_name — retorna o nome textual de um tipo de nó.
 * Útil para depuração e impressão.
 */
const char *ast_type_name(ast_node_type_t type);

#endif /* AST_H */

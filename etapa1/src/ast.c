/*
 * ast.c — Implementação da Árvore de Sintaxe Abstrata (AST)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Veja ast.h para a documentação da interface pública.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* -----------------------------------------------------------------------
 * Nomes dos tipos de nó (para impressão e depuração)
 * ----------------------------------------------------------------------- */
static const char *node_type_names[] = {
    /* Programa / declarações */
    "PROGRAM",
    "FUN_DECL",
    "VAR_DECL",
    "ARRAY_DECL",
    "PARAM",
    /* Comandos */
    "BLOCK",
    "ASSIGN",
    "IF",
    "WHILE",
    "FOR",
    "RETURN",
    "PRINT",
    "READ",
    "CALL",
    /* Expressões */
    "EXPR_CALL",
    "EXPR_INDEX",
    "EXPR_ARROW",
    "EXPR_UNARY",
    "EXPR_BINARY",
    /* Folhas */
    "SYMBOL",
    "LIT_INT",
    "LIT_FLOAT",
    "LIT_CHAR",
    "LIT_STRING",
    "LIT_BOOL",
    /* sentinela */
    "???"
};

/* -----------------------------------------------------------------------
 * ast_type_name
 * ----------------------------------------------------------------------- */
const char *ast_type_name(ast_node_type_t type)
{
    if (type < 0 || type >= AST_NODE_TYPES_COUNT)
        return "UNKNOWN";
    return node_type_names[type];
}

/* -----------------------------------------------------------------------
 * ast_new
 * ----------------------------------------------------------------------- */
ast_node_t *ast_new(ast_node_type_t type, const char *value, int lineno)
{
    /* calloc garante que todos os campos são inicializados a zero/NULL */
    ast_node_t *node = (ast_node_t *) calloc(1, sizeof(ast_node_t));
    if (node == NULL) {
        fprintf(stderr, "[AST] ERRO: falha de alocação de memória em ast_new.\n");
        return NULL;
    }
    node->type   = type;
    node->lineno = lineno;
    node->value  = (value != NULL) ? strdup(value) : NULL;
    /* children[] e next já são NULL por causa do calloc */
    return node;
}

/* -----------------------------------------------------------------------
 * ast_add_child
 * ----------------------------------------------------------------------- */
void ast_add_child(ast_node_t *parent, int index, ast_node_t *child)
{
    if (parent == NULL) return;
    if (index < 0 || index >= AST_MAX_CHILDREN) {
        fprintf(stderr, "[AST] AVISO: índice %d fora do intervalo em ast_add_child.\n", index);
        return;
    }
    parent->children[index] = child;
}

/* -----------------------------------------------------------------------
 * ast_append — encadeia ao final de uma lista ligada via 'next'
 * ----------------------------------------------------------------------- */
ast_node_t *ast_append(ast_node_t *list, ast_node_t *node)
{
    if (node == NULL) return list;
    if (list == NULL) return node;

    /* Percorre até o último elemento da lista */
    ast_node_t *cur = list;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = node;
    return list;
}

/* -----------------------------------------------------------------------
 * ast_print — impressão indentada recursiva
 *
 * Formato de saída:
 *   <indentação> [TIPO] "valor" (linha N)
 *   <indentação>   filho 0: ...
 *   <indentação>   filho 1: ...
 *   ...
 *   <indentação> (next) -> ...
 * ----------------------------------------------------------------------- */
void ast_print(const ast_node_t *root, int indent, FILE *out)
{
    if (root == NULL) return;
    if (out  == NULL) out = stdout;

    /* Imprime indentação */
    for (int i = 0; i < indent; i++)
        fprintf(out, "  ");

    /* Imprime tipo e valor do nó */
    fprintf(out, "[%s]", ast_type_name(root->type));
    if (root->value != NULL)
        fprintf(out, " \"%s\"", root->value);
    fprintf(out, "  (linha %d)\n", root->lineno);

    /* Imprime filhos recursivamente */
    for (int i = 0; i < AST_MAX_CHILDREN; i++) {
        if (root->children[i] != NULL) {
            for (int j = 0; j < indent + 1; j++) fprintf(out, "  ");
            fprintf(out, "filho[%d]:\n", i);
            ast_print(root->children[i], indent + 2, out);
        }
    }

    /* Imprime próximo elemento da lista (mesmo nível) */
    if (root->next != NULL) {
        ast_print(root->next, indent, out);
    }
}

/* -----------------------------------------------------------------------
 * ast_free — liberação recursiva
 * ----------------------------------------------------------------------- */
void ast_free(ast_node_t *root)
{
    if (root == NULL) return;

    /* Libera filhos */
    for (int i = 0; i < AST_MAX_CHILDREN; i++)
        ast_free(root->children[i]);

    /* Libera próximo da lista */
    ast_free(root->next);

    /* Libera string de valor */
    if (root->value != NULL)
        free(root->value);

    /* Libera o próprio nó */
    free(root);
}

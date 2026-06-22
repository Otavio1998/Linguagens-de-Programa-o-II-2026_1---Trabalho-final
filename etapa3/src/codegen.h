/*
 * codegen.h — Interface do Gerador de Código TAC (Etapa 3)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Etapa 3 adiciona:
 *   - codegen_bool_expr(): traduz expressões booleanas com curto-circuito
 *     usando a técnica de back-patching (ver backpatch.h).
 *   - Suporte a if/else, while e for em codegen_stmt().
 */

#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "symtab.h"
#include "tac.h"
#include "backpatch.h"

/* -----------------------------------------------------------------------
 * Estado do gerador de código
 * ----------------------------------------------------------------------- */
typedef struct {
    tac_instr_t  *code;          /* lista de instruções geradas (resultado) */
    symtab_t     *symtab;        /* tabela de símbolos global               */
    char         *current_func;  /* nome da função sendo compilada          */
    int           local_offset;  /* próximo offset disponível no frame      */
} codegen_ctx_t;

/* -----------------------------------------------------------------------
 * Interface pública — funções herdadas da Etapa 2
 * ----------------------------------------------------------------------- */

codegen_ctx_t *codegen_new(symtab_t *symtab);
void codegen_free(codegen_ctx_t *ctx);
void codegen_program(codegen_ctx_t *ctx, ast_node_t *program);
void codegen_fun(codegen_ctx_t *ctx, ast_node_t *fun_decl);
void codegen_stmt(codegen_ctx_t *ctx, ast_node_t *stmt);
char *codegen_expr(codegen_ctx_t *ctx, ast_node_t *expr);
void codegen_emit(codegen_ctx_t *ctx, tac_op_t op,
                  const char *result, const char *arg1, const char *arg2);

/* -----------------------------------------------------------------------
 * Nova função — Etapa 3
 * ----------------------------------------------------------------------- */

/*
 * codegen_bool_expr — traduz expressão booleana com curto-circuito.
 *
 * Retorna um bool_result_t com:
 *   true_list  — lista de saltos (TAC_JUMPT) a preencher quando expr=true
 *   false_list — lista de saltos (TAC_JUMPF) a preencher quando expr=false
 *
 * Os casos de && e || são implementados com back-patching.
 * Para expressões simples (relacionais, variáveis), emite um par JUMPT/JUMPF.
 *
 * TODO-E3-A: implemente os casos de && e || em codegen_bool_expr().
 */
bool_result_t codegen_bool_expr(codegen_ctx_t *ctx, ast_node_t *expr);

#endif /* CODEGEN_H */

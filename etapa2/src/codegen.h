/*
 * codegen.h — Interface do Gerador de Código TAC
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * O gerador de código percorre a AST produzida pela Etapa 1 e emite
 * instruções TAC. Ele é invocado após a análise sintática bem-sucedida.
 *
 * ESTRUTURA DE GERAÇÃO:
 *   codegen_program()  — ponto de entrada, percorre declarações de topo
 *   codegen_fun()      — gera código para uma função
 *   codegen_stmt()     — gera código para um comando
 *   codegen_expr()     — gera código para uma expressão;
 *                        retorna o nome do temporário/variável com resultado
 *
 * RETORNO DE codegen_expr():
 *   Retorna uma string alocada dinamicamente com o nome do temporário ou
 *   variável que contém o resultado da expressão. O chamador é responsável
 *   por liberar esta string com free() após uso.
 */

#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "symtab.h"
#include "tac.h"

/* -----------------------------------------------------------------------
 * Estado do gerador de código
 * Mantém a lista de instruções geradas e o escopo atual.
 * ----------------------------------------------------------------------- */
typedef struct {
    tac_instr_t  *code;          /* lista de instruções geradas (resultado) */
    symtab_t     *symtab;        /* tabela de símbolos global               */
    char         *current_func;  /* nome da função sendo compilada          */
    int           local_offset;  /* próximo offset disponível no frame      */
} codegen_ctx_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * codegen_new — cria e inicializa um contexto de geração de código.
 */
codegen_ctx_t *codegen_new(symtab_t *symtab);

/*
 * codegen_free — libera o contexto (não libera o TAC — use tac_free).
 */
void codegen_free(codegen_ctx_t *ctx);

/*
 * codegen_program — ponto de entrada: percorre a AST do programa completo
 * e popula ctx->code com as instruções TAC geradas.
 */
void codegen_program(codegen_ctx_t *ctx, ast_node_t *program);

/*
 * codegen_fun — gera código para uma declaração de função.
 */
void codegen_fun(codegen_ctx_t *ctx, ast_node_t *fun_decl);

/*
 * codegen_stmt — gera código para um comando (statement).
 */
void codegen_stmt(codegen_ctx_t *ctx, ast_node_t *stmt);

/*
 * codegen_expr — gera código para uma expressão.
 * Retorna o nome do temporário/variável que contém o resultado.
 * O chamador deve liberar a string retornada com free().
 * Retorna NULL em caso de erro.
 */
char *codegen_expr(codegen_ctx_t *ctx, ast_node_t *expr);

/*
 * codegen_emit — adiciona uma instrução ao contexto.
 * Atalho para tac_append(ctx->code, tac_new(...)).
 */
void codegen_emit(codegen_ctx_t *ctx, tac_op_t op,
                  const char *result, const char *arg1, const char *arg2);

#endif /* CODEGEN_H */

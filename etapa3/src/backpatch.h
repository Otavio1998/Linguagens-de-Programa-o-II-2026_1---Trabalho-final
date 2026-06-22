/*
 * backpatch.h — Back-patching para expressões booleanas com curto-circuito
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este módulo é PARCIALMENTE FORNECIDO. Os alunos devem implementar
 * patch_list_backpatch() (TODO-E3-E) e patch_list_merge() (TODO-E3-F)
 * em backpatch.c, e usar as funções resultantes em codegen.c.
 *
 * CONCEITO:
 *   Quando traduzimos expressões booleanas com curto-circuito, precisamos
 *   emitir saltos condicionais antes de saber para onde eles vão. A técnica
 *   de back-patching resolve isso em duas fases:
 *
 *   1. EMISSÃO: emite a instrução de salto com rótulo placeholder ("???")
 *      e registra essa instrução em uma "lista de saltos pendentes".
 *
 *   2. PREENCHIMENTO: quando o rótulo destino é conhecido, percorre a lista
 *      de saltos pendentes e substitui "???" pelo rótulo real.
 *
 * USO TÍPICO:
 *
 *   // Traduzindo:  if (a < b) stmt
 *
 *   tac_instr_t *jf = tac_new(TAC_JUMPF, "???", "a_lt_b", NULL);
 *   ctx->code = tac_append(ctx->code, jf);
 *   patch_list_t *false_list = patch_list_make(jf);
 *
 *   // ... gera código do then-block ...
 *
 *   char *lend = tac_new_label();
 *   patch_list_backpatch(false_list, lend);
 *   codegen_emit(ctx, TAC_LABEL, lend, NULL, NULL);
 *   free(lend);
 *   patch_list_free(false_list);
 */

#ifndef BACKPATCH_H
#define BACKPATCH_H

#include "tac.h"

/* -----------------------------------------------------------------------
 * Lista de saltos pendentes
 * ----------------------------------------------------------------------- */
typedef struct patch_list {
    tac_instr_t       *instr;   /* instrução TAC cujo result está pendente */
    struct patch_list *next;
} patch_list_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * patch_list_make — cria uma lista com um único elemento.
 * 'instr' deve ser uma instrução TAC_JUMP, TAC_JUMPF ou TAC_JUMPT
 * cujo campo result ainda é placeholder ("???").
 */
patch_list_t *patch_list_make(tac_instr_t *instr);

/*
 * patch_list_merge — une duas listas de saltos pendentes em uma só.
 * Retorna uma lista que contém todos os elementos de l1 seguidos de l2.
 * As listas originais não devem ser usadas após a chamada.
 *
 * TODO-E3-F: implemente em backpatch.c.
 */
patch_list_t *patch_list_merge(patch_list_t *l1, patch_list_t *l2);

/*
 * patch_list_backpatch — preenche todos os saltos pendentes com 'label'.
 * Para cada instrução da lista, substitui o campo result (que contém "???")
 * por uma cópia de label. Não libera a lista.
 *
 * TODO-E3-E: implemente em backpatch.c.
 */
void patch_list_backpatch(patch_list_t *list, const char *label);

/*
 * patch_list_free — libera a lista (não libera as instruções TAC).
 */
void patch_list_free(patch_list_t *list);

/* -----------------------------------------------------------------------
 * Resultado de tradução de expressão booleana
 *
 * Ao traduzir uma expressão booleana com curto-circuito, o gerador
 * produz duas listas de saltos pendentes:
 *   true_list  — saltos a preencher quando a expressão for verdadeira
 *   false_list — saltos a preencher quando a expressão for falsa
 * ----------------------------------------------------------------------- */
typedef struct {
    patch_list_t *true_list;
    patch_list_t *false_list;
} bool_result_t;

#endif /* BACKPATCH_H */

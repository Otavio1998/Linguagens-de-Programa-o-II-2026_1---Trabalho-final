/*
 * backpatch.c — Implementação do back-patching
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * =====================================================================
 * TAREFAS DOS ALUNOS:
 *
 * TODO-E3-E: Implemente patch_list_backpatch().
 *   Esta é a operação central da técnica: percorra a lista e substitua
 *   o campo result de cada instrução TAC pelo rótulo real.
 *   Sem esta implementação, todos os saltos ficam com destino "???" e
 *   o assembly gerado é inválido.
 *
 * TODO-E3-F: Implemente patch_list_merge().
 *   Une duas listas de saltos pendentes em uma só lista ligada.
 *   Necessário para combinar as listas de && e || em codegen_bool_expr().
 *   Sem esta implementação, expressões booleanas compostas perdem saltos.
 * =====================================================================
 *
 * As funções patch_list_make() e patch_list_free() são fornecidas completas.
 */

#include <stdlib.h>
#include <string.h>
#include "backpatch.h"

/* Fornecida completa. */
patch_list_t *patch_list_make(tac_instr_t *instr)
{
    patch_list_t *p = calloc(1, sizeof(patch_list_t));
    if (!p) return NULL;
    p->instr = instr;
    p->next  = NULL;
    return p;
}

/*
 * TODO-E3-F: Una as duas listas de saltos pendentes em uma única lista.
 *
 * A lista resultante deve conter todos os elementos de l1 seguidos de
 * todos os elementos de l2. Retorne o início da lista resultante.
 *
 * Algoritmo:
 *   - Se l1 for NULL, retorne l2.
 *   - Se l2 for NULL, retorne l1.
 *   - Percorra l1 até o último nó; aponte seu next para l2.
 *   - Retorne l1.
 *
 * Uso típico: combinar false_lists de e1 e e2 em (e1 && e2).
 */
patch_list_t *patch_list_merge(patch_list_t *l1, patch_list_t *l2)
{
    if (!l1) return l2;
    if (!l2) return l1;
    patch_list_t *p = l1;
    while (p->next) p = p->next;
    p->next = l2;
    return l1;
}

/*
 * TODO-E3-E: Preencha todos os saltos pendentes da lista com o rótulo real.
 *
 * Para cada nó da lista, substitua o campo result da instrução TAC
 * pelo rótulo fornecido. A instrução TAC já foi emitida (está na lista
 * encadeada de instruções); você está "voltando atrás" para completá-la.
 *
 * Algoritmo:
 *   Para cada p na lista:
 *     free(p->instr->result);
 *     p->instr->result = strdup(label);
 *
 * Sem esta implementação, os saltos mantêm destino "???" e o assembly
 * gerado pelo asmgen conterá instruções de salto inválidas.
 */
void patch_list_backpatch(patch_list_t *list, const char *label)
{
    for (patch_list_t *p = list; p; p = p->next) {
        free(p->instr->result);
        p->instr->result = strdup(label);
    }
}

/* Fornecida completa. */
void patch_list_free(patch_list_t *list)
{
    while (list) {
        patch_list_t *next = list->next;
        free(list);
        list = next;
    }
}

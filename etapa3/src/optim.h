/*
 * optim.h — Otimizações locais sobre TAC  (Opcional — Apêndice A)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este módulo é OPCIONAL e não é avaliado. Alunos que queiram explorar
 * otimizações de código intermediário podem implementar os TODOs aqui.
 *
 * CONCEITO:
 *   O compilador já gera TAC correto. Porém, o TAC contém muitos
 *   temporários redundantes e expressões computadas em tempo de compilação.
 *   Este módulo permite aplicar dois passes clássicos de otimização local:
 *
 *   1. Identificar os Blocos Básicos (BB) do TAC de cada função.
 *   2. Construir o Grafo de Fluxo de Controle (CFG) entre os BBs.
 *   3. Dentro de cada BB, aplicar:
 *       - Dobragem de constantes (constant folding)
 *       - Propagação de cópias (copy propagation)
 *
 * TODOs:
 *   TODO-OPT-A  cfg_build()     — identificar BBs e construir o CFG
 *   TODO-OPT-B  bb_const_fold() — dobragem de constantes dentro de BB
 *   TODO-OPT-C  bb_copy_prop()  — propagação de cópias dentro de BB
 *
 * Flags de depuração (main.c):
 *   ./compilador -O        — ativa otimização antes de gerar assembly
 *   ./compilador -O -tac   — mostra TAC otimizado
 *   ./compilador -cfg      — imprime o CFG de cada função (requer TODO-OPT-A)
 */

#ifndef OPTIM_H
#define OPTIM_H

#include <stdio.h>
#include "tac.h"

/* -----------------------------------------------------------------------
 * Bloco Básico (BB)
 *
 * Sequência maximal de instruções TAC com entrada única (first) e saída
 * única (last). Não há desvios internos: o fluxo entra pelo início e
 * sai pelo fim.
 * ----------------------------------------------------------------------- */
typedef struct basic_block {
    int                   id;      /* identificador sequencial (0-based)    */
    tac_instr_t          *first;   /* primeira instrução do bloco            */
    tac_instr_t          *last;    /* última  instrução do bloco             */
    struct basic_block  **succ;    /* array de blocos sucessores             */
    int                   n_succ;
    struct basic_block  **pred;    /* array de blocos predecessores          */
    int                   n_pred;
} basic_block_t;

/* -----------------------------------------------------------------------
 * Grafo de Fluxo de Controle (CFG) de uma função
 *
 * blocks[0] é sempre o bloco de entrada (primeiro BB da função).
 * ----------------------------------------------------------------------- */
typedef struct {
    basic_block_t **blocks;
    int             n_blocks;
    int             capacity;   /* capacidade interna do array              */
} cfg_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * cfg_build — Constrói o CFG de uma função.
 *
 * func_begin : instrução TAC_BEGINFUNC da função (inclusive)
 * func_end   : instrução TAC_ENDFUNC correspondente (exclusive — não incluída)
 *
 * Retorna um cfg_t alocado dinamicamente; libere com cfg_free().
 *
 * TODO-OPT-A: implementar em optim.c (ver comentário detalhado lá).
 */
cfg_t *cfg_build(tac_instr_t *func_begin, tac_instr_t *func_end);

/*
 * cfg_free — Libera o CFG (não libera as instruções TAC, que pertencem ao
 * codegen context).
 */
void cfg_free(cfg_t *cfg);

/*
 * cfg_print — Imprime o CFG em formato texto para depuração.
 * Mostra cada bloco com suas instruções e os IDs dos sucessores.
 */
void cfg_print(cfg_t *cfg, FILE *out);

/*
 * bb_const_fold — Dobragem de constantes dentro de um bloco básico.
 *
 * Avalia em tempo de compilação expressões aritméticas cujos dois operandos
 * são literais inteiros, substituindo a instrução por TAC_COPY com o
 * resultado pré-calculado.
 *
 * Retorna o número de expressões dobradas.
 *
 * TODO-OPT-B: implementar em optim.c.
 */
int bb_const_fold(basic_block_t *bb);

/*
 * bb_copy_prop — Propagação de cópias dentro de um bloco básico.
 *
 * Mantém uma tabela de cópias ativas (d = s geradas por TAC_COPY) e
 * substitui usos posteriores de d por s, enquanto nenhuma das duas
 * variáveis for redefinida.
 *
 * Retorna o número de substituições realizadas.
 *
 * TODO-OPT-C: implementar em optim.c.
 */
int bb_copy_prop(basic_block_t *bb);

/*
 * optim_program — Aplica todas as otimizações ao programa TAC completo.
 *
 * Percorre a lista TAC, localiza cada função (TAC_BEGINFUNC … TAC_ENDFUNC),
 * constrói o CFG e aplica bb_const_fold + bb_copy_prop em cada BB.
 * Fornecida completa — chama os TODOs acima.
 */
void optim_program(tac_instr_t *prog);

#endif /* OPTIM_H */

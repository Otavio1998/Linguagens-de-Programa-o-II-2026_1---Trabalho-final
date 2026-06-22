/*
 * asmgen.h — Interface do Gerador de Assembly x86-64
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este módulo traduz a lista de instruções TAC produzida pela Etapa 3
 * em assembly x86-64 no formato AT&T (usado pelo assembler GNU as/gcc).
 *
 * PIPELINE:
 *   TAC list  →  [otimizações TAC]  →  asmgen  →  arquivo .s
 *
 * O arquivo .s gerado pode ser montado e ligado com:
 *   gcc programa.s -o programa -no-pie
 */

#ifndef ASMGEN_H
#define ASMGEN_H

#include <stdio.h>
#include "tac.h"
#include "symtab.h"

/* -----------------------------------------------------------------------
 * Contexto do gerador de assembly
 * ----------------------------------------------------------------------- */
typedef struct {
    FILE       *out;            /* arquivo de saída (.s)                    */
    symtab_t   *symtab;        /* tabela de símbolos                        */
    int         frame_size;    /* tamanho do frame atual (em bytes)          */
    int         temp_count;    /* número de temporários na função atual      */
    /* Mapeamento de nomes de temporários/vars para offsets no frame.
     * Implementação simples: array de pares (nome, offset). */
    char      **var_names;     /* nomes das variáveis/temporários            */
    int        *var_offsets;   /* offsets correspondentes no frame (%rbp)    */
    int         var_count;     /* número de entradas no mapeamento           */
    int         var_capacity;  /* capacidade alocada                         */
} asmgen_ctx_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * asmgen_new — cria e inicializa o contexto do gerador.
 */
asmgen_ctx_t *asmgen_new(FILE *out, symtab_t *symtab);

/*
 * asmgen_free — libera o contexto.
 */
void asmgen_free(asmgen_ctx_t *ctx);

/*
 * asmgen_program — ponto de entrada: traduz toda a lista TAC para assembly.
 * Emite o preâmbulo (.text, .globl main), todas as funções e o segmento .bss.
 */
void asmgen_program(asmgen_ctx_t *ctx, const tac_instr_t *tac_list);

/*
 * asmgen_function — traduz uma função (beginFunc...endFunc) para assembly.
 */
void asmgen_function(asmgen_ctx_t *ctx, const tac_instr_t *begin);

/*
 * asmgen_instr — traduz uma única instrução TAC.
 * Funções internas; expostas para facilitar testes unitários.
 */
void asmgen_instr(asmgen_ctx_t *ctx, const tac_instr_t *instr);

/*
 * asmgen_operand — retorna a representação assembly de um operando
 * (variável, temporário ou literal). String alocada dinamicamente.
 * Chamador deve liberar com free().
 */
char *asmgen_operand(asmgen_ctx_t *ctx, const char *name);

/*
 * asmgen_var_offset — retorna o offset de uma variável/temporário no frame.
 * Retorna 0 e imprime aviso se não encontrado.
 */
int asmgen_var_offset(asmgen_ctx_t *ctx, const char *name);

/*
 * asmgen_var_register — registra uma nova variável/temporário no frame
 * com o offset especificado.
 */
void asmgen_var_register(asmgen_ctx_t *ctx, const char *name, int offset);

#endif /* ASMGEN_H */

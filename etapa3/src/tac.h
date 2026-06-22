/*
 * tac.h — Código de Três Endereços (TAC)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Define a estrutura de uma instrução TAC e as funções para criar,
 * encadear e imprimir listas de instruções TAC.
 *
 * O TAC é a representação intermediária usada nas Etapas 2 e 3.
 * Na Etapa 4, o TAC será traduzido para código assembly x86-64.
 */

#ifndef TAC_H
#define TAC_H

#include <stdio.h>

/* -----------------------------------------------------------------------
 * Operações TAC
 * ----------------------------------------------------------------------- */
typedef enum {
    /* Movimentação e cópia */
    TAC_COPY,           /* result = arg1                    */
    /* Aritméticas */
    TAC_ADD,            /* result = arg1 + arg2             */
    TAC_SUB,            /* result = arg1 - arg2             */
    TAC_MUL,            /* result = arg1 * arg2             */
    TAC_DIV,            /* result = arg1 / arg2             */
    TAC_MOD,            /* result = arg1 % arg2             */
    TAC_NEG,            /* result = -arg1                   */
    /* Relacionais (resultado: 0 ou 1) */
    TAC_LT,             /* result = arg1 < arg2             */
    TAC_GT,             /* result = arg1 > arg2             */
    TAC_LE,             /* result = arg1 <= arg2            */
    TAC_GE,             /* result = arg1 >= arg2            */
    TAC_EQ,             /* result = arg1 == arg2            */
    TAC_NE,             /* result = arg1 != arg2            */
    /* Lógicas (Etapa 3) */
    TAC_NOT,            /* result = !arg1                   */
    TAC_AND,            /* result = arg1 && arg2            */
    TAC_OR,             /* result = arg1 || arg2            */
    /* Desvios (Etapa 3) */
    TAC_LABEL,          /* result: (define um rótulo)       */
    TAC_JUMP,           /* goto result                      */
    TAC_JUMPF,          /* if !arg1 goto result             */
    TAC_JUMPT,          /* if  arg1 goto result             */
    /* Arrays */
    TAC_LOAD,           /* result = arg1[arg2]              */
    TAC_STORE,          /* arg1[arg2] = result              */
    /* Funções (Etapa 3) */
    TAC_BEGINFUNC,      /* início de função: result=nome    */
    TAC_ENDFUNC,        /* fim de função                    */
    TAC_PARAM,          /* parâmetro: arg1=valor            */
    TAC_CALL,           /* result = call arg1 arg2=#params  */
    TAC_RETURN,         /* return arg1                      */
    TAC_RETURN_VOID,    /* return (sem valor)               */
    /* Declarações */
    TAC_DECL_GLOBAL,    /* global result, arg1=size_bytes   */
    TAC_DECL_LOCAL,     /* local result, arg1=offset        */
    /* I/O */
    TAC_PRINT,          /* print arg1                       */
    TAC_READ,           /* read result                      */

    TAC_NOP,            /* sem operação (placeholder)       */
    TAC_OP_COUNT        /* sentinela                        */
} tac_op_t;

/* -----------------------------------------------------------------------
 * Instrução TAC (quádrupla)
 * ----------------------------------------------------------------------- */
typedef struct tac_instr {
    tac_op_t          op;       /* operação                 */
    char             *result;   /* destino ou rótulo        */
    char             *arg1;     /* primeiro operando        */
    char             *arg2;     /* segundo operando         */
    struct tac_instr *next;     /* próxima instrução        */
} tac_instr_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * tac_new — cria uma nova instrução TAC.
 * As strings são duplicadas (strdup); passe NULL para campos não usados.
 */
tac_instr_t *tac_new(tac_op_t op,
                     const char *result,
                     const char *arg1,
                     const char *arg2);

/*
 * tac_append — encadeia 'instr' ao final da lista 'list'.
 * Retorna o início da lista (que não muda).
 * Se list == NULL, retorna instr.
 */
tac_instr_t *tac_append(tac_instr_t *list, tac_instr_t *instr);

/*
 * tac_concat — concatena duas listas de instruções TAC.
 * Retorna o início da lista combinada (primeiro os de 'a', depois os de 'b').
 */
tac_instr_t *tac_concat(tac_instr_t *a, tac_instr_t *b);

/*
 * tac_print — imprime a lista de instruções TAC em formato legível.
 */
void tac_print(const tac_instr_t *list, FILE *out);

/*
 * tac_free — libera toda a memória da lista de instruções TAC.
 */
void tac_free(tac_instr_t *list);

/*
 * tac_new_temp — gera um novo nome de temporário único (_t1, _t2, ...).
 * A string retornada é alocada dinamicamente (deve ser liberada com free).
 */
char *tac_new_temp(void);

/*
 * tac_new_label — gera um novo rótulo único (_L1, _L2, ...).
 * A string retornada é alocada dinamicamente (deve ser liberada com free).
 */
char *tac_new_label(void);

/*
 * tac_reset_counters — reinicia os contadores de temporários e rótulos.
 * Útil para testes.
 */
void tac_reset_counters(void);

/*
 * tac_op_name — retorna o nome textual de uma operação TAC.
 */
const char *tac_op_name(tac_op_t op);

#endif /* TAC_H */

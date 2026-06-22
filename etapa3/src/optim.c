/*
 * optim.c — Otimizações locais sobre TAC  (ESQUELETO — Opcional)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Módulo OPCIONAL (Apêndice A da especificação). Não é avaliado.
 *
 * ARQUITETURA:
 *
 *   optim_program(prog)                        ← fornecida completa
 *     para cada função (TAC_BEGINFUNC…TAC_ENDFUNC):
 *       cfg = cfg_build(begin, end)            ← TODO-OPT-A
 *       para cada BB em cfg:
 *         bb_const_fold(bb)                    ← TODO-OPT-B
 *         bb_copy_prop(bb)                     ← TODO-OPT-C
 *       cfg_free(cfg)
 *
 * FORNECIDO COMPLETO (não modificar):
 *   cfg_new(), bb_new(), bb_add_succ()   — alocação e ligação de nós
 *   cfg_find_by_label()                  — busca bloco pelo rótulo TAC
 *   is_int_literal()                     — testa se string é inteiro literal
 *   cfg_free(), cfg_print()              — liberação e depuração
 *   optim_program()                      — ponto de entrada da otimização
 *
 * A IMPLEMENTAR (TODOs):
 *   cfg_build()     — TODO-OPT-A
 *   bb_const_fold() — TODO-OPT-B
 *   bb_copy_prop()  — TODO-OPT-C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "optim.h"

/* -----------------------------------------------------------------------
 * Funções auxiliares internas — fornecidas completas, não modificar
 * ----------------------------------------------------------------------- */

static cfg_t *cfg_new(void)
{
    cfg_t *cfg   = calloc(1, sizeof(cfg_t));
    cfg->capacity = 8;
    cfg->blocks   = calloc(cfg->capacity, sizeof(basic_block_t *));
    return cfg;
}

static basic_block_t *bb_new(int id, tac_instr_t *first)
{
    basic_block_t *b = calloc(1, sizeof(basic_block_t));
    b->id    = id;
    b->first = first;
    return b;
}

/* Adiciona aresta from→to e atualiza succ/pred de ambos os lados. */
static void bb_add_succ(basic_block_t *from, basic_block_t *to)
{
    from->succ = realloc(from->succ, (from->n_succ + 1) * sizeof(basic_block_t *));
    from->succ[from->n_succ++] = to;
    to->pred   = realloc(to->pred,   (to->n_pred   + 1) * sizeof(basic_block_t *));
    to->pred[to->n_pred++] = from;
}

/* Encontra o bloco cujo first é um TAC_LABEL com o nome dado. */
static basic_block_t *cfg_find_by_label(cfg_t *cfg, const char *label)
{
    if (!label) return NULL;
    for (int i = 0; i < cfg->n_blocks; i++) {
        tac_instr_t *f = cfg->blocks[i]->first;
        if (f && f->op == TAC_LABEL && f->result && strcmp(f->result, label) == 0)
            return cfg->blocks[i];
    }
    return NULL;
}

/* Retorna 1 se s representa um literal inteiro ("42", "-7", "0"). */
static int is_int_literal(const char *s)
{
    if (!s || !*s) return 0;
    const char *p = s;
    if (*p == '-') p++;
    if (!isdigit((unsigned char)*p)) return 0;
    while (*p) {
        if (!isdigit((unsigned char)*p)) return 0;
        p++;
    }
    return 1;
}

/* -----------------------------------------------------------------------
 * cfg_free — fornecida completa
 * ----------------------------------------------------------------------- */
void cfg_free(cfg_t *cfg)
{
    if (!cfg) return;
    for (int i = 0; i < cfg->n_blocks; i++) {
        basic_block_t *b = cfg->blocks[i];
        if (b) { free(b->succ); free(b->pred); free(b); }
    }
    free(cfg->blocks);
    free(cfg);
}

/* -----------------------------------------------------------------------
 * cfg_print — fornecida completa
 * ----------------------------------------------------------------------- */
void cfg_print(cfg_t *cfg, FILE *out)
{
    if (!cfg) return;
    fprintf(out, "# CFG: %d bloco(s) básico(s)\n", cfg->n_blocks);
    for (int i = 0; i < cfg->n_blocks; i++) {
        basic_block_t *b = cfg->blocks[i];
        fprintf(out, "BB%d", b->id);
        if (b->first && b->first->op == TAC_LABEL && b->first->result)
            fprintf(out, " [%s]", b->first->result);
        fprintf(out, ":\n");

        /* Instrução por instrução */
        for (tac_instr_t *t = b->first; t; t = t->next) {
            fprintf(out, "  %-12s", tac_op_name(t->op));
            if (t->result) fprintf(out, "  %s", t->result);
            if (t->arg1)   fprintf(out, ", %s", t->arg1);
            if (t->arg2)   fprintf(out, ", %s", t->arg2);
            fprintf(out, "\n");
            if (t == b->last) break;
        }

        /* Sucessores */
        if (b->n_succ > 0) {
            fprintf(out, "  -> ");
            for (int j = 0; j < b->n_succ; j++)
                fprintf(out, "BB%d%s", b->succ[j]->id,
                        (j + 1 < b->n_succ) ? ", " : "");
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
    }
}

/* -----------------------------------------------------------------------
 * TODO-OPT-A: cfg_build
 * -----------------------------------------------------------------------
 *
 * Constrói o CFG de uma função a partir do TAC entre func_begin (inclusive)
 * e func_end (exclusive).
 *
 * ── FASE 1: Identificar líderes e criar blocos ───────────────────────────
 *
 *   Um LÍDER é a primeira instrução de um bloco básico.
 *   São líderes no TAC gerado pelo compilador LC−:
 *
 *   (1) A primeira instrução após TAC_BEGINFUNC.
 *   (2) Toda instrução TAC_LABEL  — no nosso TAC, rótulos só aparecem como
 *       alvos de desvios, portanto qualquer rótulo abre um novo bloco.
 *   (3) A instrução imediatamente após um desvio incondicional (TAC_JUMP),
 *       condicional (TAC_JUMPT, TAC_JUMPF) ou retorno (TAC_RETURN,
 *       TAC_RETURN_VOID) — pois o código após um desvio pode ser o início
 *       de um bloco alternativo.
 *
 *   Percorra t de func_begin->next até func_end (exclusive).
 *   Ao detectar um líder:
 *     • Feche o bloco anterior: atribua current->last = prev.
 *     • Crie um novo bloco: bb_new(cfg->n_blocks, t).
 *     • Adicione ao array cfg->blocks (redimensione se necessário).
 *   Ao terminar, feche o último bloco aberto: current->last = prev.
 *
 * ── FASE 2: Adicionar arestas (succ / pred) ──────────────────────────────
 *
 *   Para cada bloco b cujo last é t:
 *
 *   t = TAC_JUMP L
 *       → único sucessor: bloco que começa com TAC_LABEL L
 *
 *   t = TAC_JUMPT L  ou  TAC_JUMPF L
 *       → dois sucessores:
 *           • bloco que começa com TAC_LABEL L   (desvio tomado)
 *           • cfg->blocks[i+1]                   (queda — desvio não tomado)
 *
 *   t = TAC_RETURN  ou  TAC_RETURN_VOID
 *       → sem sucessores (saída da função)
 *
 *   qualquer outro
 *       → único sucessor: cfg->blocks[i+1]       (queda)
 *
 *   Use cfg_find_by_label() para localizar o bloco-alvo pelo nome do rótulo.
 *   Use bb_add_succ() para registrar cada aresta (atualiza succ e pred).
 *
 * DICA: cfg->blocks[i+1] é o bloco de "queda" de cfg->blocks[i] quando
 *       i+1 < cfg->n_blocks.
 * ----------------------------------------------------------------------- */
cfg_t *cfg_build(tac_instr_t *func_begin, tac_instr_t *func_end)
{
    (void)func_begin;
    (void)func_end;
    /* TODO-OPT-A: implemente as duas fases descritas acima.
     * O stub retorna um CFG vazio para não travar o compilador. */
    return cfg_new();
}

/* -----------------------------------------------------------------------
 * TODO-OPT-B: bb_const_fold
 * -----------------------------------------------------------------------
 *
 * Dobragem de constantes (constant folding) dentro de um bloco básico.
 *
 * Para cada instrução aritmética (TAC_ADD, TAC_SUB, TAC_MUL, TAC_DIV,
 * TAC_MOD) cujos DOIS operandos (arg1 e arg2) são literais inteiros:
 *
 *   1. Converta arg1 e arg2 para long com strtol().
 *   2. Calcule o resultado em tempo de compilação.
 *   3. Substitua a instrução por TAC_COPY:
 *        • free(t->arg1);  t->arg1 = strdup("<resultado>");
 *        • free(t->arg2);  t->arg2 = NULL;
 *        • t->op = TAC_COPY;
 *
 * Exemplo de transformação no TAC:
 *
 *   ANTES:   _t1  =  3  +  4          (TAC_ADD,  result="_t1", arg1="3", arg2="4")
 *   DEPOIS:  _t1  =  7                (TAC_COPY, result="_t1", arg1="7", arg2=NULL)
 *
 * Tome cuidado com divisão por zero: se arg2 == 0 em DIV ou MOD, não
 * dobre (mantenha a instrução original para que o erro ocorra em runtime).
 *
 * Use is_int_literal() para testar os operandos.
 * Retorne o número de dobramentos realizados.
 * ----------------------------------------------------------------------- */
int bb_const_fold(basic_block_t *bb)
{
    (void)bb;
    /* TODO-OPT-B */
    return 0;
}

/* -----------------------------------------------------------------------
 * TODO-OPT-C: bb_copy_prop
 * -----------------------------------------------------------------------
 *
 * Propagação de cópias (copy propagation) dentro de um bloco básico.
 *
 * Mantém uma tabela de cópias ativas: pares (dst, src) onde
 * "dst = src" foi gerado por uma instrução TAC_COPY mais cedo no bloco.
 *
 * Para cada instrução t (na ordem do bloco):
 *
 *   PASSO 1 — Substituir usos:
 *     Para cada par ativo (dst, src) na tabela:
 *       Se t->arg1 == dst, substitua: free(t->arg1); t->arg1 = strdup(src).
 *       Se t->arg2 == dst, substitua: free(t->arg2); t->arg2 = strdup(src).
 *
 *   PASSO 2 — Invalidar cópias afetadas pela definição de t:
 *     Se t define uma variável v (t->result != NULL):
 *       Remova da tabela todo par (d, s) onde d == v  OU  s == v
 *       (d foi redefinido / s foi modificado → a cópia não é mais válida).
 *
 *   PASSO 3 — Registrar nova cópia:
 *     Se t->op == TAC_COPY e t->result e t->arg1 são não-nulos:
 *       Adicione (t->result, t->arg1) à tabela.
 *
 * Exemplo:
 *
 *   _t1 = x            → cópia ativa: (_t1 → x)
 *   _t2 = _t1 + y      → arg1 substituído: _t2 = x + y   (+1 substituição)
 *   _t1 = 5            → invalida (_t1 → x)
 *   _t3 = _t1 + 1      → _t1 não está na tabela; sem substituição
 *
 * Retorne o número total de substituições (arg1 + arg2 combinados).
 * ----------------------------------------------------------------------- */
int bb_copy_prop(basic_block_t *bb)
{
    (void)bb;
    /* TODO-OPT-C */
    return 0;
}

/* -----------------------------------------------------------------------
 * optim_program — fornecida completa
 * ----------------------------------------------------------------------- */
void optim_program(tac_instr_t *prog)
{
    for (tac_instr_t *t = prog; t; t = t->next) {
        if (t->op != TAC_BEGINFUNC) continue;

        /* Localiza o TAC_ENDFUNC correspondente */
        tac_instr_t *end = t->next;
        while (end && end->op != TAC_ENDFUNC) end = end->next;
        if (!end) continue;

        cfg_t *cfg = cfg_build(t, end);
        if (!cfg) continue;

        int total = 0;
        for (int i = 0; i < cfg->n_blocks; i++) {
            total += bb_const_fold(cfg->blocks[i]);
            total += bb_copy_prop(cfg->blocks[i]);
        }
        if (total > 0)
            fprintf(stderr, "[OPTIM] %s: %d substituição(ões) aplicada(s).\n",
                    t->result ? t->result : "?", total);

        cfg_free(cfg);
    }
}

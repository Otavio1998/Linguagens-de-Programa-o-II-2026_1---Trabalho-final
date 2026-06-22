/*
 * asmgen.c — Gerador de Assembly x86-64 (COMPLETO — fornecido aos alunos)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Traduz a lista TAC produzida por codegen.c em assembly x86-64 AT&T.
 * Este arquivo é fornecido COMPLETO: os alunos não precisam modificá-lo.
 * A tarefa dos alunos é completar codegen.c (TODOs E3-A a E3-D).
 *
 * Uso:
 *   ./compilador < programa.lc > programa.s
 *   gcc programa.s -o programa -no-pie
 *   ./programa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asmgen.h"

/* Registradores para passagem de argumentos (ABI System V x86-64) */
static const char *arg_regs[] = {
    "%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"
};
static const int n_arg_regs = 6;

/* Mapeamento de operador relacional → instrução setcc */
static const char *relop_setcc(tac_op_t op)
{
    switch (op) {
        case TAC_LT: return "setl";
        case TAC_GT: return "setg";
        case TAC_LE: return "setle";
        case TAC_GE: return "setge";
        case TAC_EQ: return "sete";
        case TAC_NE: return "setne";
        default:     return "sete";
    }
}

/* -----------------------------------------------------------------------
 * asmgen_new
 * ----------------------------------------------------------------------- */
asmgen_ctx_t *asmgen_new(FILE *out, symtab_t *symtab)
{
    asmgen_ctx_t *ctx = calloc(1, sizeof(asmgen_ctx_t));
    if (!ctx) return NULL;
    ctx->out      = out ? out : stdout;
    ctx->symtab   = symtab;
    ctx->var_capacity = 64;
    ctx->var_names   = calloc(ctx->var_capacity, sizeof(char *));
    ctx->var_offsets = calloc(ctx->var_capacity, sizeof(int));
    return ctx;
}

/* -----------------------------------------------------------------------
 * asmgen_free
 * ----------------------------------------------------------------------- */
void asmgen_free(asmgen_ctx_t *ctx)
{
    if (!ctx) return;
    for (int i = 0; i < ctx->var_count; i++)
        free(ctx->var_names[i]);
    free(ctx->var_names);
    free(ctx->var_offsets);
    free(ctx);
}

/* -----------------------------------------------------------------------
 * asmgen_var_register / asmgen_var_offset
 * ----------------------------------------------------------------------- */
void asmgen_var_register(asmgen_ctx_t *ctx, const char *name, int offset)
{
    for (int i = 0; i < ctx->var_count; i++)
        if (strcmp(ctx->var_names[i], name) == 0) {
            ctx->var_offsets[i] = offset;
            return;
        }
    if (ctx->var_count >= ctx->var_capacity) {
        ctx->var_capacity *= 2;
        ctx->var_names   = realloc(ctx->var_names,   ctx->var_capacity * sizeof(char *));
        ctx->var_offsets = realloc(ctx->var_offsets, ctx->var_capacity * sizeof(int));
    }
    ctx->var_names[ctx->var_count]   = strdup(name);
    ctx->var_offsets[ctx->var_count] = offset;
    ctx->var_count++;
}

int asmgen_var_offset(asmgen_ctx_t *ctx, const char *name)
{
    for (int i = 0; i < ctx->var_count; i++)
        if (strcmp(ctx->var_names[i], name) == 0)
            return ctx->var_offsets[i];
    fprintf(stderr, "[ASMGEN] AVISO: '%s' não encontrado no frame.\n", name);
    return 0;
}

/* -----------------------------------------------------------------------
 * asmgen_operand
 * Retorna string alocada dinamicamente; chamador deve liberar com free().
 * ----------------------------------------------------------------------- */
char *asmgen_operand(asmgen_ctx_t *ctx, const char *name)
{
    if (!name) return strdup("$0");

    /* Literal inteiro */
    if (isdigit((unsigned char)name[0]) ||
        (name[0] == '-' && isdigit((unsigned char)name[1]))) {
        char *buf = malloc(strlen(name) + 2);
        sprintf(buf, "$%s", name);
        return buf;
    }

    /* Variável global */
    sym_entry_t *e = symtab_lookup(ctx->symtab, name);
    if (e && e->scope == SYM_SCOPE_GLOBAL) {
        char *buf = malloc(strlen(name) + 8);
        sprintf(buf, "%s(%%rip)", name);
        return buf;
    }

    /* Temporário ou variável local: offset no frame */
    int off = asmgen_var_offset(ctx, name);
    char *buf = malloc(32);
    sprintf(buf, "%d(%%rbp)", off);
    return buf;
}

/* -----------------------------------------------------------------------
 * asmgen_call — emite código para chamada de função
 * params[0..nparams-1] são os argumentos em ordem de avaliação.
 * ----------------------------------------------------------------------- */
static void asmgen_call(asmgen_ctx_t *ctx, const tac_instr_t *call_instr,
                        const char **params, int nparams)
{
    FILE *out = ctx->out;

    /* Carrega argumentos nos registradores da ABI */
    for (int i = 0; i < nparams && i < n_arg_regs; i++) {
        char *src = asmgen_operand(ctx, params[i]);
        fprintf(out, "    movq    %s, %s\n", src, arg_regs[i]);
        free(src);
    }

    /* Argumentos excedentes na pilha (em ordem inversa) */
    int extra = nparams > n_arg_regs ? nparams - n_arg_regs : 0;
    for (int i = nparams - 1; i >= n_arg_regs; i--) {
        char *src = asmgen_operand(ctx, params[i]);
        fprintf(out, "    pushq   %s\n", src);
        free(src);
    }
    /* Alinha stack a 16 bytes se número de args extras for ímpar */
    if (extra % 2 != 0)
        fprintf(out, "    subq    $8, %%rsp\n");

    fprintf(out, "    call    %s\n", call_instr->arg1);

    /* Remove args extras da pilha */
    if (extra > 0) {
        int cleanup = extra + (extra % 2 != 0 ? 1 : 0);
        fprintf(out, "    addq    $%d, %%rsp\n", cleanup * 8);
    }

    /* Recupera valor de retorno de %rax */
    if (call_instr->result) {
        char *dst = asmgen_operand(ctx, call_instr->result);
        fprintf(out, "    movq    %%rax, %s\n", dst);
        free(dst);
    }
}

/* -----------------------------------------------------------------------
 * asmgen_instr — traduz uma instrução TAC individual
 * (TAC_PARAM e TAC_CALL são tratados em asmgen_function)
 * ----------------------------------------------------------------------- */
void asmgen_instr(asmgen_ctx_t *ctx, const tac_instr_t *instr)
{
    FILE *out = ctx->out;
    if (!instr) return;

    switch (instr->op) {

        case TAC_DECL_LOCAL:
            break;

        case TAC_LABEL:
            fprintf(out, "%s:\n", instr->result);
            break;

        case TAC_COPY: {
            char *src = asmgen_operand(ctx, instr->arg1);
            char *dst = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", src);
            fprintf(out, "    movq    %%rax, %s\n", dst);
            free(src); free(dst);
            break;
        }

        case TAC_NEG: {
            char *src = asmgen_operand(ctx, instr->arg1);
            char *dst = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", src);
            fprintf(out, "    negq    %%rax\n");
            fprintf(out, "    movq    %%rax, %s\n", dst);
            free(src); free(dst);
            break;
        }

        case TAC_ADD: {
            char *a = asmgen_operand(ctx, instr->arg1);
            char *b = asmgen_operand(ctx, instr->arg2);
            char *d = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", a);
            fprintf(out, "    addq    %s, %%rax\n", b);
            fprintf(out, "    movq    %%rax, %s\n", d);
            free(a); free(b); free(d);
            break;
        }

        case TAC_SUB: {
            char *a = asmgen_operand(ctx, instr->arg1);
            char *b = asmgen_operand(ctx, instr->arg2);
            char *d = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", a);
            fprintf(out, "    subq    %s, %%rax\n", b);
            fprintf(out, "    movq    %%rax, %s\n", d);
            free(a); free(b); free(d);
            break;
        }

        case TAC_MUL: {
            char *a = asmgen_operand(ctx, instr->arg1);
            char *b = asmgen_operand(ctx, instr->arg2);
            char *d = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", a);
            fprintf(out, "    movq    %s, %%rcx\n", b);
            fprintf(out, "    imulq   %%rcx, %%rax\n");
            fprintf(out, "    movq    %%rax, %s\n", d);
            free(a); free(b); free(d);
            break;
        }

        case TAC_DIV: {
            char *a = asmgen_operand(ctx, instr->arg1);
            char *b = asmgen_operand(ctx, instr->arg2);
            char *d = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", a);
            fprintf(out, "    movq    %s, %%rcx\n", b);
            fprintf(out, "    cqto\n");
            fprintf(out, "    idivq   %%rcx\n");
            fprintf(out, "    movq    %%rax, %s\n", d);
            free(a); free(b); free(d);
            break;
        }

        case TAC_MOD: {
            char *a = asmgen_operand(ctx, instr->arg1);
            char *b = asmgen_operand(ctx, instr->arg2);
            char *d = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", a);
            fprintf(out, "    movq    %s, %%rcx\n", b);
            fprintf(out, "    cqto\n");
            fprintf(out, "    idivq   %%rcx\n");
            fprintf(out, "    movq    %%rdx, %s\n", d);
            free(a); free(b); free(d);
            break;
        }

        case TAC_LT: case TAC_GT: case TAC_LE:
        case TAC_GE: case TAC_EQ: case TAC_NE: {
            char *a = asmgen_operand(ctx, instr->arg1);
            char *b = asmgen_operand(ctx, instr->arg2);
            char *d = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", a);
            fprintf(out, "    cmpq    %s, %%rax\n", b);
            fprintf(out, "    %-8s%%al\n", relop_setcc(instr->op));
            fprintf(out, "    movzbq  %%al, %%rax\n");
            fprintf(out, "    movq    %%rax, %s\n", d);
            free(a); free(b); free(d);
            break;
        }

        case TAC_NOT: {
            char *src = asmgen_operand(ctx, instr->arg1);
            char *dst = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", src);
            fprintf(out, "    testq   %%rax, %%rax\n");
            fprintf(out, "    sete    %%al\n");
            fprintf(out, "    movzbq  %%al, %%rax\n");
            fprintf(out, "    movq    %%rax, %s\n", dst);
            free(src); free(dst);
            break;
        }

        case TAC_JUMP:
            fprintf(out, "    jmp     %s\n", instr->result);
            break;

        case TAC_JUMPF: {
            char *cond = asmgen_operand(ctx, instr->arg1);
            fprintf(out, "    cmpq    $0, %s\n", cond);
            fprintf(out, "    je      %s\n", instr->result);
            free(cond);
            break;
        }

        case TAC_JUMPT: {
            char *cond = asmgen_operand(ctx, instr->arg1);
            fprintf(out, "    cmpq    $0, %s\n", cond);
            fprintf(out, "    jne     %s\n", instr->result);
            free(cond);
            break;
        }

        case TAC_LOAD: {
            char *base = asmgen_operand(ctx, instr->arg1);
            char *idx  = asmgen_operand(ctx, instr->arg2);
            char *dst  = asmgen_operand(ctx, instr->result);
            fprintf(out, "    movq    %s, %%rax\n", idx);
            fprintf(out, "    leaq    %s, %%rcx\n", base);
            fprintf(out, "    movq    (%%rcx,%%rax,8), %%rax\n");
            fprintf(out, "    movq    %%rax, %s\n", dst);
            free(base); free(idx); free(dst);
            break;
        }

        case TAC_STORE: {
            char *base = asmgen_operand(ctx, instr->result);
            char *idx  = asmgen_operand(ctx, instr->arg1);
            char *val  = asmgen_operand(ctx, instr->arg2);
            fprintf(out, "    movq    %s, %%rax\n", val);
            fprintf(out, "    movq    %s, %%rcx\n", idx);
            fprintf(out, "    leaq    %s, %%rdx\n", base);
            fprintf(out, "    movq    %%rax, (%%rdx,%%rcx,8)\n");
            free(base); free(idx); free(val);
            break;
        }

        case TAC_PARAM:
        case TAC_CALL:
            /* Tratados com buffer de parâmetros em asmgen_function() */
            break;

        case TAC_RETURN: {
            char *val = asmgen_operand(ctx, instr->arg1);
            fprintf(out, "    movq    %s, %%rax\n", val);
            fprintf(out, "    movq    %%rbp, %%rsp\n");
            fprintf(out, "    popq    %%rbp\n");
            fprintf(out, "    ret\n");
            free(val);
            break;
        }

        case TAC_RETURN_VOID:
            fprintf(out, "    movq    %%rbp, %%rsp\n");
            fprintf(out, "    popq    %%rbp\n");
            fprintf(out, "    ret\n");
            break;

        case TAC_PRINT: {
            char *val = asmgen_operand(ctx, instr->arg1);
            fprintf(out, "    movq    %s, %%rsi\n", val);
            fprintf(out, "    leaq    _fmt_int(%%rip), %%rdi\n");
            fprintf(out, "    xorq    %%rax, %%rax\n");
            fprintf(out, "    call    printf\n");
            free(val);
            break;
        }

        case TAC_READ: {
            char *dst = asmgen_operand(ctx, instr->result);
            fprintf(out, "    leaq    %s, %%rsi\n", dst);
            fprintf(out, "    leaq    _fmt_read(%%rip), %%rdi\n");
            fprintf(out, "    xorq    %%rax, %%rax\n");
            fprintf(out, "    call    scanf\n");
            free(dst);
            break;
        }

        case TAC_BEGINFUNC:
        case TAC_ENDFUNC:
        case TAC_DECL_GLOBAL:
        case TAC_NOP:
            break;

        default:
            fprintf(out, "    # TAC não traduzido: op=%d\n", instr->op);
            break;
    }
}

/* -----------------------------------------------------------------------
 * asmgen_function — traduz uma função completa (beginFunc...endFunc)
 * ----------------------------------------------------------------------- */
void asmgen_function(asmgen_ctx_t *ctx, const tac_instr_t *begin)
{
    FILE *out = ctx->out;
    const char *fname = begin->result;

    /* Reinicia o mapeamento de variáveis do frame anterior */
    for (int i = 0; i < ctx->var_count; i++) free(ctx->var_names[i]);
    ctx->var_count  = 0;
    ctx->frame_size = 0;
    ctx->temp_count = 0;

    /* Primeira passagem: dimensiona o frame (locais + temporários) */
    int frame = 0;
    for (const tac_instr_t *t = begin; t && t->op != TAC_ENDFUNC; t = t->next) {
        if (t->op == TAC_DECL_LOCAL && t->result && t->arg1) {
            int off = -(atoi(t->arg1) + 8);
            asmgen_var_register(ctx, t->result, off);
            if (-off > frame) frame = -off;
        }
        if (t->result && t->result[0] == '_' && t->result[1] == 't') {
            int found = 0;
            for (int i = 0; i < ctx->var_count; i++)
                if (strcmp(ctx->var_names[i], t->result) == 0) { found = 1; break; }
            if (!found) {
                frame += 8;
                asmgen_var_register(ctx, t->result, -frame);
            }
        }
    }
    if (frame % 16 != 0) frame += (16 - frame % 16);
    ctx->frame_size = frame;

    /* Emite prólogo */
    fprintf(out, "%s:\n", fname);
    fprintf(out, "    pushq   %%rbp\n");
    fprintf(out, "    movq    %%rsp, %%rbp\n");
    if (frame > 0)
        fprintf(out, "    subq    $%d, %%rsp\n", frame);
    fprintf(out, "\n");

    /* Salva parâmetros dos registradores no frame */
    int param_idx = 0;
    for (const tac_instr_t *t = begin->next; t && t->op != TAC_ENDFUNC; t = t->next) {
        if (t->op == TAC_DECL_LOCAL && param_idx < n_arg_regs) {
            sym_entry_t *e = symtab_lookup(ctx->symtab, t->result);
            if (e && e->scope == SYM_SCOPE_LOCAL && e->offset < 0) {
                int off = e->offset;
                fprintf(out, "    movq    %s, %d(%%rbp)\n", arg_regs[param_idx++], off);
            }
        }
    }

    /* Segunda passagem: gera código; coleta parâmetros antes de cada CALL */
    int         param_cap = 16;
    const char **param_buf = calloc(param_cap, sizeof(const char *));
    int         param_count = 0;

    for (const tac_instr_t *t = begin->next; t && t->op != TAC_ENDFUNC; t = t->next) {
        if (t->op == TAC_PARAM) {
            if (param_count >= param_cap) {
                param_cap *= 2;
                param_buf = realloc(param_buf, param_cap * sizeof(const char *));
            }
            param_buf[param_count++] = t->arg1;
        } else if (t->op == TAC_CALL) {
            asmgen_call(ctx, t, param_buf, param_count);
            param_count = 0;
        } else {
            asmgen_instr(ctx, t);
        }
    }
    free(param_buf);

    fprintf(out, "\n");
}

/* -----------------------------------------------------------------------
 * asmgen_program — ponto de entrada
 * ----------------------------------------------------------------------- */
void asmgen_program(asmgen_ctx_t *ctx, const tac_instr_t *tac_list)
{
    FILE *out = ctx->out;

    fprintf(out, "    .text\n");
    fprintf(out, "    .globl main\n\n");

    fprintf(out, "    .section .rodata\n");
    fprintf(out, "_fmt_int:   .string \"%%ld\\n\"\n");
    fprintf(out, "_fmt_float: .string \"%%g\\n\"\n");
    fprintf(out, "_fmt_str:   .string \"%%s\\n\"\n");
    fprintf(out, "_fmt_read:  .string \"%%ld\"\n\n");
    fprintf(out, "    .text\n\n");

    const tac_instr_t *t = tac_list;
    while (t) {
        if (t->op == TAC_BEGINFUNC) {
            asmgen_function(ctx, t);
            while (t && t->op != TAC_ENDFUNC) t = t->next;
        }
        if (t) t = t->next;
    }

    fprintf(out, "\n    .bss\n");
    t = tac_list;
    while (t) {
        if (t->op == TAC_DECL_GLOBAL && t->result && t->arg1)
            fprintf(out, "    .comm %s, %s, 8\n", t->result, t->arg1);
        t = t->next;
    }
}

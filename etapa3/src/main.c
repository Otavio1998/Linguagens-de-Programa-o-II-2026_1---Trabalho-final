/*
 * main.c — Ponto de entrada do compilador LC- (Etapa 3 — Final)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Pipeline completo:
 *   programa LC−  →  AST  →  TAC  →  assembly x86-64 (stdout)
 *
 * USO:
 *   ./compilador < programa.lc > programa.s   # gera assembly
 *   ./compilador -tac < programa.lc           # inspeciona TAC (depuração)
 *   ./compilador -O   < programa.lc > a.s     # otimiza antes de gerar assembly
 *   ./compilador -O -tac < programa.lc        # inspeciona TAC otimizado
 *   ./compilador -cfg < programa.lc           # imprime CFG de cada função (depuração)
 *   gcc programa.s -o programa -no-pie
 *   ./programa
 *
 * CÓDIGO DE SAÍDA:
 *   0 — sucesso
 *   1 — erro sintático/léxico
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "codegen.h"
#include "asmgen.h"
#include "optim.h"

extern ast_node_t *ast_root;
symtab_t *global_symtab = NULL;
extern int yyparse(void);

int main(int argc, char *argv[])
{
    int print_tac = 0, optimize = 0, print_cfg = 0;
    for (int i = 1; i < argc; i++) {
        if      (strcmp(argv[i], "-tac") == 0) print_tac  = 1;
        else if (strcmp(argv[i], "-O")   == 0) optimize   = 1;
        else if (strcmp(argv[i], "-cfg") == 0) print_cfg  = 1;
    }

    global_symtab = symtab_new();
    if (!global_symtab) {
        fprintf(stderr, "ERRO FATAL: não foi possível alocar a tabela de símbolos.\n");
        return 1;
    }

    int parse_result = yyparse();
    if (parse_result != 0) {
        fprintf(stderr, "[COMPILADOR] Análise FALHOU (código %d).\n", parse_result);
        symtab_free(global_symtab);
        return 1;
    }

    /* Geração de código TAC */
    codegen_ctx_t *cg = codegen_new(global_symtab);
    codegen_program(cg, ast_root);

    /* Otimização opcional (Apêndice A): ativa com -O */
    if (optimize) optim_program(cg->code);

    /* Depuração do CFG (Apêndice A): ativa com -cfg */
    if (print_cfg) {
        for (tac_instr_t *t = cg->code; t; t = t->next) {
            if (t->op != TAC_BEGINFUNC) continue;
            tac_instr_t *end = t->next;
            while (end && end->op != TAC_ENDFUNC) end = end->next;
            if (!end) continue;
            fprintf(stderr, "=== CFG de '%s' ===\n",
                    t->result ? t->result : "?");
            cfg_t *cfg = cfg_build(t, end);
            if (cfg) { cfg_print(cfg, stderr); cfg_free(cfg); }
        }
    }

    if (print_tac) {
        /* Modo de depuração: imprime TAC legível em vez de assembly */
        tac_print(cg->code, stdout);
    } else {
        /* Modo normal: gera assembly x86-64 para stdout */
        asmgen_ctx_t *ag = asmgen_new(stdout, global_symtab);
        asmgen_program(ag, cg->code);
        asmgen_free(ag);
    }

    tac_free(cg->code);
    cg->code = NULL;
    codegen_free(cg);

    ast_free(ast_root);
    symtab_free(global_symtab);
    return 0;
}

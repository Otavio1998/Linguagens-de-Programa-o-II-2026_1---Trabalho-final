/*
 * main.c — Ponto de entrada do compilador LARA (Etapa 2)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Etapa 2: após a análise sintática, invoca o gerador de código TAC
 * e imprime a lista de instruções TAC produzida na saída padrão.
 *
 * USO:
 *   ./etapa2 < programa.lc
 *
 * CÓDIGO DE SAÍDA:
 *   0 — análise e geração bem-sucedidas
 *   1 — erro sintático ou léxico
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symtab.h"
#include "codegen.h"

/* Raiz da AST — preenchida por parser.y durante a análise */
extern ast_node_t *ast_root;

/* Tabela de símbolos global — usada pelo scanner e pelo parser */
symtab_t *global_symtab = NULL;

/* Função do parser gerada pelo bison */
extern int yyparse(void);

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;

    /* Inicializa a tabela de símbolos global */
    global_symtab = symtab_new();
    if (!global_symtab) {
        fprintf(stderr, "ERRO FATAL: não foi possível alocar a tabela de símbolos.\n");
        return 1;
    }

    /* Executa a análise léxica + sintática + construção da AST */
    int parse_result = yyparse();
    if (parse_result != 0) {
        fprintf(stderr, "[ETAPA 2] Análise FALHOU (código %d).\n", parse_result);
        symtab_free(global_symtab);
        return 1;
    }

    fprintf(stderr, "[ETAPA 2] Análise CONCLUÍDA com SUCESSO.\n");

    /* Geração de código TAC */
    codegen_ctx_t *cg = codegen_new(global_symtab);
    codegen_program(cg, ast_root);
    tac_print(cg->code, stdout);
    tac_free(cg->code);
    cg->code = NULL;
    codegen_free(cg);

    ast_free(ast_root);
    symtab_free(global_symtab);
    return 0;
}

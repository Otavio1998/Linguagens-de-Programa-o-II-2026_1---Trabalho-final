/*
 * main.c — Ponto de entrada do compilador LARA (Etapa 1)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este arquivo orquestra a Etapa 1 do compilador:
 *   1. Inicializa a tabela de símbolos global
 *   2. Chama o parser (yyparse) que, por sua vez, invoca o scanner
 *   3. Verifica se a análise foi bem-sucedida
 *   4. Imprime a AST construída
 *   5. Chama as funções de percorrimento (ast_walk.c)
 *   6. Imprime a tabela de símbolos
 *   7. Libera memória e sai
 *
 * USO:
 *   ./etapa1 < programa.lc        — lê da entrada padrão
 *   ./etapa1 programa.lc          — (não implementado aqui; use redireção)
 *
 * CÓDIGO DE SAÍDA:
 *   0 — análise bem-sucedida
 *   1 — erro sintático ou léxico
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symtab.h"

/* ----------------------------------------------------------------------- */
/* Declarações de variáveis e funções definidas em outros módulos           */
/* ----------------------------------------------------------------------- */

/* Raiz da AST — preenchida por parser.y durante a análise */
extern ast_node_t *ast_root;

/* Tabela de símbolos global — usada pelo scanner e pelo parser */
symtab_t *global_symtab = NULL;

/* Função do parser gerada pelo bison */
extern int yyparse(void);

/* Função de percorrimento da AST — definida em ast_walk.c */
extern void main_walk(const ast_node_t *root);

/* ----------------------------------------------------------------------- */
/* main                                                                      */
/* ----------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    (void)argc;  /* silencia warning de argc não usado */
    (void)argv;

    /* 1. Inicializa a tabela de símbolos global */
    global_symtab = symtab_new();
    if (global_symtab == NULL) {
        fprintf(stderr, "ERRO FATAL: não foi possível alocar a tabela de símbolos.\n");
        return 1;
    }

    /* 2. Executa a análise léxica + sintática + construção da AST
     *    yyparse() retorna:
     *      0 — análise bem-sucedida
     *      1 — erro sintático
     *      2 — erro de memória (em bison)
     */
    int parse_result = yyparse();

    /* 3. Verifica resultado da análise */
    if (parse_result != 0) {
        fprintf(stderr, "[ETAPA 1] Análise FALHOU (código %d).\n", parse_result);
        symtab_free(global_symtab);
        return 1;
    }

    fprintf(stderr, "[ETAPA 1] Análise CONCLUÍDA com SUCESSO.\n");

    /* 4. Imprime a AST produzida */
    printf("=== Árvore de Sintaxe Abstrata (AST) ===\n");
    ast_print(ast_root, 0, stdout);
    printf("=========================================\n\n");

    /* 5. Percorre a AST e exibe estatísticas */
    main_walk(ast_root);

    /* 6. Imprime a tabela de símbolos */
    symtab_print(global_symtab, stdout);

    /* 7. Libera memória */
    ast_free(ast_root);
    symtab_free(global_symtab);

    return 0;
}

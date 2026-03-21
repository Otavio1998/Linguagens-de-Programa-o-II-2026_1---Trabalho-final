/*
 * ast_walk.c — Percorrimento da AST: esboço para completar
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este arquivo contém um exemplo de função que percorre recursivamente
 * a AST para coletar estatísticas. Ele está INTENCIONALMENTE INCOMPLETO:
 * a função ast_count_nodes() compila e executa, mas não produz resultados
 * corretos ainda. O procedimento ast_count_leaves() está totalmente
 * esqueleto (retorna sempre 0).
 *
 * =====================================================================
 * TAREFA DOS ALUNOS:
 *
 * (E) Complete ast_count_nodes() para que ela retorne o número TOTAL
 *     de nós na AST, incluindo todos os descendentes via 'next'.
 *     A versão atual não percorre o encadeamento via 'next'.
 *
 * (F) Implemente ast_count_leaves() do zero. Um nó é "folha" quando
 *     todos os seus filhos são NULL E next também é NULL.
 *     Dica: o tipo do nó pode ajudar (AST_SYMBOL, AST_LIT_*), mas
 *     a definição estrutural de "folha" é mais robusta.
 *
 * (G) Implemente ast_max_depth() — retorna a profundidade máxima
 *     da árvore (comprimento do caminho mais longo da raiz a uma folha).
 *     A raiz tem profundidade 0.
 *
 * A função main_walk() ao final do arquivo demonstra como chamar
 * essas funções após a análise sintática.
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/* -----------------------------------------------------------------------
 * (E) ast_count_nodes — conta o número total de nós da AST
 *
 * VERSÃO ATUAL: percorre apenas os filhos (children[]), ignorando
 * o encadeamento via 'next'. Por isso, em programas com múltiplos
 * comandos ou declarações, a contagem ficará incorreta.
 *
 * TODO-E: corrija a função para também contar os nós encadeados via
 * 'next'. Dica: adicione a chamada recursiva correspondente.
 * ----------------------------------------------------------------------- */
int ast_count_nodes(const ast_node_t *node)
{
    if (node == NULL)
        return 0;

    int count = 1;  /* conta este nó */

    /* Percorre todos os filhos */
    for (int i = 0; i < AST_MAX_CHILDREN; i++) {
        if(node->children[i] != NULL) {
            count += ast_count_nodes(node->children[i]);
        }
    }

    /* TODO-E: adicione aqui a contagem recursiva via 'next' */
    if(node->next != NULL){
        count += ast_count_nodes(node->next);
    }

    return count;
}

/* -----------------------------------------------------------------------
 * (F) ast_count_leaves — conta o número de folhas da AST
 *
 * VERSÃO ATUAL: esqueleto — sempre retorna 0.
 *
 * TODO-F: implemente esta função. Um nó é folha quando todos os seus
 * filhos são NULL E next é NULL. Percorra recursivamente a árvore.
 * ----------------------------------------------------------------------- */
int ast_count_leaves(const ast_node_t *node)
{
    /* TODO-F: implementar */
    if (node == NULL) return 0;

    int is_leaf = 1;
    for(int i=0; i <  AST_MAX_CHILDREN; i++){
        if (node->children[i] != NULL){
            is_leaf = 0;
            break;
        }
    }
    if (node->next != NULL) {
        is_leaf = 0;
    }

    int count = is_leaf ? 1 : 0;

    for(int i=0; i< AST_MAX_CHILDREN; i++){
        count += ast_count_leaves(node->children[i]);
    }
    count += ast_count_leaves(node->next);

    return count;
}

/* -----------------------------------------------------------------------
 * (G) ast_max_depth — retorna a profundidade máxima da AST
 *
 * A raiz tem profundidade 0. Cada nível de filho adiciona 1.
 * O encadeamento 'next' NÃO aumenta a profundidade (é mesmo nível).
 *
 * VERSÃO ATUAL: esqueleto — sempre retorna 0.
 *
 * TODO-G: implemente esta função.
 * Dica: use a função auxiliar max(a, b) definida abaixo.
 * ----------------------------------------------------------------------- */
static int max(int a, int b) { return (a > b) ? a : b; }

int ast_max_depth(const ast_node_t *node)
{
    /* TODO-G: implementar */
    if(node == NULL){
        return 0;
    }

    int max_deph = 0;

    for(int i=0; i< AST_MAX_CHILDREN; i++){
        if(node->children[i] != NULL){
            max_deph = max(max_deph, 1 + ast_max_depth(node->children[i]));
        }
    }

    max_deph = max(max_deph, ast_max_depth(node->next));

    return max_deph;
}

/* -----------------------------------------------------------------------
 * main_walk — demonstra as funções acima após análise sintática
 *
 * Esta função deve ser chamada em main.c após a análise bem-sucedida.
 * ----------------------------------------------------------------------- */
void main_walk(const ast_node_t *root)
{
    if (root == NULL) {
        printf("[WALK] AST vazia — nada a percorrer.\n");
        return;
    }

    printf("\n=== Estatísticas da AST ===\n");
    printf("  Nós totais  : %d\n", ast_count_nodes(root));
    printf("  Folhas      : %d\n", ast_count_leaves(root));
    printf("  Profund. max: %d\n", ast_max_depth(root));
    printf("===========================\n\n");
}

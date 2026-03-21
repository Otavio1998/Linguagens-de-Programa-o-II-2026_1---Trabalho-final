/*
 * symtab.h — Interface da Tabela de Símbolos
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * A tabela de símbolos armazena os identificadores reconhecidos durante
 * a análise léxica e sintática. Na Etapa 1, ela é usada de forma simples:
 * cada identificador é inserido ao ser reconhecido pelo scanner, e os
 * nós folha AST_SYMBOL da AST apontam para a entrada correspondente.
 *
 * IMPLEMENTAÇÃO:
 *   Usamos uma tabela hash com encadeamento externo (listas ligadas
 *   para tratar colisões). O tamanho da tabela é fixo em SYMTAB_SIZE.
 *
 * EXTENSÕES FUTURAS (Etapas 2 e 3):
 *   - Campo 'nature' (escalar, array, função)
 *   - Campo 'datatype' (int, float, char, bool, void)
 *   - Campo 'offset' (deslocamento no registro de ativação)
 *   - Suporte a escopos aninhados via pilha de tabelas
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

/* Número de buckets da tabela hash.
 * Valor primo para melhor distribuição. */
#define SYMTAB_SIZE 509

/* -----------------------------------------------------------------------
 * Tipos de natureza do símbolo (usados a partir da Etapa 2)
 * Na Etapa 1, todos os símbolos têm natureza SYM_UNKNOWN.
 * ----------------------------------------------------------------------- */
typedef enum {
    SYM_UNKNOWN  = 0,  /* ainda não determinado */
    SYM_VAR      = 1,  /* variável escalar */
    SYM_ARRAY    = 2,  /* array */
    SYM_FUNCTION = 3   /* função */
} sym_nature_t;

/* -----------------------------------------------------------------------
 * Tipos de dado do símbolo (usados a partir da Etapa 2)
 * ----------------------------------------------------------------------- */
typedef enum {
    SYM_TYPE_UNKNOWN = 0,
    SYM_TYPE_INT     = 1,
    SYM_TYPE_FLOAT   = 2,
    SYM_TYPE_CHAR    = 3,
    SYM_TYPE_BOOL    = 4,
    SYM_TYPE_VOID    = 5,
    SYM_TYPE_STRING  = 6   /* apenas para literais — não é tipo de variável */
} sym_datatype_t;

/* -----------------------------------------------------------------------
 * Entrada da tabela de símbolos
 * ----------------------------------------------------------------------- */
typedef struct sym_entry {
    char           *lexeme;    /* string do identificador (duplicada) */
    int             lineno;    /* linha onde foi declarado/primeira ocorrência */
    sym_nature_t    nature;    /* natureza (Etapa 2+) */
    sym_datatype_t  datatype;  /* tipo de dado (Etapa 2+) */
    int             offset;    /* deslocamento no frame (Etapa 2+) */
    struct sym_entry *next;    /* próximo na lista de colisão */
} sym_entry_t;

/* -----------------------------------------------------------------------
 * Tabela de símbolos (estrutura principal)
 * ----------------------------------------------------------------------- */
typedef struct {
    sym_entry_t *buckets[SYMTAB_SIZE];
    int          count;     /* número total de entradas */
} symtab_t;

/* -----------------------------------------------------------------------
 * Interface pública
 * ----------------------------------------------------------------------- */

/*
 * symtab_new — aloca e inicializa uma nova tabela de símbolos vazia.
 * Retorna ponteiro para a tabela, ou NULL em caso de erro.
 */
symtab_t *symtab_new(void);

/*
 * symtab_insert — insere ou retorna a entrada de 'lexeme' na tabela.
 *
 * Se o lexema já existe, retorna a entrada existente (sem duplicar).
 * Se não existe, cria uma nova entrada com nature=SYM_UNKNOWN e
 * datatype=SYM_TYPE_UNKNOWN.
 *
 * Parâmetros:
 *   tab    : tabela de símbolos
 *   lexeme : string do identificador
 *   lineno : linha do programa-fonte
 *
 * Retorna: ponteiro para a entrada (nunca NULL se alocação bem-sucedida).
 */
sym_entry_t *symtab_insert(symtab_t *tab, const char *lexeme, int lineno);

/*
 * symtab_lookup — busca 'lexeme' na tabela.
 *
 * Retorna: ponteiro para a entrada, ou NULL se não encontrado.
 */
sym_entry_t *symtab_lookup(symtab_t *tab, const char *lexeme);

/*
 * symtab_print — imprime o conteúdo da tabela (para depuração).
 *
 * Parâmetros:
 *   tab : tabela de símbolos
 *   out : arquivo de saída (use stdout para imprimir na tela)
 */
void symtab_print(const symtab_t *tab, FILE *out);

/*
 * symtab_free — libera toda a memória da tabela e das entradas.
 */
void symtab_free(symtab_t *tab);

#endif /* SYMTAB_H */

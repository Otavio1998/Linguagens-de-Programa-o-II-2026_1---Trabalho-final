/*
 * tokens.h — Definição dos tokens da Linguagem LARA
 *
 * INF01083 — Linguagens de Programação II / Compiladores
 * Universidade Federal do Rio Grande do Sul — INF/UFRGS
 * Professor: Nicolas Maillard
 * Semestre: 2026/1
 *
 * A Linguagem LARA é um subconjunto de C com algumas variações sintáticas
 * introduzidas para fins didáticos. Seu compilador será desenvolvido
 * incrementalmente ao longo das 4 etapas do projeto.
 *
 * ATENÇÃO: este arquivo é gerado automaticamente pelo bison a partir
 * de parser.y (via %token). Ele é incluído pelo scanner (scanner.l) para
 * que ambos compartilhem os mesmos valores numéricos de token.
 * NÃO edite este arquivo manualmente.
 */

#ifndef TOKENS_H
#define TOKENS_H

/* Palavras reservadas */
#define TK_PR_INT       256
#define TK_PR_FLOAT     257
#define TK_PR_BOOL      258
#define TK_PR_CHAR      259
#define TK_PR_IF        260
#define TK_PR_ELSE      261
#define TK_PR_WHILE     262
#define TK_PR_FOR       263
#define TK_PR_RETURN    264
#define TK_PR_VOID      265
#define TK_PR_ARRAY     266   /* <-- variação: LARA usa 'array' em vez de [] na declaração */
#define TK_PR_OF        267   /* <-- variação: 'array N of tipo' em vez de 'tipo v[N]'  */
#define TK_PR_LET       268   /* <-- variação: 'let x := expr' em vez de 'tipo x = expr' */
#define TK_PR_FUN       269   /* <-- variação: 'fun tipo nome(params) { }' em vez de 'tipo nome(params) { }' */
#define TK_PR_DO        270
#define TK_PR_PRINT     271
#define TK_PR_READ      272

/* Identificadores e literais */
#define TK_ID           300
#define TK_LIT_INT      301
#define TK_LIT_FLOAT    302
#define TK_LIT_CHAR     303   /* caractere entre apóstrofes: 'a' */
#define TK_LIT_STRING   304   /* cadeia entre aspas: "texto" */
#define TK_LIT_TRUE     305   /* literal booleano verdadeiro */
#define TK_LIT_FALSE    306   /* literal booleano falso */

/* Operadores compostos (2+ caracteres) */
#define TK_OC_LE        320   /* <=  menor ou igual */
#define TK_OC_GE        321   /* >=  maior ou igual */
#define TK_OC_EQ        322   /* ==  igualdade */
#define TK_OC_NE        323   /* !=  diferença */
#define TK_OC_AND       324   /* &&  conjunção lógica */
#define TK_OC_OR        325   /* ||  disjunção lógica */
#define TK_OC_ARROW     326   /* ->  acesso a campo de struct */
#define TK_OC_ASSIGN    327   /* :=  atribuição LARA (variação: usa := em vez de =) */
#define TK_OC_PLUSEQ    328   /* +=  atribuição composta */
#define TK_OC_MINUSEQ   329   /* -=  atribuição composta */

/* Caracteres simples usados como tokens são retornados diretamente
 * pelo scanner com seu valor ASCII: '+', '-', '*', '/', '%', '<', '>',
 * '!', '=', '(', ')', '{', '}', '[', ']', ',', ';', ':', '.'
 * Não precisam de #define. */

/* Token especial: erro léxico */
#define TK_ERROR        400

#endif /* TOKENS_H */

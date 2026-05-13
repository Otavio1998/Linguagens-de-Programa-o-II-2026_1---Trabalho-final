/*
 * codegen.c — Gerador de Código TAC (ESQUELETO — Etapa 2)
 *
 * INF01083 — Linguagens de Programação II / Compiladores — 2026/1
 * UFRGS / INF — Prof. Nicolas Maillard
 *
 * Este arquivo contém a estrutura do gerador de código com as funções
 * auxiliares completas e os casos mais simples implementados como exemplo.
 * Os alunos devem completar os casos marcados com TODO.
 *
 * =====================================================================
 * TAREFAS DOS ALUNOS:
 *
 * TODO-E2-A: Em codegen_program(), complete o loop que percorre as
 *            declarações globais e calcula seus offsets na symtab.
 *
 * TODO-E2-B: Em codegen_expr(), complete os casos de AST_EXPR_BINARY
 *            para os operadores aritméticos (+, -, *, /, %).
 *
 * TODO-E2-C: Em codegen_expr(), adicione os casos para os operadores
 *            relacionais (<, >, <=, >=, ==, !=).
 *
 * TODO-E2-D: Em codegen_stmt(), complete o caso AST_ASSIGN para :=
 *            (atribuição simples — não compound assignment).
 * =====================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

/* -----------------------------------------------------------------------
 * Tamanho em bytes de cada tipo (para cálculo de offsets)
 * ----------------------------------------------------------------------- */
static int type_size(sym_datatype_t dt)
{
    switch (dt) {
        case SYM_TYPE_INT:   return 4;
        case SYM_TYPE_FLOAT: return 8;
        case SYM_TYPE_CHAR:  return 1;
        case SYM_TYPE_BOOL:  return 1;
        default:             return 4;
    }
}

/* -----------------------------------------------------------------------
 * Mapeia operador string → opcode TAC
 * ----------------------------------------------------------------------- */
static tac_op_t op_to_tac(const char *op)
{
    if (!op) return TAC_NOP;
    if (strcmp(op, "+")  == 0) return TAC_ADD;
    if (strcmp(op, "-")  == 0) return TAC_SUB;
    if (strcmp(op, "*")  == 0) return TAC_MUL;
    if (strcmp(op, "/")  == 0) return TAC_DIV;
    if (strcmp(op, "%")  == 0) return TAC_MOD;
    if (strcmp(op, "<")  == 0) return TAC_LT;
    if (strcmp(op, ">")  == 0) return TAC_GT;
    if (strcmp(op, "<=") == 0) return TAC_LE;
    if (strcmp(op, ">=") == 0) return TAC_GE;
    if (strcmp(op, "==") == 0) return TAC_EQ;
    if (strcmp(op, "!=") == 0) return TAC_NE;
    if (strcmp(op, "&&") == 0) return TAC_AND;
    if (strcmp(op, "||") == 0) return TAC_OR;
    return TAC_NOP;
}

/* -----------------------------------------------------------------------
 * codegen_new
 * ----------------------------------------------------------------------- */
codegen_ctx_t *codegen_new(symtab_t *symtab)
{
    codegen_ctx_t *ctx = calloc(1, sizeof(codegen_ctx_t));
    if (!ctx) return NULL;
    ctx->symtab        = symtab;
    ctx->code          = NULL;
    ctx->current_func  = NULL;
    ctx->local_offset  = 0;
    return ctx;
}

/* -----------------------------------------------------------------------
 * codegen_free
 * ----------------------------------------------------------------------- */
void codegen_free(codegen_ctx_t *ctx)
{
    if (!ctx) return;
    free(ctx->current_func);
    free(ctx);
}

/* -----------------------------------------------------------------------
 * codegen_emit — atalho para adicionar instrução ao contexto
 * ----------------------------------------------------------------------- */
void codegen_emit(codegen_ctx_t *ctx, tac_op_t op,
                  const char *result, const char *arg1, const char *arg2)
{
    tac_instr_t *i = tac_new(op, result, arg1, arg2);
    ctx->code = tac_append(ctx->code, i);
}

/* -----------------------------------------------------------------------
 * codegen_program — percorre a AST do programa completo
 * ----------------------------------------------------------------------- */
void codegen_program(codegen_ctx_t *ctx, ast_node_t *program)
{
    if (!program) return;

    /* O filho 0 de AST_PROGRAM é a lista de declarações de topo-nível */
    ast_node_t *decl = program->children[0];

    /*
     * TODO-E2-A: percorra a lista de declarações (via ->next) e para cada
     * declaração:
     *   - Se for AST_VAR_DECL global: atribua offset global, emita TAC_DECL_GLOBAL
     *   - Se for AST_ARRAY_DECL global: atribua offset global, emita TAC_DECL_GLOBAL
     *   - Se for AST_FUN_DECL: chame codegen_fun()
     *
     * Use symtab_lookup() para encontrar a entrada e setar seu offset.
     * Use uma variável local 'global_offset' iniciada em 0 e incremente
     * pelo tamanho do tipo a cada variável/array global.
     *
     * Exemplo de emissão para variável global 'x' com offset 0:
     *   codegen_emit(ctx, TAC_DECL_GLOBAL, "x", "4", NULL);
     *
     * Dica: o nome da variável está em decl->value.
     *       O tipo base está em decl->children[0]->value.
     */

    /* Código parcial fornecido como exemplo — processa apenas funções */
    int global_offset = 0;
    while (decl) {
        if (decl->type == AST_FUN_DECL) {
            codegen_fun(ctx, decl);
        }
        /* TODO-E2-A: adicione tratamento para AST_VAR_DECL e AST_ARRAY_DECL */
        else if(decl->type == AST_VAR_DECL) { 
            const char *var_name = decl->value;
            sym_entry_t *e = symtab_lookup(ctx->symtab, var_name);
            if(e){
                e->scope = SYM_SCOPE_GLOBAL;
                e->offset = global_offset;
                global_offset += type_size(e->datatype);
                char size_str[16];
                snprintf(size_str, sizeof(size_str), "%d", type_size(e->datatype));
                codegen_emit(ctx, TAC_DECL_GLOBAL, var_name, size_str, NULL);
            }
        }
            else if (decl->type == AST_ARRAY_DECL) {
                const char* arr_name = decl->value;
                sym_entry_t* e = symtab_lookup(ctx->symtab, arr_name);
                if (e) {
                    e->scope = SYM_SCOPE_GLOBAL;
                    e->offset = global_offset;
                    global_offset += type_size(e->datatype) * e->array_size;
                    char size_str[16];
                    snprintf(size_str, sizeof(size_str), "%d", type_size(e->datatype) * e->array_size);
                    codegen_emit(ctx, TAC_DECL_GLOBAL, arr_name, size_str, NULL);

                }
                
            }
        decl = decl->next;
    }
}

/* -----------------------------------------------------------------------
 * codegen_fun — gera código para uma função
 * ----------------------------------------------------------------------- */
void codegen_fun(codegen_ctx_t *ctx, ast_node_t *fun_decl)
{
    if (!fun_decl || fun_decl->type != AST_FUN_DECL) return;

    const char *fname = fun_decl->value;

    /* Atualiza contexto para a função atual */
    free(ctx->current_func);
    ctx->current_func = strdup(fname);
    ctx->local_offset = 0;

    /* Emite rótulo de início da função */
    codegen_emit(ctx, TAC_BEGINFUNC, fname, NULL, NULL);

    /* Processa parâmetros — são variáveis locais com offsets negativos
     * (convenção: parâmetros ficam acima do frame pointer) */
    ast_node_t *param = fun_decl->children[1];
    int param_offset = -4;  /* começa acima do frame pointer */
    while (param) {
        if (param->type == AST_PARAM && param->value) {
            sym_entry_t *e = symtab_lookup(ctx->symtab, param->value);
            if (e) {
                e->scope  = SYM_SCOPE_LOCAL;
                e->offset = param_offset;
                param_offset -= type_size(e->datatype);
            }
        }
        param = param->next;
    }

    /* Processa corpo da função */
    ast_node_t *body = fun_decl->children[2];
    if (body && body->type == AST_BLOCK) {
        ast_node_t *stmt = body->children[0];
        while (stmt) {
            codegen_stmt(ctx, stmt);
            stmt = stmt->next;
        }
    }

    /* Emite fim da função */
    codegen_emit(ctx, TAC_ENDFUNC, fname, NULL, NULL);
}

/* -----------------------------------------------------------------------
 * codegen_stmt — gera código para um comando
 * ----------------------------------------------------------------------- */
void codegen_stmt(codegen_ctx_t *ctx, ast_node_t *stmt)
{
    if (!stmt) return;

    switch (stmt->type) {

        /* --- Declaração de variável local: let x := expr --- */
        case AST_VAR_DECL: {
            const char *vname = stmt->value;
            sym_entry_t *e = symtab_lookup(ctx->symtab, vname);
            if (e) {
                e->scope  = SYM_SCOPE_LOCAL;
                e->offset = ctx->local_offset;
                ctx->local_offset += type_size(e->datatype);
                char offset_str[16];
                snprintf(offset_str, sizeof(offset_str), "%d", e->offset);
                codegen_emit(ctx, TAC_DECL_LOCAL, vname, offset_str, NULL);
            }
            /* Processa inicializador, se houver */
            if (stmt->children[1]) {
                char *val = codegen_expr(ctx, stmt->children[1]);
                codegen_emit(ctx, TAC_COPY, vname, val, NULL);
                free(val);
            }
            break;
        }

        /*
         * --- Atribuição ---
         *
         * TODO-E2-D: complete este caso para o operador ':='.
         * Você deve:
         *   1. Gerar código para a expressão do lado direito (stmt->children[1])
         *      usando codegen_expr() — ela retorna o nome do resultado.
         *   2. Obter o nome do lvalue (lado esquerdo) a partir de stmt->children[0].
         *      Para um AST_SYMBOL simples, o nome está em children[0]->value.
         *   3. Emitir um TAC_COPY do resultado para o lvalue.
         *   4. Liberar a string retornada por codegen_expr() com free().
         *
         * Exemplo:  x := a + b
         *   gera:   _t1 = a + b
         *           x = _t1
         *
         * Atenção: trate também o caso de lvalue indexado (AST_EXPR_INDEX)
         * com TAC_STORE — mas isso é bônus; foque primeiro no caso simples.
         */
        case AST_ASSIGN: {
            if (strcmp(stmt->value, ":=") == 0) {
                /* TODO-E2-D: implemente aqui */
                char *retval = codegen_expr(ctx, stmt->children[1]);
                if(stmt->children[0]->type == AST_EXPR_INDEX) {
                    char *idx = codegen_expr(ctx, stmt->children[0]->children[0]);
                    codegen_emit(ctx, TAC_STORE, stmt->children[0]->value, idx, retval);
                    free(idx);
                }
                else{
                    const char *lname = stmt->children[0]->value;
                    codegen_emit(ctx, TAC_COPY, lname, retval, NULL);
                }
                free(retval);
            } else if (strcmp(stmt->value, "+=") == 0) {
                /* compound assignment += */
                char *lname = stmt->children[0]->value;
                char *rval  = codegen_expr(ctx, stmt->children[1]);
                char *tmp   = tac_new_temp();
                codegen_emit(ctx, TAC_ADD, tmp, lname, rval);
                codegen_emit(ctx, TAC_COPY, lname, tmp, NULL);
                free(rval); free(tmp);
            } else if (strcmp(stmt->value, "-=") == 0) {
                char *lname = stmt->children[0]->value;
                char *rval  = codegen_expr(ctx, stmt->children[1]);
                char *tmp   = tac_new_temp();
                codegen_emit(ctx, TAC_SUB, tmp, lname, rval);
                codegen_emit(ctx, TAC_COPY, lname, tmp, NULL);
                free(rval); free(tmp);
            }
            break;
        }

        /* --- print --- */
        case AST_PRINT: {
            char *val = codegen_expr(ctx, stmt->children[0]);
            codegen_emit(ctx, TAC_PRINT, NULL, val, NULL);
            free(val);
            break;
        }

        /* --- read --- */
        case AST_READ: {
            const char *lname = stmt->children[0]->value;
            codegen_emit(ctx, TAC_READ, lname, NULL, NULL);
            break;
        }

        /* --- return --- */
        case AST_RETURN: {
            if (stmt->children[0]) {
                char *val = codegen_expr(ctx, stmt->children[0]);
                codegen_emit(ctx, TAC_RETURN, NULL, val, NULL);
                free(val);
            } else {
                codegen_emit(ctx, TAC_RETURN_VOID, NULL, NULL, NULL);
            }
            break;
        }

        /* --- chamada de função como comando --- */
        case AST_CALL: {
            /* Processa argumentos */
            ast_node_t *arg = stmt->children[0];
            int nargs = 0;
            while (arg) { nargs++; arg = arg->next; }
            arg = stmt->children[0];
            while (arg) {
                char *val = codegen_expr(ctx, arg);
                codegen_emit(ctx, TAC_PARAM, NULL, val, NULL);
                free(val);
                arg = arg->next;
            }
            char nargs_str[16];
            snprintf(nargs_str, sizeof(nargs_str), "%d", nargs);
            codegen_emit(ctx, TAC_CALL, NULL, stmt->value, nargs_str);
            break;
        }

        /* --- bloco aninhado --- */
        case AST_BLOCK: {
            ast_node_t *s = stmt->children[0];
            while (s) { codegen_stmt(ctx, s); s = s->next; }
            break;
        }

        /* if, while, for — implementados na Etapa 3 */
        case AST_IF:
        case AST_WHILE:
        case AST_FOR:
            fprintf(stderr, "[CODEGEN] Controle de fluxo: implementar na Etapa 3.\n");
            break;

        default:
            fprintf(stderr, "[CODEGEN] Comando desconhecido: tipo=%d\n", stmt->type);
            break;
    }
}

/* -----------------------------------------------------------------------
 * codegen_expr — gera código para uma expressão
 * Retorna o nome do temporário/variável com o resultado (alocar com strdup).
 * Chamador deve liberar com free().
 * ----------------------------------------------------------------------- */
char *codegen_expr(codegen_ctx_t *ctx, ast_node_t *expr)
{
    if (!expr) return strdup("_undef");

    switch (expr->type) {

        /* --- Identificador (variável) --- */
        case AST_SYMBOL:
            return strdup(expr->value);

        /* --- Literais --- */
        case AST_LIT_INT:
        case AST_LIT_FLOAT:
        case AST_LIT_CHAR:
            return strdup(expr->value);
        case AST_LIT_BOOL:
            return strdup(strcmp(expr->value, "true") == 0 ? "1" : "0");
        case AST_LIT_STRING:
            return strdup(expr->value);

        /* --- Operador unário --- */
        case AST_EXPR_UNARY: {
            char *val = codegen_expr(ctx, expr->children[0]);
            char *tmp = tac_new_temp();
            if (strcmp(expr->value, "-") == 0)
                codegen_emit(ctx, TAC_NEG, tmp, val, NULL);
            else if (strcmp(expr->value, "!") == 0)
                codegen_emit(ctx, TAC_NOT, tmp, val, NULL);
            free(val);
            return tmp;
        }

        /* --- Operador binário --- */
        case AST_EXPR_BINARY: {
            char *left  = codegen_expr(ctx, expr->children[0]);
            char *right = codegen_expr(ctx, expr->children[1]);
            char *tmp   = tac_new_temp();
            tac_op_t op = op_to_tac(expr->value);

            /*
             * TODO-E2-B: implemente a geração de TAC para operadores aritméticos.
             * A função op_to_tac() já converte o operador string para o opcode TAC.
             * Emita a instrução usando codegen_emit() com o opcode correto.
             *
             * TODO-E2-C: os operadores relacionais (<, >, <=, >=, ==, !=) funcionam
             * exatamente da mesma forma — op_to_tac() já os cobre. Verifique se o
             * caso genérico abaixo já é suficiente ou se precisa de tratamento especial.
             *
             * Por enquanto, o código abaixo emite TAC_NOP para qualquer operador
             * (placeholder). Substitua pela emissão correta.
             */
            if (op != TAC_NOP) {
                /* TODO-E2-B e TODO-E2-C: substitua a linha abaixo */
                codegen_emit(ctx, op, tmp, left, right);
                /* pela linha correta: */
                /* codegen_emit(ctx, op, tmp, left, right); */
            } else {
                fprintf(stderr, "[CODEGEN] Operador desconhecido: '%s'\n", expr->value);
                codegen_emit(ctx, TAC_NOP, tmp, left, right);
            }

            free(left);
            free(right);
            return tmp;
        }

        /* --- Indexação de array: v[i] --- */
        case AST_EXPR_INDEX: {
            char *idx = codegen_expr(ctx, expr->children[0]);
            char *tmp = tac_new_temp();
            codegen_emit(ctx, TAC_LOAD, tmp, expr->value, idx);
            free(idx);
            return tmp;
        }

        /* --- Chamada de função como expressão --- */
        case AST_EXPR_CALL: {
            ast_node_t *arg = expr->children[0];
            int nargs = 0;
            while (arg) { nargs++; arg = arg->next; }
            arg = expr->children[0];
            while (arg) {
                char *val = codegen_expr(ctx, arg);
                codegen_emit(ctx, TAC_PARAM, NULL, val, NULL);
                free(val);
                arg = arg->next;
            }
            char nargs_str[16];
            snprintf(nargs_str, sizeof(nargs_str), "%d", nargs);
            char *tmp = tac_new_temp();
            codegen_emit(ctx, TAC_CALL, tmp, expr->value, nargs_str);
            return tmp;
        }

        default:
            fprintf(stderr, "[CODEGEN] Expressão desconhecida: tipo=%d\n", expr->type);
            return strdup("_err");
    }
}

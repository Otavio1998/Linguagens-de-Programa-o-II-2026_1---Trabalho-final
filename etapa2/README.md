# Etapa 2 — Geração de Código de Três Endereços (TAC)

**Disciplina:** INF01083 — Linguagens de Programação II / Compiladores
**Semestre:** 2026/1
**Professor:** Nicolas Maillard INF/UFRGS
**Lab Etapa 2:** quarta-feira, 22 de abril de 2026

---

## Pré-requisitos

- Etapa 1 concluída (entendimento do frontend: scanner, parser, AST)
- Ferramentas: `flex`, `bison`, `gcc` instalados
- Sistema: Linux ou macOS

---

## Estrutura de Arquivos

```
etapa2/
├── Makefile
├── README.md
├── doc/
│   └── especificacao_etapa2.md   — especificação completa (leia antes de começar)
├── src/
│   ├── scanner.l                 — scanner LARA (completo, da Etapa 1)
│   ├── parser.y                  — parser LARA (completo, da Etapa 1)
│   ├── tokens.h                  — definição de tokens (completo)
│   ├── ast.h / ast.c             — AST (completo)
│   ├── ast_walk.c                — percorrimento de AST (completo)
│   ├── symtab.h / symtab.c      — tabela de símbolos (completo)
│   ├── tac.h / tac.c             — módulo TAC (FORNECIDO COMPLETO)
│   ├── codegen.h                 — interface do gerador (completo)
│   ├── codegen.c                 — gerador de código (ESQUELETO — completar)
│   └── main.c                    — ponto de entrada (completo)
├── solution/
│   └── codegen_solution.c        — solução completa (apenas para o professor)
└── tests/
    ├── valid/                    — programas LARA válidos com saída esperada
    ├── invalid/                  — programas inválidos (devem ser rejeitados)
    └── run_tests.sh              — script de testes
```

---

## Como Compilar

```bash
cd etapa2
make
```

O executável gerado é `./lara`.

---

## Como Usar

```bash
./lara < programa.lc         # imprime TAC na stdout
./lara < programa.lc 2>/dev/null  # suprime mensagens de depuração
```

---

## Tarefas dos Alunos

Edite `src/codegen.c` e complete os seguintes TODOs:

### TODO-E2-A: `codegen_program()` — declarações globais

Complete o loop em `codegen_program()` para processar:
- `AST_VAR_DECL` (variável global): atribua offset, emita `TAC_DECL_GLOBAL`
- `AST_ARRAY_DECL` (array global): calcule tamanho total, emita `TAC_DECL_GLOBAL`

Use `symtab_lookup()` para encontrar a entrada na tabela e definir `scope` e `offset`.

**Exemplo:** para `int x ;` global com offset 0:
```c
codegen_emit(ctx, TAC_DECL_GLOBAL, "x", "4", NULL);
```

### TODO-E2-B: `codegen_expr()` — operadores aritméticos

No `case AST_EXPR_BINARY`, substitua `TAC_NOP` pela chamada correta:
```c
codegen_emit(ctx, op, tmp, left, right);  // op já vem de op_to_tac()
```

### TODO-E2-C: `codegen_expr()` — operadores relacionais

Os operadores `<`, `>`, `<=`, `>=`, `==`, `!=` seguem o mesmo padrão do TODO-E2-B.
A função `op_to_tac()` já os suporta — verifique se TODO-E2-B já cobre esse caso.

### TODO-E2-D: `codegen_stmt()` — atribuição simples `:=`

No `case AST_ASSIGN`, implemente o operador `:=`:
```c
char *rval = codegen_expr(ctx, stmt->children[1]);
// Para lvalue simples (AST_SYMBOL):
codegen_emit(ctx, TAC_COPY, lv->value, rval, NULL);
free(rval);
```

---

## Como Testar

```bash
make test          # executa run_tests.sh
# ou
bash tests/run_tests.sh
```

Para testar manualmente com a saída esperada:
```bash
./lara < tests/valid/01_soma.lc
diff <(./lara < tests/valid/01_soma.lc 2>/dev/null) tests/valid/01_soma.expected
```

---

## Critérios de Avaliação

| Critério                                    | Peso |
|---------------------------------------------|------|
| TODO-E2-A: declarações globais corretas      | 25%  |
| TODO-E2-B: operadores aritméticos corretos   | 25%  |
| TODO-E2-C: operadores relacionais corretos   | 20%  |
| TODO-E2-D: atribuição `:=` correta           | 20%  |
| Compilação sem erros e testes passando       | 10%  |

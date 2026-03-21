# Etapa 1 — Frontend do Compilador LARA

**Disciplina:** INF01083 — Linguagens de Programação II / Compiladores
**Semestre:** 2026/1
**Professor:** Nicolas Maillard INF/UFRGS
**Lab Etapa 1:** quarta-feira, 18 de março de 2026
**Grupos:** 2–3 alunos

---

## A Linguagem LARA

LARA é um subconjunto de C com variações sintáticas introduzidas para fins didáticos.

| Construção       | C padrão               | LARA                           |
|------------------|------------------------|-------------------------------|
| Declaração var.  | `int x = 5;`           | `let x := 5;`                 |
| Declaração array | `int v[10];`           | `array 10 of int v;`          |
| Cabeçalho função | `int f(int a) { }`     | `fun int f(int a) { }`        |
| Atribuição       | `x = expr;`            | `x := expr;`                  |
| Laço while       | `while (c) { }`        | `while (c) do { }`            |
| Literais bool    | `1` / `0`              | `true` / `false`              |

Tipos disponíveis: `int`, `float`, `bool`, `char`, `void`.

---

## Estrutura de Arquivos

```
etapa1/
├── Makefile                         — compilação, testes, limpeza
├── README.md                        — este arquivo
├── src/
│   ├── tokens.h                     — definição numérica dos tokens (referência)
│   ├── ast.h / ast.c                — AST: ast_new, ast_append, ast_print, ast_free
│   ├── symtab.h / symtab.c          — tabela de símbolos (hash djb2)
│   ├── scanner.l                    — scanner flex  [TODOs A e B para alunos]
│   ├── parser.y                     — gramática bison [TODOs C e D para alunos]
│   ├── ast_walk.c                   — percorrimento AST [TODOs E, F e G para alunos]
│   └── main.c                       — ponto de entrada (completo)
├── tests/
│   ├── run_tests.sh                 — script de testes automatizados
│   ├── valid/                       — programas LARA que devem ser aceitos
│   │   ├── 01_hello.lc              — programa mínimo
│   │   ├── 02_expr.lc               — expressões e atribuições
│   │   ├── 03_control.lc            — if/else, while, for, &&, ||
│   │   ├── 04_arrays.lc             — arrays, floats com expoente (requer TODO-B)
│   │   ├── 05_bool.lc               — literais bool, negação !
│   │   └── 06_chars_strings.lc      — char, strings, print
│   └── invalid/                     — programas que devem ser rejeitados
│       ├── 01_missing_semi.lc
│       ├── 02_unmatched_brace.lc
│       ├── 03_bad_assign.lc
│       ├── 04_bad_array_decl.lc
│       ├── 05_lex_error.lc
│       └── 06_bad_fun.lc
└── doc/
    ├── especificacao_etapa1.md      — especificação completa
    └── especificacao_etapa1.pdf     — versão PDF (gerada com pandoc)
```

---

## Pré-requisitos

- **GCC** ≥ 9 (ou clang equivalente)
- **flex** ≥ 2.6
- **bison** ≥ 2.3
- GNU make

---

## Como Compilar

```bash
cd etapa1/
make
```

Para limpar os arquivos gerados:

```bash
make clean
```

---

## Como Usar

O compilador lê da entrada padrão:

```bash
./lara < programa.lc
```

Em caso de sucesso, imprime a AST e estatísticas na saída padrão.
Erros léxicos e sintáticos vão para a saída de erro (stderr).
Código de saída: **0** = sucesso, **1** = erro.

---

## Tarefas dos Alunos

O código contém **7 pontos incompletos** marcados com `TODO`. São as tarefas que você deve resolver:

### TODO-A — Espaço em branco com tab (`scanner.l`)

A regra `[ \n]+` ignora apenas espaço e newline.
**Tarefa:** estender para também ignorar `\t` (tabulação) e `\r` (retorno de carro).
**Dica:** use uma classe de caracteres `[ \n\t\r]`.

### TODO-B — Float com expoente (`scanner.l`)

A definição `FLOAT` aceita apenas `3.14` mas não `1.5e10` ou `2.3E-4`.
**Tarefa:** estender o regex para aceitar notação científica opcional: `(e|E)(+|-)?{DIGIT}+`
**Dica:** use `?` para tornar o expoente opcional; agrupe com parênteses.

### TODO-C — Operadores `&&` e `||` (`parser.y`)

As ações semânticas dos operadores lógicos retornam `NULL` em vez de criar um nó AST.
**Tarefa:** preencher as chamadas a `ast_new(AST_EXPR_BINARY, "&&", ...)` e `ast_new(..., "||", ...)`.
**Siga** o padrão dos operadores relacionais (`<`, `>`, etc.) já implementados.

### TODO-D — Lista de argumentos com vírgula (`parser.y`)

A regra `expr_list_ne` aceita apenas um argumento.
**Tarefa:** adicionar a regra `expr_list_ne ',' expr` usando `ast_append()` para encadear.
**Siga** o padrão de `param_list_ne` já implementado.

### TODO-E — `ast_count_nodes` com `next` (`ast_walk.c`)

A função não percorre o encadeamento via `next`, contando menos nós do que o correto.
**Tarefa:** descomentar/adicionar a chamada recursiva `count += ast_count_nodes(node->next)`.

### TODO-F — `ast_count_leaves` (`ast_walk.c`)

A função retorna sempre 0.
**Tarefa:** implementar do zero. Um nó é "folha" quando todos os `children[]` e `next` são `NULL`.
**Percorra** a árvore recursivamente tanto via `children[]` quanto via `next`.

### TODO-G — `ast_max_depth` (`ast_walk.c`)

A função retorna sempre 0.
**Tarefa:** retornar a profundidade máxima da árvore. A raiz tem profundidade 0; cada nível de filho adiciona 1. O `next` não aumenta a profundidade.
**Dica:** use a função auxiliar `max(a, b)` já definida no arquivo.

---

## Como Testar

### Com make

```bash
make test
```

Executa os testes e mostra quais programas foram aceitos/rejeitados.

### Com o script de testes

```bash
bash tests/run_tests.sh
```

Saída com resultado de cada teste e resumo final.

### Testes individuais

```bash
./lara < tests/valid/01_hello.lc          # deve imprimir AST e sair com código 0
./lara < tests/invalid/01_missing_semi.lc  # deve sair com código 1
echo $?                                       # verifica código de saída
```

---

## Critérios de Avaliação da Etapa 1

| Critério                                   | Peso |
|--------------------------------------------|------|
| TODO-A: espaço branco com tab (`\t`, `\r`) | 10%  |
| TODO-B: float com expoente (`1.5e10`)      | 15%  |
| TODO-C: operadores lógicos `&&` e `\|\|`  | 15%  |
| TODO-D: lista de argumentos com vírgula    | 20%  |
| TODO-E: `ast_count_nodes` com `next`       | 10%  |
| TODO-F: `ast_count_leaves`                 | 15%  |
| TODO-G: `ast_max_depth`                    | 15%  |

**Total: 100%**

---

## Entrega

- **Formato:** arquivo `.tar.gz` contendo os diretórios `src/` e `tests/`
- **Conteúdo obrigatório:** todos os `.c`, `.h`, `.l`, `.y`, `.lc` e `Makefile`
- **Não incluir:** binários (`.o`, `lara`), arquivos gerados (`lex.yy.c`, `parser.tab.*`)
- **Via:** Moodle da disciplina

```bash
tar czf etapa1-grupo-NNN.tar.gz --exclude='*.o' --exclude='lex.yy.c' \
    --exclude='parser.tab.*' --exclude='lara' src/ tests/ Makefile
```

---

## Nota sobre Ferramentas de IA

Conforme o plano de ensino da disciplina, o uso de ferramentas de IA para resolver os TODOs é **proibido**. Os TODOs representam o aprendizado central da etapa.

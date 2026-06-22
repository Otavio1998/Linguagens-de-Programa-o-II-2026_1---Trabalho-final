# Etapa 3 — Compilador Completo: TAC com Controle de Fluxo + Assembly

**Disciplina:** INF01083 — Linguagens de Programação II / Compiladores
**Semestre:** 2026/1
**Professor:** Nicolas Maillard — sala 242, INF/UFRGS
**Lab:** segunda-feira, 01 de junho de 2026 *(etapa final)*

---

## Objetivo

Esta é a **etapa final** do projeto. O compilador LC− deve ser capaz de produzir
binários executáveis. O aluno implementa a geração de TAC para controle de fluxo;
o assembly é gerado automaticamente pela infraestrutura fornecida.

```
programa.lc  →  AST  →  TAC  →  assembly x86-64  →  binário
                        (aluno)    (fornecido)
```

---

## Pré-requisitos

- Etapa 2 concluída (geração de TAC para expressões e atribuições)
- Ferramentas: `flex`, `bison`, `gcc` instalados
- Execução dos testes: Linux x86-64 (gera assembly portável)
- Leitura obrigatória: `doc/especificacao_etapa3.md` e `src/backpatch.h`

---

## Estrutura de Arquivos

```
etapa3/
├── Makefile
├── README.md
├── doc/
│   └── especificacao_etapa3.md   — especificação completa
├── src/
│   ├── scanner.l / parser.y / tokens.h   — frontend (completo)
│   ├── ast.h / ast.c / ast_walk.c        — AST (completo)
│   ├── symtab.h / symtab.c               — tabela de símbolos (completo)
│   ├── tac.h / tac.c                     — módulo TAC (completo)
│   ├── backpatch.h / backpatch.c         — back-patching (FORNECIDO COMPLETO)
│   ├── asmgen.h / asmgen.c               — assembly x86-64 (FORNECIDO COMPLETO)
│   ├── codegen.h                         — interface do gerador (completo)
│   ├── codegen.c                         — gerador TAC (ESQUELETO — completar)
│   └── main.c                            — pipeline completo (completo)
├── solution/
│   ├── codegen_e3_solution.c             — solução dos TODOs (apenas professor)
│   └── asmgen_complete.c                 — referência asmgen (apenas professor)
└── tests/
    ├── valid/     — 6 programas com saída de execução esperada (.expected)
    ├── invalid/   — 6 programas inválidos (devem ser rejeitados)
    └── run_tests.sh
```

---

## Como Compilar

```bash
cd etapa3
make
```

O executável gerado é `./compilador`.

---

## Como Usar

```bash
# Compilar um programa LC− para assembly (stdout)
./compilador < programa.lc > programa.s

# Modo depuração: inspecionar o TAC gerado
./compilador -tac < programa.lc

# Montar, linkar e executar (requer Linux x86-64)
gcc programa.s -o programa -no-pie
./programa
```

---

## Tarefas dos Alunos

Edite `src/backpatch.c` (TODOs E e F) e `src/codegen.c` (TODOs A–D).
**Ordem recomendada: comece por E e F** — sem eles, nenhum salto funciona.

### TODO-E3-E: `patch_list_backpatch()` — o núcleo do back-patching (`backpatch.c`)

Percorra a lista de saltos pendentes e substitua o campo `result` de cada
instrução TAC pelo rótulo real. Esta é a operação que "volta atrás" nas
instruções já emitidas para completá-las. Ver seção 4 da especificação.

### TODO-E3-F: `patch_list_merge()` — combinação de listas (`backpatch.c`)

Una duas listas ligadas de saltos pendentes em uma única lista.
Necessário para combinar as listas de `&&` e `||`. Ver seção 4.

### TODO-E3-A: `codegen_bool_expr()` — `&&` e `||` com curto-circuito (`codegen.c`)

Implemente os dois casos usando back-patching. Consulte a seção 5.1 da
especificação e os comentários no código.

### TODO-E3-B: `codegen_stmt()` — `if/else` (`codegen.c`)

Use `codegen_bool_expr()` para a condição e back-patching para os rótulos.
Trate os casos com e sem `else` (ver seção 5.2 da especificação).

### TODO-E3-C: `codegen_stmt()` — `while...do` (`codegen.c`)

Emita o rótulo de início, gere a condição e o corpo, feche o laço com `goto`
e aplique back-patching na saída (seção 5.3).

### TODO-E3-D: `codegen_stmt()` — `for` (`codegen.c`)

`children[0]` = init, `children[1]` = condição, `children[2]` = passo,
`children[3]` = corpo (seção 5.4).

---

## Como Testar

```bash
make test
# ou
bash tests/run_tests.sh
```

Cada teste compila o programa, executa o binário e compara a saída com
o arquivo `.expected`. Em macOS, apenas a geração de assembly é verificada
(a execução requer Linux x86-64).

---

## Critérios de Avaliação

| Critério                                              | Arquivo        | Peso |
|-------------------------------------------------------|----------------|------|
| TODO-E3-E: `patch_list_backpatch()` correto           | `backpatch.c`  | 15%  |
| TODO-E3-F: `patch_list_merge()` correto               | `backpatch.c`  | 10%  |
| TODO-E3-A: `&&` e `\|\|` com curto-circuito           | `codegen.c`    | 25%  |
| TODO-E3-B: `if/else` com back-patching                | `codegen.c`    | 20%  |
| TODO-E3-C: `while` com back-patching                  | `codegen.c`    | 15%  |
| TODO-E3-D: `for` com back-patching                    | `codegen.c`    | 15%  |

Verificação por execução: programas compilados que produzem saída correta.

---

## Extra: Otimizações Locais (Opcional)

O módulo `src/optim.c` contém três TODOs opcionais para quem quiser
explorar otimizações clássicas de compiladores. **Não são avaliados.**

| TODO       | Função            | O que implementar                              |
|------------|-------------------|------------------------------------------------|
| OPT-A      | `cfg_build()`     | Identificar blocos básicos e construir o CFG   |
| OPT-B      | `bb_const_fold()` | Dobragem de constantes dentro de um BB         |
| OPT-C      | `bb_copy_prop()`  | Propagação de cópias dentro de um BB           |

```bash
# Compilar com otimização:
./compilador -O < programa.lc > programa.s

# Ver TAC antes e depois:
./compilador    -tac < programa.lc
./compilador -O -tac < programa.lc

# Visualizar o CFG (requer OPT-A implementado):
./compilador -cfg < programa.lc
```

Ver Apêndice A da especificação para os algoritmos detalhados.

---
title: "Etapa 1 — Frontend do Compilador LARA"
subtitle: "INF01083 — Linguagens de Programação II / Compiladores — 2026/1"
author: "Prof. Nicolas Maillard — INF/UFRGS"
date: "Laboratório: 18 de março de 2026"
lang: pt-BR
---

> **Ambiente de desenvolvimento obrigatório:** Todo o desenvolvimento e teste do
> projeto deve ser realizado em **Linux** (Ubuntu 22.04 LTS ou equivalente).
> O compilador `lara` é gerado com GCC, flex e bison para a arquitetura
> x86-64 Linux. Submissões que funcionem apenas em macOS ou Windows **não**
> serão aceitas.

# Objetivo

A Etapa 1 tem dois objetivos complementares:

1. **Revisar** os conceitos de análise léxica (flex) e sintática (bison), e de Árvore de Sintaxe Abstrata (AST), que são o frontend de qualquer compilador.
2. **Praticar** o percorrimento recursivo de uma estrutura de árvore em C.

Os alunos recebem um compilador quase completo para a linguagem **LARA** e devem completar **7 pontos intencionalmente deixados em aberto** (marcados com `TODO-A` a `TODO-G`).

---

# A Linguagem LARA

**LARA** é a sigla de *Linguagem Acadêmica Reduzida e Adaptada*. O nome reflete as três propriedades essenciais da linguagem: é *acadêmica* (projetada para ensino de compiladores), *reduzida* (subconjunto deliberadamente pequeno de C) e *adaptada* (sintaxe propositalmente diferente da linguagem-fonte de inspiração, de modo a exigir que os alunos leiam e compreendam o código fornecido).

## Diferenças em relação ao C

| Construção        | C padrão               | LARA                          |
|-------------------|------------------------|-------------------------------|
| Declaração var.   | `int x = 5;`           | `let x := 5;`                 |
| Declaração array  | `int v[10];`           | `array 10 of int v;`          |
| Cabeçalho função  | `int f(int a) { }`     | `fun int f(int a) { }`        |
| Atribuição        | `x = expr;`            | `x := expr;`                  |
| Laço while        | `while (c) { }`        | `while (c) do { }`            |
| Literais bool     | `1` / `0`              | `true` / `false`              |

## Tabela de Tokens

| Token              | Valor | Descrição                            | Exemplo          |
|--------------------|-------|--------------------------------------|------------------|
| `TK_PR_INT`        | 258   | tipo inteiro                         | `int`            |
| `TK_PR_FLOAT`      | 259   | tipo ponto flutuante                 | `float`          |
| `TK_PR_BOOL`       | 260   | tipo booleano                        | `bool`           |
| `TK_PR_CHAR`       | 261   | tipo caractere                       | `char`           |
| `TK_PR_IF`         | 262   | condicional                          | `if`             |
| `TK_PR_ELSE`       | 263   | alternativa                          | `else`           |
| `TK_PR_WHILE`      | 264   | laço com condição no início          | `while`          |
| `TK_PR_FOR`        | 265   | laço com init/cond/step              | `for`            |
| `TK_PR_RETURN`     | 266   | retorno de função                    | `return`         |
| `TK_PR_VOID`       | 267   | tipo vazio / ausência de valor       | `void`           |
| `TK_PR_ARRAY`      | 268   | declaração de vetor (LARA)           | `array`          |
| `TK_PR_OF`         | 269   | tipo base do vetor (LARA)            | `of`             |
| `TK_PR_LET`        | 270   | declaração de variável local (LARA)  | `let`            |
| `TK_PR_FUN`        | 271   | cabeçalho de função (LARA)           | `fun`            |
| `TK_PR_DO`         | 272   | separador do while (LARA)            | `do`             |
| `TK_PR_PRINT`      | 273   | saída padrão                         | `print`          |
| `TK_PR_READ`       | 274   | entrada padrão                       | `read`           |
| `TK_LIT_TRUE`      | 275   | literal booleano verdadeiro          | `true`           |
| `TK_LIT_FALSE`     | 276   | literal booleano falso               | `false`          |
| `TK_OC_LE`         | 277   | menor ou igual                       | `<=`             |
| `TK_OC_GE`         | 278   | maior ou igual                       | `>=`             |
| `TK_OC_EQ`         | 279   | igualdade                            | `==`             |
| `TK_OC_NE`         | 280   | diferença                            | `!=`             |
| `TK_OC_AND`        | 281   | conjunção lógica                     | `&&`             |
| `TK_OC_OR`         | 282   | disjunção lógica                     | `\|\|`           |
| `TK_OC_ASSIGN`     | 284   | atribuição LARA                      | `:=`             |
| `TK_OC_PLUSEQ`     | 285   | atribuição composta soma             | `+=`             |
| `TK_OC_MINUSEQ`    | 286   | atribuição composta subtração        | `-=`             |
| `TK_ERROR`         | 287   | caractere inválido (erro léxico)     | `@`, `#`, `$`   |
| `TK_ID`            | 288   | identificador                        | `x`, `soma`      |
| `TK_LIT_INT`       | 289   | literal inteiro                      | `42`, `0`        |
| `TK_LIT_FLOAT`     | 290   | literal ponto flutuante              | `3.14`, `1.5e10` |
| `TK_LIT_CHAR`      | 291   | literal caractere                    | `'a'`, `'z'`     |
| `TK_LIT_STRING`    | 292   | literal cadeia de caracteres         | `"texto"`        |

Caracteres simples (`+`, `-`, `*`, `/`, `%`, `<`, `>`, `!`, `=`, `(`, `)`, `{`, `}`, `[`, `]`, `,`, `;`, `:`) são retornados diretamente com seu valor ASCII.

## Gramática (estilo Yacc)

```yacc
program
    : toplevel_list
    | /* vazio */
    ;

toplevel_list
    : toplevel_decl
    | toplevel_list toplevel_decl
    ;

toplevel_decl
    : fun_decl
    | var_decl
    | array_decl
    ;

fun_decl
    : 'fun' type_spec ID '(' param_list ')' block
    ;

param_list
    : /* vazio */
    | param_list_ne
    ;

param_list_ne
    : param
    | param_list_ne ',' param
    ;

param
    : type_spec ID
    ;

var_decl
    : type_spec ID ';'
    ;

array_decl
    : 'array' INT_LIT 'of' type_spec ID ';'
    ;

type_spec
    : 'int'
    | 'float'
    | 'bool'
    | 'char'
    | 'void'
    ;

block
    : '{' stmt_list '}'
    | '{' '}'
    ;

stmt_list
    : stmt
    | stmt_list stmt
    ;

stmt
    : simple_stmt ';'
    | compound_stmt
    ;

simple_stmt
    : assign_stmt
    | return_stmt
    | print_stmt
    | read_stmt
    | call_stmt
    | var_local
    ;

compound_stmt
    : if_stmt
    | while_stmt
    | for_stmt
    ;

var_local
    : 'let' ID ':=' expr
    ;

assign_stmt
    : lvalue ':=' expr
    | lvalue '+=' expr
    | lvalue '-=' expr
    ;

if_stmt
    : 'if' '(' expr ')' block
    | 'if' '(' expr ')' block 'else' block
    ;

while_stmt
    : 'while' '(' expr ')' 'do' block
    ;

for_stmt
    : 'for' '(' assign_stmt ';' expr ';' assign_stmt ')' block
    ;

return_stmt
    : 'return' expr
    ;

print_stmt
    : 'print' expr
    ;

read_stmt
    : 'read' lvalue
    ;

call_stmt
    : ID '(' expr_list ')'
    ;

expr
    : expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | expr '<' expr
    | expr '>' expr
    | expr '<=' expr
    | expr '>=' expr
    | expr '==' expr
    | expr '!=' expr
    | expr '&&' expr
    | expr '||' expr
    | '!' expr
    | '-' expr
    | '(' expr ')'
    | ID '(' expr_list ')'
    | ID '[' expr ']'
    | ID
    | literal
    ;

expr_list
    : /* vazio */
    | expr_list_ne
    ;

expr_list_ne
    : expr
    | expr_list_ne ',' expr
    ;

lvalue
    : ID
    | ID '[' expr ']'
    ;

literal
    : INT_LIT
    | FLOAT_LIT
    | CHAR_LIT
    | STRING_LIT
    | 'true'
    | 'false'
    ;
```

**Precedência de operadores** (menor para maior):

| Nível | Operadores                     | Associatividade |
|-------|--------------------------------|-----------------|
| 1     | `:=`, `+=`, `-=`               | direita         |
| 2     | `\|\|`                         | esquerda        |
| 3     | `&&`                           | esquerda        |
| 4     | `==`, `!=`                     | esquerda        |
| 5     | `<`, `>`, `<=`, `>=`           | esquerda        |
| 6     | `+`, `-`                       | esquerda        |
| 7     | `*`, `/`, `%`                  | esquerda        |
| 8     | `!`, `-` (unário)              | direita         |
| 9     | `[`                            | esquerda        |

---

# Como o Compilador é Construído: Flex, Bison e o Pipeline

Esta seção explica o que cada ferramenta faz, quais arquivos produz, e como
as peças se encaixam para formar o compilador `lara`. Leia com atenção antes
de começar a editar qualquer arquivo.

## Visão geral do pipeline de compilação

Compilar o projeto com `make` executa os seguintes passos, nesta ordem:

```
src/scanner.l  --flex-->  src/lex.yy.c       (scanner em C)
src/parser.y   --bison--> src/parser.tab.c   (parser em C)
                             src/parser.tab.h   (definição dos tokens)

src/lex.yy.c  --|
src/parser.tab.c--|
src/ast.c      --|--gcc--> lara               (binário final)
src/symtab.c   --|
src/ast_walk.c --|
src/main.c     --|
```

Cada etapa é descrita a seguir.

## Flex — o scanner

### O que é

Flex (*Fast Lexical Analyzer Generator*) é uma ferramenta que gera scanners
(analisadores léxicos) automaticamente a partir de uma especificação de
expressões regulares.

### Entrada: `src/scanner.l`

O arquivo `scanner.l` contém a especificação do scanner de LARA. Ele é dividido
em três seções separadas por `%%`:

```
definições       ← macros como DIGIT, LETTER, FLOAT
%%
regras           ← pares (expressão regular) { ação em C }
%%
código auxiliar  ← funções C extras (normalmente vazio)
```

Cada regra tem a forma:

```
expressão_regular   { código C executado quando o padrão casa }
```

Por exemplo, a regra que reconhece a palavra reservada `if` e retorna o token
correspondente é:

```c
"if"    { return TK_PR_IF; }
```

E a regra que reconhece identificadores (sequências de letras e dígitos) e
insere o lexema na tabela de símbolos é:

```c
{ID}    { yylval.sym = symtab_insert(global_symtab, yytext, yylineno);
          return TK_ID; }
```

Aqui, `yytext` é uma variável global do flex que contém o texto do token
reconhecido, e `yylineno` é o número da linha corrente.

### Comando de invocação

```bash
flex -o src/lex.yy.c src/scanner.l
```

### Saída: `src/lex.yy.c`

O flex gera o arquivo `lex.yy.c`, que contém a implementação em C da função:

```c
int yylex(void);
```

Cada chamada a `yylex()` lê caracteres da entrada (por padrão, `stdin`),
avança até o fim do próximo token, e **retorna o código numérico do token**
(ex.: `TK_PR_IF`, `TK_LIT_INT`, `'+'`, etc.). Se o token tem um valor
associado (identificador, literal), ele é armazenado na variável global
`yylval` antes de retornar.

`yylex()` é chamada repetidamente pelo parser — os alunos nunca precisam
chamá-la diretamente.

## Bison — o parser

### O que é

Bison é um gerador de parsers LALR(1). Ele recebe uma gramática com ações
semânticas em C e gera automaticamente um parser capaz de reconhecer essa
gramática.

### Entrada: `src/parser.y`

O arquivo `parser.y` contém a especificação do parser de LARA. Também tem
três seções separadas por `%%`:

```
declarações     ← tokens (%token), tipos (%type), precedência (%left, %right)
%%
gramática       ← regras de produção com ações semânticas em C
%%
código auxiliar ← funções C extras (ex.: yyerror)
```

Cada regra de produção tem a forma:

```
nao_terminal
    : sequência_de_símbolos   { ação semântica em C }
    | outra_alternativa       { ação semântica em C }
    ;
```

Nas ações semânticas, `$$` representa o valor do não-terminal sendo reduzido,
e `$1`, `$2`, ... representam os valores dos símbolos do lado direito. Por
exemplo, a regra que cria um nó binário na AST para a soma de duas expressões:

```c
expr
    : expr '+' expr
        {
            $$ = ast_new(AST_EXPR_BINARY, "+", yylineno);
            $$->children[0] = $1;
            $$->children[1] = $3;
        }
    ;
```

### Comando de invocação

```bash
bison -d -o src/parser.tab.c src/parser.y
```

A opção `-d` instrui o bison a gerar também o arquivo de cabeçalho.

### Saída: `src/parser.tab.c` e `src/parser.tab.h`

O bison gera dois arquivos:

**`src/parser.tab.c`** — contém a implementação em C da função:

```c
int yyparse(void);
```

`yyparse()` implementa o autômato LALR(1) que reconhece a gramática de LARA.
Internamente, ela chama `yylex()` repetidamente para obter tokens, executa as
ações semânticas associadas às reduções e, ao final de uma análise bem-sucedida,
retorna 0. Em caso de erro sintático, chama `yyerror()` e retorna 1.

**`src/parser.tab.h`** — define os valores numéricos de todos os tokens
declarados com `%token` no arquivo `.y`. Este arquivo é incluído pelo scanner
(`#include "parser.tab.h"` no `scanner.l`) para que `yylex()` e `yyparse()`
usem os mesmos valores numéricos para cada token.

## Como `main()` orquestra tudo

### Localização: `src/main.c`

O arquivo `main.c` é o ponto de entrada do compilador `lara`. Ele não realiza
análise léxica nem sintática diretamente — essas tarefas são delegadas às
funções geradas pelo flex e pelo bison.

O fluxo de execução é o seguinte:

```c
int main(int argc, char *argv[])
{
    // 1. Cria a tabela de símbolos global (usada pelo scanner e pelo parser)
    global_symtab = symtab_new();

    // 2. Chama o parser — que por sua vez chama o scanner repetidamente
    int resultado = yyparse();

    // 3. Se a análise foi bem-sucedida (retorno 0):
    if (resultado == 0) {
        // ast_root aponta para a raiz da AST completa do programa
        ast_print(ast_root, 0, stdout);
        main_walk(ast_root);
        symtab_print(global_symtab, stdout);
    }

    // 4. Libera memória e sai
    ast_free(ast_root);
    symtab_free(global_symtab);
    return resultado;
}
```

### Por que `yyparse()` dá acesso à AST?

A variável global `ast_root` é declarada em `parser.y`:

```c
ast_node_t *ast_root = NULL;   /* declarada na seção de código de parser.y */
```

e declarada como `extern` em `main.c`:

```c
extern ast_node_t *ast_root;
```

Durante a análise, cada redução pela regra do símbolo inicial (`program`)
executa a ação semântica:

```c
program : toplevel_list   { ast_root = $1; }
```

Isso significa: quando o parser reconhece o programa inteiro (reduz para
`program`), ele atribui a lista de declarações de topo à variável `ast_root`.
Portanto, após `yyparse()` retornar 0, `ast_root` já aponta para a raiz da
AST do programa analisado — pronta para ser percorrida por `main_walk()` ou
pelas etapas seguintes do compilador.

## Guia de leitura do código: por onde começar

Recomenda-se explorar os arquivos na seguinte ordem:

1. **`src/tokens.h`** — lista de constantes numéricas dos tokens. Leia apenas
   para ter uma referência; não precisa entender a implementação.

2. **`src/ast.h`** — define o tipo `ast_node_t` (estrutura de um nó da AST) e
   as funções `ast_new()`, `ast_add_child()`, `ast_append()`, `ast_print()`.
   Entenda os campos `type`, `value`, `children[]` e `next` — eles aparecem em
   todos os outros módulos.

3. **`src/symtab.h`** — interface da tabela de símbolos. Entenda `symtab_insert()`
   e `symtab_lookup()`.

4. **`src/main.c`** — ponto de entrada. Leia na íntegra; é curto e explica o
   fluxo de alto nível.

5. **`src/scanner.l`** — especificação léxica. Identifique as seções de
   definições, regras e código auxiliar. Localize os TODOs-A e B.

6. **`src/parser.y`** — gramática com ações semânticas. Observe como cada
   regra cria nós AST com `ast_new()` e os encadeia com `ast_append()`.
   Localize os TODOs-C e D.

7. **`src/ast_walk.c`** — funções de percorrimento da AST. São as funções
   que os alunos devem implementar nos TODOs-E, F e G.

---

# Arquivos Fornecidos

| Arquivo          | Estado        | Descrição                                      |
|------------------|---------------|------------------------------------------------|
| `tokens.h`       | Completo      | Definição numérica dos tokens (referência)     |
| `ast.h` / `ast.c`| Completo      | Implementação completa da AST                  |
| `symtab.h/.c`    | Completo      | Tabela de símbolos com hash djb2               |
| `main.c`         | Completo      | Ponto de entrada do compilador                 |
| `scanner.l`      | **Esqueleto** | 2 TODOs (A e B)                               |
| `parser.y`       | **Esqueleto** | 2 TODOs (C e D)                               |
| `ast_walk.c`     | **Esqueleto** | 3 TODOs (E, F e G)                            |

---

# Como Começar — Passo a Passo

## 1. Obter o código

Faça o download do arquivo `etapa1-INF01083-2026-1.tar.gz` disponível no
Moodle da disciplina e transfira-o para a sua máquina Linux.

## 2. Descompactar

```bash
tar xzf etapa1-INF01083-2026-1.tar.gz
cd etapa1/
```

Você verá a seguinte estrutura:

```
etapa1/
├── src/           ← código-fonte (edite apenas os arquivos marcados "Esqueleto")
├── tests/
│   ├── valid/     ← programas LARA corretos para testar
│   ├── invalid/   ← programas com erros sintáticos (devem ser rejeitados)
│   └── run_tests.sh
├── doc/           ← esta especificação em PDF
├── Makefile
└── README.md
```

## 3. Instalar as dependências (uma única vez)

```bash
sudo apt-get update
sudo apt-get install -y build-essential flex bison
```

## 4. Compilar o projeto

```bash
make
```

Se tudo correr bem, o binário `lara` será gerado no diretório `etapa1/`.
**Erros de compilação não são esperados** — o scaffold já compila desde o início.

## 5. Executar um primeiro teste manual

```bash
echo 'fun void main() { let x := 42 ; print x ; }' | ./lara
```

O compilador imprimirá a AST do programa e as estatísticas. Com os TODOs
ainda não implementados, alguns casos podem produzir saída incompleta ou
mensagens de aviso — isso é esperado.

## 6. Executar a suite de testes

```bash
make test
# ou equivalentemente:
bash tests/run_tests.sh
```

Com o scaffold inicial, os **testes de programas válidos falharão** (é esperado,
pois os TODOs ainda não estão implementados). Os **testes de programas inválidos
devem passar** — o compilador já deve rejeitar programas com erros sintáticos.

## 7. Entender o código antes de editar

Antes de escrever qualquer linha, leia a seção
**"Como o Compilador é Construído: Flex, Bison e o Pipeline"** desta
especificação e siga o **Guia de leitura do código** (também nessa seção).
A ordem sugerida é: `tokens.h` → `ast.h` → `symtab.h` → `main.c` →
`scanner.l` → `parser.y` → `ast_walk.c`.

## 8. Implementar os TODOs

Edite apenas os três arquivos marcados "Esqueleto":

| Arquivo       | TODOs      | O que fazer                         |
|---------------|------------|-------------------------------------|
| `scanner.l`   | A, B       | Regras léxicas para `	` e float    |
| `parser.y`    | C, D       | Regras sintáticas para `&&`/`\|\|` e args |
| `ast_walk.c`  | E, F, G    | Funções de percorrimento da AST     |

Cada TODO está marcado no código com um comentário `/* TODO-X: ... */` e
acompanhado de instruções sobre o que implementar. Após cada modificação:

```bash
make          # recompila (roda flex e bison automaticamente se necessário)
make test     # verifica os testes
```

## 9. Trabalho em grupo com GitHub

Consulte a seção **"Colaboração com GitHub"** da especificação unificada do
projeto para instruções sobre como configurar o repositório, fazer commits e
submeter o trabalho.


---

# Tarefas — Descrição Detalhada

## TODO-A: Espaço em branco com tab (`scanner.l`)

**Arquivo:** `src/scanner.l`
**Localização:** regra `[ \n]+`

**Problema:** a regra atual ignora apenas espaço (` `) e newline (`\n`), mas
não ignora tabulação (`\t`) nem retorno de carro (`\r`). Programas com tabs
(ex: código gerado por editores) provocam erro léxico.

**Tarefa:** editar a expressão regular para incluir `\t` e `\r`.

```
/* Antes */
[ \n]+      { /* ignora espaço em branco */ }

/* Depois */
[ \n\t\r]+  { /* ignora espaço em branco */ }
```

---

## TODO-B: Float com expoente (`scanner.l`)

**Arquivo:** `src/scanner.l`
**Localização:** definição `FLOAT`

**Problema:** a definição atual reconhece `3.14` e `0.5`, mas não reconhece
notação científica como `1.5e10`, `2.3E-4`, `6.02e+23`.

**Tarefa:** estender o regex `FLOAT` para suportar expoente opcional.

```
/* Antes */
FLOAT  {DIGIT}*"."{DIGIT}+|{DIGIT}+"."{DIGIT}*

/* Depois */
FLOAT  ({DIGIT}*"."{DIGIT}+|{DIGIT}+"."{DIGIT}*)([eE][+-]?{DIGIT}+)?
```

| Entrada    | Token esperado após TODO-B |
|------------|---------------------------|
| `3.14`     | `TK_LIT_FLOAT`            |
| `1.5e10`   | `TK_LIT_FLOAT`            |
| `2.3E-4`   | `TK_LIT_FLOAT`            |
| `6.02e+23` | `TK_LIT_FLOAT`            |

---

## TODO-C: Operadores `&&` e `||` (`parser.y`)

**Arquivo:** `src/parser.y`
**Localização:** regras `expr TK_OC_AND expr` e `expr TK_OC_OR expr`

**Problema:** as ações semânticas retornam `NULL` em vez de criar um nó
`AST_EXPR_BINARY`.

**Tarefa:** preencher as duas ações semânticas seguindo o padrão dos outros
operadores binários já implementados.

```c
/* Antes */
| expr TK_OC_AND expr  { $$ = NULL; /* INCOMPLETO */ }
| expr TK_OC_OR  expr  { $$ = NULL; /* INCOMPLETO */ }

/* Depois */
| expr TK_OC_AND expr  {
      $$ = ast_new(AST_EXPR_BINARY, "&&", yylineno);
      $$->children[0] = $1;
      $$->children[1] = $3;
  }
| expr TK_OC_OR  expr  {
      $$ = ast_new(AST_EXPR_BINARY, "||", yylineno);
      $$->children[0] = $1;
      $$->children[1] = $3;
  }
```

---

## TODO-D: Lista de argumentos com vírgula (`parser.y`)

**Arquivo:** `src/parser.y`
**Localização:** regra `expr_list_ne`

**Problema:** a regra só aceita um argumento. Chamadas como `f(a, b, c)`
geram erro sintático.

**Tarefa:** adicionar a produção recursiva com `ast_append()`.

```yacc
/* Antes */
expr_list_ne
    : expr                     { $$ = $1; }
    /* TODO-D: falta regra para lista com vírgula */
    ;

/* Depois */
expr_list_ne
    : expr                     { $$ = $1; }
    | expr_list_ne ',' expr    { $$ = ast_append($1, $3); }
    ;
```

`ast_append(list, node)` encadeia `node` ao final da lista `list` via o campo
`next` de `ast_node_t`, e retorna a cabeça da lista.

---

## TODO-E: `ast_count_nodes` com `next` (`ast_walk.c`)

**Arquivo:** `src/ast_walk.c`
**Localização:** função `ast_count_nodes`

**Problema:** a versão atual percorre os filhos (`children[]`) mas ignora o
encadeamento `next`. Em programas com múltiplos comandos, a contagem será menor
que o total real de nós.

**Tarefa:** adicionar a chamada recursiva via `next`:

```c
count += ast_count_nodes(node->next);
```

---

## TODO-F: `ast_count_leaves` (`ast_walk.c`)

**Arquivo:** `src/ast_walk.c`
**Localização:** função `ast_count_leaves`

**Problema:** a função sempre retorna 0.

**Definição:** um nó é *folha* quando todos os seus `children[]` são `NULL`
**e** `next` também é `NULL`.

**Tarefa:** implementar com percorrimento recursivo. Exemplo:

```c
int ast_count_leaves(const ast_node_t *node)
{
    if (node == NULL) return 0;
    int is_leaf = 1;
    for (int i = 0; i < AST_MAX_CHILDREN; i++)
        if (node->children[i] != NULL) { is_leaf = 0; break; }
    if (node->next != NULL) is_leaf = 0;
    int count = is_leaf ? 1 : 0;
    for (int i = 0; i < AST_MAX_CHILDREN; i++)
        count += ast_count_leaves(node->children[i]);
    count += ast_count_leaves(node->next);
    return count;
}
```

---

## TODO-G: `ast_max_depth` (`ast_walk.c`)

**Arquivo:** `src/ast_walk.c`
**Localização:** função `ast_max_depth`

**Problema:** a função sempre retorna 0.

**Definição:** profundidade máxima da árvore (a raiz tem profundidade 0; cada
nível de filho adiciona 1). O campo `next` **não** aumenta a profundidade —
ele representa o mesmo nível sintático.

**Tarefa:** implementar com percorrimento recursivo. Exemplo:

```c
int ast_max_depth(const ast_node_t *node)
{
    if (node == NULL) return -1;
    int depth = 0;
    for (int i = 0; i < AST_MAX_CHILDREN; i++)
        depth = max(depth, 1 + ast_max_depth(node->children[i]));
    depth = max(depth, ast_max_depth(node->next));
    return depth;
}
```

---

# Aulas Relacionadas

Os tópicos necessários para a Etapa 1 são cobertos nas cinco aulas que antecedem
o laboratório de 18 de março:

| Aula | Data      | Tema                                                                     | Relevância para E1               |
|------|-----------|--------------------------------------------------------------------------|----------------------------------|
| E1   | Seg 02/03 | Introdução geral — fases de compilador; visão geral do projeto e da LARA | Contexto e estrutura do semestre |
| E2   | Qua 04/03 | Análise léxica — tokens, expressões regulares, AFND→AFD, flex            | `scanner.l`: TODOs A e B         |
| E3   | Seg 09/03 | Análise sintática descendente — GLCs, LL(1), estrutura de arquivo bison  | `parser.y`: base teórica         |
| E4   | Qua 11/03 | Análise ascendente — LALR(1), conflitos, ações semânticas no bison       | `parser.y`: TODOs C e D          |
| E5   | Seg 16/03 | AST — construção com ações semânticas, percorrimento recursivo em C      | `ast.h`/`ast.c`: TODOs E, F, G   |

---

# Entrega e Avaliação

## Sessão de laboratório (18 de março de 2026)

No encontro, cada grupo demonstra ao professor:

- Compilação com `make` sem erros
- Execução de pelo menos 3 programas de teste (`bash tests/run_tests.sh`)
- Compreensão do código escrito (o professor pode fazer perguntas a qualquer
  integrante do grupo)

A avaliação parcial é registrada durante a sessão.

## Prazo de entrega no Moodle: lab + 48 horas

Após o laboratório, os grupos têm **48 horas** para incorporar correções
identificadas durante a sessão e submeter a versão final no Moodle.

- **Deadline:** sexta-feira, 20 de março de 2026 (18h)
- **Formato:** arquivo `etapa1-grupo-NOME.tar.gz` gerado a partir do repositório GitHub do grupo (ver seção GitHub abaixo)

```bash
# Dentro do diretório etapa1/:
tar czf etapa1-grupo-NOME.tar.gz \
    --exclude='src/*.o'          \
    --exclude='src/lex.yy.c'     \
    --exclude='src/parser.tab.*' \
    --exclude='lara'             \
    src/ tests/ Makefile
```

## Critérios de Avaliação

| Critério                                    | Peso |
|---------------------------------------------|------|
| TODO-A: espaço branco com `\t` e `\r`       | 10%  |
| TODO-B: float com expoente (`1.5e10`)        | 15%  |
| TODO-C: operadores lógicos `&&` e `\|\|`    | 15%  |
| TODO-D: lista de argumentos com vírgula      | 20%  |
| TODO-E: `ast_count_nodes` com `next`         | 10%  |
| TODO-F: `ast_count_leaves`                   | 15%  |
| TODO-G: `ast_max_depth`                      | 15%  |

A avaliação considera tanto a **corretude** (testes automatizados) quanto a
**clareza** do código. Grupos que não souberem explicar o código que escreveram
perdem a nota proporcional ao TODO em questão.

---

# Apêndice: As 4 Etapas do Projeto

| Etapa | Lab   | Tema                                              |
|-------|-------|---------------------------------------------------|
| **1** | 18/03 | Frontend: scanner (flex) + parser (bison) + AST   |
| **2** | 22/04 | TAC básico: expressões, declarações, atribuições  |
| **3** | 06/05 | TAC completo: booleanos, if/while, funções        |
| **4** | 01/06 | Assembly (x86-64) + otimizações                   |

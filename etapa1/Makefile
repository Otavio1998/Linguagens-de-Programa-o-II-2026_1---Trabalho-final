# =============================================================================
# Makefile — Etapa 1 do Compilador LARA
#
# INF01083 — Linguagens de Programação II / Compiladores — 2026/1
# UFRGS / INF — Prof. Nicolas Maillard
#
# Uso:
#   make           — compila tudo e gera o binário 'lara'
#   make clean     — remove arquivos gerados
#   make test      — executa todos os testes em tests/
#   make ast       — compila e roda um exemplo simples, imprimindo a AST
# =============================================================================

# Nome do executável final
TARGET = lara

# Diretório do código-fonte
SRCDIR = src

# Compilador C e flags
CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c11 -D_POSIX_C_SOURCE=200809L -I$(SRCDIR)

# Ferramentas de geração
FLEX    = flex
BISON   = bison

# Arquivos gerados automaticamente (não edite)
BISON_OUT  = $(SRCDIR)/parser.tab.c
BISON_H    = $(SRCDIR)/parser.tab.h
FLEX_OUT   = $(SRCDIR)/lex.yy.c

# Fontes C compilados diretamente (sem geração)
C_SRCS = $(SRCDIR)/ast.c \
         $(SRCDIR)/symtab.c \
         $(SRCDIR)/ast_walk.c \
         $(SRCDIR)/main.c

# Todos os fontes C (incluindo os gerados)
ALL_SRCS = $(BISON_OUT) $(FLEX_OUT) $(C_SRCS)

# Objetos
OBJS = $(ALL_SRCS:.c=.o)

# =============================================================================
# Regras
# =============================================================================


# Detecção de sistema operacional
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
    # macOS: workaround para bug do flex com PATH longo
    FLEX_ENV = env -i PATH="/usr/bin:/bin:/usr/local/bin:/opt/homebrew/bin" \
               HOME="$${HOME}" TMPDIR="$${TMPDIR}" LANG="C"
else
    FLEX_ENV =
endif
.PHONY: all clean test ast help

## Alvo padrão: compila tudo
all: $(TARGET)

## Linka todos os objetos no executável final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo ">>> Compilação concluída: $(TARGET)"

## Geração do parser (bison) — deve ser antes do flex para gerar parser.tab.h
$(BISON_OUT) $(BISON_H): $(SRCDIR)/parser.y
	$(BISON) -d -o $(BISON_OUT) $(SRCDIR)/parser.y
	@echo ">>> bison gerou $(BISON_OUT) e $(BISON_H)"

## Geração do scanner (flex) — depende do parser.tab.h para os tokens
## Nota: env -i com PATH mínimo contorna bug do Apple flex com PATH longo
$(FLEX_OUT): $(SRCDIR)/scanner.l $(BISON_H)
	$(FLEX_ENV) $(FLEX) -o $(FLEX_OUT) $(SRCDIR)/scanner.l
	@echo ">>> flex gerou $(FLEX_OUT)"

## Compilação de cada .c em .o (regra genérica)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

## Dependências manuais (os gerados precisam dos headers)
$(SRCDIR)/lex.yy.o:     $(FLEX_OUT) $(BISON_H) $(SRCDIR)/tokens.h $(SRCDIR)/symtab.h $(SRCDIR)/ast.h
$(SRCDIR)/parser.tab.o: $(BISON_OUT) $(BISON_H) $(SRCDIR)/ast.h $(SRCDIR)/symtab.h
$(SRCDIR)/ast.o:        $(SRCDIR)/ast.c $(SRCDIR)/ast.h
$(SRCDIR)/symtab.o:     $(SRCDIR)/symtab.c $(SRCDIR)/symtab.h
$(SRCDIR)/ast_walk.o:   $(SRCDIR)/ast_walk.c $(SRCDIR)/ast.h
$(SRCDIR)/main.o:       $(SRCDIR)/main.c $(SRCDIR)/ast.h $(SRCDIR)/symtab.h

## Remove arquivos gerados
clean:
	rm -f $(SRCDIR)/lex.yy.c $(SRCDIR)/parser.tab.c $(SRCDIR)/parser.tab.h
	rm -f $(SRCDIR)/*.o
	rm -f $(TARGET)
	@echo ">>> Limpeza concluída."

## Roda todos os testes
test: $(TARGET)
	@echo "=== Testes de programas VÁLIDOS ==="
	@passed=0; failed=0; \
	for f in tests/valid/*.lc; do \
	    printf "  %-40s " "$$f"; \
	    if ./$(TARGET) < "$$f" > /dev/null 2>&1; then \
	        echo "OK"; passed=$$((passed+1)); \
	    else \
	        echo "FALHOU"; failed=$$((failed+1)); \
	    fi; \
	done; \
	echo "  Resultado: $$passed OK, $$failed FALHOU"
	@echo ""
	@echo "=== Testes de programas INVÁLIDOS (devem falhar) ==="
	@passed=0; failed=0; \
	for f in tests/invalid/*.lc; do \
	    printf "  %-40s " "$$f"; \
	    if ./$(TARGET) < "$$f" > /dev/null 2>&1; then \
	        echo "DEVERIA TER FALHADO (erro!)"; failed=$$((failed+1)); \
	    else \
	        echo "Rejeitado (correto)"; passed=$$((passed+1)); \
	    fi; \
	done; \
	echo "  Resultado: $$passed rejeitados corretamente, $$failed com problema"

## Roda um exemplo simples e exibe a AST
ast: $(TARGET)
	@echo "=== AST do programa de exemplo ==="
	./$(TARGET) < tests/valid/01_hello.lc

## Ajuda
help:
	@echo "Alvos disponíveis:"
	@echo "  make         — compila e gera ./lara"
	@echo "  make clean   — remove arquivos gerados"
	@echo "  make test    — executa suite de testes"
	@echo "  make ast     — mostra AST do exemplo básico"
	@echo "  make help    — exibe esta mensagem"

# Makefile — Etapa 3 (Final) — INF01083/2026-1
TARGET  = compilador
SRCDIR  = src
CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c11 -D_POSIX_C_SOURCE=200809L -I$(SRCDIR)
FLEX    = flex
BISON   = bison

BISON_OUT = $(SRCDIR)/parser.tab.c
BISON_H   = $(SRCDIR)/parser.tab.h
FLEX_OUT  = $(SRCDIR)/lex.yy.c

C_SRCS = $(SRCDIR)/ast.c $(SRCDIR)/symtab.c $(SRCDIR)/ast_walk.c \
         $(SRCDIR)/tac.c $(SRCDIR)/codegen.c $(SRCDIR)/backpatch.c \
         $(SRCDIR)/asmgen.c $(SRCDIR)/optim.c $(SRCDIR)/main.c
ALL_SRCS = $(BISON_OUT) $(FLEX_OUT) $(C_SRCS)
OBJS = $(ALL_SRCS:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BISON_OUT) $(BISON_H): $(SRCDIR)/parser.y
	$(BISON) -d -o $(BISON_OUT) $(SRCDIR)/parser.y

$(FLEX_OUT): $(SRCDIR)/scanner.l $(BISON_H)
	env -i PATH="/usr/bin:/bin:/usr/local/bin:/opt/homebrew/bin" HOME="$${HOME}" TMPDIR="$${TMPDIR}" LANG="C" \
	    $(FLEX) -o $(FLEX_OUT) $(SRCDIR)/scanner.l

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/lex.yy.c $(SRCDIR)/parser.tab.c $(SRCDIR)/parser.tab.h
	rm -f $(SRCDIR)/*.o $(TARGET) etapa3
	rm -f _test.s _test_bin /tmp/_test_e3.s /tmp/_test_e3_bin

test: $(TARGET)
	@bash tests/run_tests.sh

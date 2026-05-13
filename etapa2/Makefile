# Makefile — Etapa 2 — INF01083/2026-1
TARGET  = lara
SRCDIR  = src
CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c11 -D_POSIX_C_SOURCE=200809L -I$(SRCDIR)
FLEX    = flex
BISON   = bison

BISON_OUT = $(SRCDIR)/parser.tab.c
BISON_H   = $(SRCDIR)/parser.tab.h
FLEX_OUT  = $(SRCDIR)/lex.yy.c

C_SRCS = $(SRCDIR)/ast.c $(SRCDIR)/symtab.c $(SRCDIR)/ast_walk.c \
         $(SRCDIR)/tac.c $(SRCDIR)/codegen.c $(SRCDIR)/main.c
ALL_SRCS = $(BISON_OUT) $(FLEX_OUT) $(C_SRCS)
OBJS = $(ALL_SRCS:.c=.o)


# Detecção de sistema operacional
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
    # macOS: workaround para bug do flex com PATH longo
    FLEX_ENV = env -i PATH="/usr/bin:/bin:/usr/local/bin:/opt/homebrew/bin" \
               HOME="$${HOME}" TMPDIR="$${TMPDIR}" LANG="C"
else
    FLEX_ENV =
endif
.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BISON_OUT) $(BISON_H): $(SRCDIR)/parser.y
	$(BISON) -d -o $(BISON_OUT) $(SRCDIR)/parser.y

$(FLEX_OUT): $(SRCDIR)/scanner.l $(BISON_H)
	$(FLEX_ENV) $(FLEX) -o $(FLEX_OUT) $(SRCDIR)/scanner.l

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/lex.yy.c $(SRCDIR)/parser.tab.c $(SRCDIR)/parser.tab.h
	rm -f $(SRCDIR)/*.o $(TARGET)

test: $(TARGET)
	@bash tests/run_tests.sh

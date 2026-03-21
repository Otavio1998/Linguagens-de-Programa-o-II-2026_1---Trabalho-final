#!/bin/bash
# run_tests.sh — Suite de testes automatizada da Etapa 1
#
# INF01083 — Linguagens de Programação II / Compiladores — 2026/1
# UFRGS / INF — Prof. Nicolas Maillard
#
# Uso:
#   bash tests/run_tests.sh        (a partir da raiz do projeto)
#
# Saída:
#   Relatório por teste e resumo final.
#   Código de saída 0 se todos passaram, 1 se algum falhou.
#
# Nota: este script deve ser executado a partir do diretório etapa1/
#   (o mesmo diretório onde está o Makefile).

set -e

# ------------------------------------------------------------
# 1. Compilar o projeto
# ------------------------------------------------------------
echo "=== Compilando o projeto ==="
if ! make 2>&1; then
    echo "ERRO FATAL: compilação falhou. Abortando testes."
    exit 1
fi
echo ""

if [ ! -x "./lara" ]; then
    echo "ERRO FATAL: binário './lara' não encontrado após compilação."
    exit 1
fi

# ------------------------------------------------------------
# Contadores globais
# ------------------------------------------------------------
total_ok=0
total_fail=0

# ------------------------------------------------------------
# 2. Testes de programas VÁLIDOS (devem retornar 0)
# ------------------------------------------------------------
echo "=== Testes de programas VÁLIDOS (devem ser aceitos) ==="

valid_dir="tests/valid"
if [ ! -d "$valid_dir" ]; then
    echo "  Diretório '$valid_dir' não encontrado."
else
    for f in "$valid_dir"/*.lc; do
        [ -f "$f" ] || continue
        printf "  %-45s " "$f"
        if ./lara < "$f" > /dev/null 2>&1; then
            echo "OK"
            total_ok=$((total_ok + 1))
        else
            echo "FALHOU  <-- esperava sucesso"
            total_fail=$((total_fail + 1))
        fi
    done
fi

echo ""

# ------------------------------------------------------------
# 3. Testes de programas INVÁLIDOS (devem retornar != 0)
# ------------------------------------------------------------
echo "=== Testes de programas INVÁLIDOS (devem ser rejeitados) ==="

invalid_dir="tests/invalid"
if [ ! -d "$invalid_dir" ]; then
    echo "  Diretório '$invalid_dir' não encontrado."
else
    for f in "$invalid_dir"/*.lc; do
        [ -f "$f" ] || continue
        printf "  %-45s " "$f"
        if ./lara < "$f" > /dev/null 2>&1; then
            echo "DEVERIA TER FALHADO  <-- erro: programa inválido foi aceito"
            total_fail=$((total_fail + 1))
        else
            echo "Rejeitado (correto)"
            total_ok=$((total_ok + 1))
        fi
    done
fi

echo ""

# ------------------------------------------------------------
# 4. Resumo final
# ------------------------------------------------------------
total=$((total_ok + total_fail))
echo "========================================"
echo "  Total de testes : $total"
echo "  OK              : $total_ok"
echo "  Falharam        : $total_fail"
echo "========================================"

if [ "$total_fail" -eq 0 ]; then
    echo "  TODOS OS TESTES PASSARAM."
    exit 0
else
    echo "  $total_fail TESTE(S) FALHARAM."
    exit 1
fi

#!/usr/bin/env bash
# run_tests.sh — Suite de testes da Etapa 2
# INF01083 — Linguagens de Programação II / Compiladores — 2026/1

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPILER="$SCRIPT_DIR/../lara"

if [ ! -x "$COMPILER" ]; then
    echo "ERRO: compilador '$COMPILER' não encontrado. Execute 'make' primeiro."
    exit 1
fi

passed=0
failed=0

echo "=== Testes VÁLIDOS (TAC esperado) ==="
for f in "$SCRIPT_DIR/valid/"*.lc; do
    expected="${f%.lc}.expected"
    if [ ! -f "$expected" ]; then
        echo "PULANDO (sem .expected): $(basename $f)"
        continue
    fi
    "$COMPILER" < "$f" > /tmp/_actual_e2.txt 2>/dev/null
    if diff -q /tmp/_actual_e2.txt "$expected" > /dev/null 2>&1; then
        echo "OK: $(basename $f)"
        passed=$((passed + 1))
    else
        echo "FALHOU: $(basename $f)"
        diff /tmp/_actual_e2.txt "$expected" | head -15
        failed=$((failed + 1))
    fi
done

echo ""
echo "=== Testes INVÁLIDOS (devem rejeitar) ==="
for f in "$SCRIPT_DIR/invalid/"*.lc; do
    "$COMPILER" < "$f" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "OK (rejeitado): $(basename $f)"
        passed=$((passed + 1))
    else
        echo "FALHOU (deveria rejeitar): $(basename $f)"
        failed=$((failed + 1))
    fi
done

rm -f /tmp/_actual_e2.txt

echo ""
echo "=== Resultado: $passed passou(aram), $failed falhou(aram) ==="
[ $failed -eq 0 ] && exit 0 || exit 1

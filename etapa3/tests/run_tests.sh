#!/usr/bin/env bash
# run_tests.sh — Testes de execução da Etapa 3 (Final)
# INF01083 — Linguagens de Programação II / Compiladores — 2026/1
#
# Para cada programa .lc em tests/valid/:
#   1. Compila para assembly: ./compilador < prog.lc > _test.s
#   2. Monta e linka:         gcc _test.s -o _test_bin -no-pie
#   3. Executa e compara saída com .expected
#
# Dica de depuração: ./compilador -tac < prog.lc  (imprime TAC em vez de asm)
#
# Nota: os testes de execução requerem Linux x86-64 com gcc.
# Em macOS, apenas a geração de assembly é verificada (execução é pulada).

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
COMPILER="$SCRIPT_DIR/../compilador"

if [ ! -x "$COMPILER" ]; then
    echo "ERRO: '$COMPILER' não encontrado. Execute 'make' primeiro."
    exit 1
fi

passed=0
failed=0
skipped=0

LINUX=0
[[ "$(uname)" == "Linux" ]] && LINUX=1

echo "=== Testes VÁLIDOS (execução) ==="
for f in "$SCRIPT_DIR/valid/"*.lc; do
    base="${f%.lc}"
    expected="${base}.expected"
    name="$(basename "$f")"

    if [ ! -f "$expected" ]; then
        echo "PULANDO (sem .expected): $name"
        continue
    fi

    # Gera assembly
    "$COMPILER" < "$f" > /tmp/_test_e3.s 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "FALHOU (compilação): $name"
        failed=$((failed+1))
        continue
    fi

    if [ "$LINUX" -eq 0 ]; then
        echo "SKIP (execução requer Linux): $name"
        skipped=$((skipped+1))
        continue
    fi

    # Monta e linka
    gcc /tmp/_test_e3.s -o /tmp/_test_e3_bin -no-pie 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "FALHOU (link/montagem): $name"
        failed=$((failed+1))
        continue
    fi

    # Executa e compara
    actual=$(/tmp/_test_e3_bin 2>/dev/null)
    expected_val=$(cat "$expected")

    if [ "$actual" = "$expected_val" ]; then
        echo "OK: $name"
        passed=$((passed+1))
    else
        echo "FALHOU: $name"
        echo "  esperado: $(printf '%s' "$expected_val" | head -5)"
        echo "  obtido:   $(printf '%s' "$actual"       | head -5)"
        failed=$((failed+1))
    fi
    rm -f /tmp/_test_e3_bin
done

echo ""
echo "=== Testes INVÁLIDOS (devem rejeitar) ==="
for f in "$SCRIPT_DIR/invalid/"*.lc; do
    name="$(basename "$f")"
    "$COMPILER" < "$f" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "OK (rejeitado): $name"
        passed=$((passed+1))
    else
        echo "FALHOU (deveria rejeitar): $name"
        failed=$((failed+1))
    fi
done

rm -f /tmp/_test_e3.s

echo ""
echo "=== Resultado: $passed OK  $failed FALHOU  $skipped SKIP ==="
[ "$failed" -eq 0 ]

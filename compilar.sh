#!/bin/bash
# ============================================================================
# Script de compilación rápida para métodos numéricos
# ============================================================================

echo "🔨 COMPILANDO MÉTODOS NUMÉRICOS..."
echo "=================================="

cd "Diferenciacion Numerica/Ecuaciones Diferenciales" 2>/dev/null || {
    echo "Error: No se encontró el directorio. Ejecuta desde la raíz del proyecto."
    exit 1
}

ERRORES=0

# Compilar RK4
echo -n "  RK4.cpp... "
if g++ -g -o rk4 Rk4.cpp -lm 2>/dev/null; then
    echo "✓"
else
    echo "✗"
    ERRORES=$((ERRORES + 1))
fi

# Compilar Euler
echo -n "  Euler.cpp... "
if g++ -g -o euler Euler.cpp -lm 2>/dev/null; then
    echo "✓"
else
    echo "✗"
    ERRORES=$((ERRORES + 1))
fi

# Compilar Heun
echo -n "  Heun.cpp... "
if g++ -g -o heun Heun.cpp -lm 2>/dev/null; then
    echo "✓"
else
    echo "✗"
    ERRORES=$((ERRORES + 1))
fi

cd "../.." 2>/dev/null

# Compilar Graficador
echo -n "  Graficador.cpp... "
if g++ -std=c++17 -o Graficador Graficador.cpp 2>/dev/null; then
    echo "✓"
else
    echo "✗"
    ERRORES=$((ERRORES + 1))
fi

echo "=================================="

if [ $ERRORES -eq 0 ]; then
    echo "✅ Compilación exitosa"
    echo ""
    echo "Para comenzar:"
    echo "  1. Ejecutar un método: ./Diferenciacion\\ Numerica/Ecuaciones\\ Diferenciales/rk4"
    echo "  2. Graficar resultados: ./Graficador"
else
    echo "❌ Se encontraron errores de compilación ($ERRORES)"
    exit 1
fi

#include <stdio.h>
#include <math.h>

/**
 * MÉTODO DE PUNTO FIJO - TRANSFORMACIÓN f(x) = 0 → x = g(x)
 * ==========================================================
 * 
 * CÓMO OBTENER g(x) A PARTIR DE f(x):
 * 
 * Si tienes f(x) = 0 y necesitas g(x) para x = g(x), usa una de estas estrategias:
 * 
 * MÉTODO 1: DESPEJE DIRECTO
 * -------------------------
 * Ejemplo: f(x) = x² - 4 = 0
 * Despejamos: x² = 4  →  x = ±√4  →  g(x) = √4 = 2 (raíz positiva)
 *                                   g(x) = -√4 = -2 (raíz negativa)
 * 
 * Ejemplo: f(x) = cos(x) - x = 0
 * Despejamos: cos(x) = x  →  g(x) = cos(x)
 * 
 * Ejemplo: f(x) = e^x - 2x = 0
 * Despejamos: e^x = 2x  →  x = e^x/2  →  g(x) = e^x/2
 *       o bien: e^x = 2x  →  x = ln(2x)  →  g(x) = ln(2x)
 * 
 * MÉTODO 2: FÓRMULA GENERAL (SIEMPRE FUNCIONA)
 * --------------------------------------------
 * g(x) = x - λ*f(x)    donde λ es un factor pequeño (0.01 a 0.5)
 * 
 * Esta fórmula SIEMPRE transforma f(x) = 0 en x = g(x)
 * Si |f'(x)| es grande, usar λ pequeño (ej: 0.01)
 * Si |f'(x)| es pequeño, usar λ más grande (ej: 0.3)
 * 
 * Ejemplo: f(x) = x² - 4
 * g(x) = x - λ(x² - 4) = x - λx² + 4λ
 * Con λ = 0.1: g(x) = x - 0.1x² + 0.4
 * 
 * MÉTODO 3: TRANSFORMACIONES ESPECÍFICAS
 * --------------------------------------
 * • Para f(x) = x² - a:     g(x) = √a  o  g(x) = a/x
 * • Para f(x) = x³ - a:     g(x) = ∛a  o  g(x) = (x² + a)/x
 * • Para f(x) = ax + b:     g(x) = -b/a (constante)
 * • Para f(x) = e^x - a:    g(x) = ln(a)
 * • Para f(x) = ln(x) - a:  g(x) = e^a
 * 
 * CRITERIO DE CONVERGENCIA:
 * Para que converja, debe cumplirse |g'(x)| < 1 cerca de la raíz
 * 
 * EJEMPLOS COMUNES:
 * ================
 * 
 * 1. f(x) = x² - 2  (encontrar √2)
 *    g(x) = √2 = 1.414...  (constante)
 *    o g(x) = 2/x           (variable)
 * 
 * 2. f(x) = x² - 4  (encontrar ±2)
 *    g(x) = 2      (para raíz positiva)
 *    g(x) = -2     (para raíz negativa)
 *    g(x) = 4/x    (converge a ambas según punto inicial)
 * 
 * 3. f(x) = x³ - 8  (encontrar ∛8 = 2)
 *    g(x) = ∛8 = 2           (constante)
 *    g(x) = ∛(8) = (8)^(1/3) (constante)
 * 
 * 4. f(x) = cos(x) - x  (encontrar punto donde cos(x) = x)
 *    g(x) = cos(x)
 * 
 * 5. f(x) = e^(-x) - x  (encontrar punto donde e^(-x) = x)
 *    g(x) = e^(-x)
 * 
 * INSTRUCCIONES PARA CAMBIAR LA FUNCIÓN:
 * ======================================
 * 1. Modifica la función g(x) abajo usando una de las estrategias anteriores
 * 2. Si no sabes cómo despejar, usa: g(x) = x - λ*f(x) con λ = 0.1
 * 3. Prueba diferentes valores de λ si no converge
 */

double g(double);
void PuntoFijo();

int main()
{
    PuntoFijo();
    return 0;
}

/**
 * FUNCIÓN g(x) - MODIFICAR AQUÍ
 * =============================
 * Función actual: g(x) = e^(-x)
 * Corresponde a: f(x) = e^(-x) - x = 0
 * 
 * Para cambiar la función, reemplaza "return x*x-0.5or:
 * 
 * EJEMPLOS LISTOS PARA USAR:
 * return 2;                    // Para f(x) = x² - 4, raíz positiva
 * return -2;                   // Para f(x) = x² - 4, raíz negativa  
 * return 4/x;                  // Para f(x) = x² - 4, converge a ±2
 * return sqrt(2);              // Para f(x) = x² - 2, √2 ≈ 1.414
 * return 2/x;                  // Para f(x) = x² - 2, converge a ±√2
 * return cos(x);               // Para f(x) = cos(x) - x
 * return exp(x)/2;             // Para f(x) = e^x - 2x
 * return log(2*x);             // Para f(x) = e^x - 2x (alternativa)
 * return pow(x+1, 1.0/3.0);    // Para f(x) = x³ - x - 1
 * 
 * FÓRMULA GENERAL (SIEMPRE FUNCIONA):
 * return x - 0.1*f(x);         // Donde f(x) es tu función original
 */
double g(double x)
{ 
    return exp(-x);  // ← CAMBIAR ESTA LÍNEA
    
    /* FUNCIÓN f(x) CORRESPONDIENTE (solo para referencia):
     * Para g(x) = e^(-x), f(x) es: f(x) = e^(-x) - x
     * 
     * Si cambias g(x), asegúrate de que corresponda a tu f(x) deseada:
     * - Si tienes f(x) = x² - 4, usa g(x) = 2 o g(x) = 4/x
     * - Si tienes f(x) = cos(x) - x, usa g(x) = cos(x)
     * - Si no sabes, usa g(x) = x - λ*f(x) con λ pequeño
     */
}

/**
 * FUNCIÓN f(x) IMPLÍCITA
 * ======================
 * Esta función no se usa en el algoritmo, pero te ayuda a verificar
 * que g(x) es correcta. Para g(x) = x*x-0.5x) sería:
 */
double f_verificacion(double x) {
    return exp(-x) - x;  // f(x) = e^(-x) - x
    /* OTROS EJEMPLOS:
     * return x*x - 4;              // Para g(x) = 2 o g(x) = 4/x
     * return x*x - 2;              // Para g(x) = sqrt(2) o g(x) = 2/x
     * return cos(x) - x;           // Para g(x) = cos(x)
     * return exp(x) - 2*x;         // Para g(x) = exp(x)/2
     */
}

void PuntoFijo()
{
    double xViejo;
    double xNuevo;
    int contador = 0;
    double error = 0;
    double tolerancia;
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    MÉTODO DE PUNTO FIJO                      ║\n");
    printf("║                                                              ║\n");
    printf("║  Función actual: g(x) = e^(-x)                               ║\n");
    printf("║  Busca raíz de: f(x) = e^(-x) - x = 0                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Ingrese la tolerancia (ej: 0.0001): "); 
    scanf("%lf", &tolerancia);
    printf("Ingrese el punto inicial (ej: 0.5): "); 
    scanf("%lf", &xViejo);
    
    printf("\n┌─────────────────────────────────────────────────────────────┐\n");
    printf("│  Iter  │    x_i     │   g(x_i)   │    Error   │ |g'(x)| │\n");
    printf("├─────────────────────────────────────────────────────────────┤\n");
    
    do
    {
        contador++;

        // Verificar criterio de convergencia |g'(x)| < 1
        double derivada = fabs((g(xViejo + 0.01) - g(xViejo)) / 0.01);
        
        if (derivada >= 1) 
        { 
            printf("│  %2d    │     -      │     -      │     -      │ %.4f │\n", 
                   contador, derivada);
            printf("└─────────────────────────────────────────────────────────────┘\n");
            printf("\n❌ NO CONVERGE: |g'(x)| = %.4f ≥ 1\n", derivada);
            printf("\n💡 SOLUCIONES:\n");
            printf("   • Cambiar el punto inicial\n");
            printf("   • Usar g(x) = x - λ*f(x) con λ pequeño (ej: 0.1)\n");
            printf("   • Verificar que g(x) corresponde a tu f(x)\n");
            break;
        }
        else
        {
            xNuevo = g(xViejo);
            error = fabs(xNuevo - xViejo);
            
            printf("│  %2d    │ %10.6f │ %10.6f │ %.2e │ %.4f │\n", 
                   contador, xViejo, xNuevo, error, derivada);
            
            xViejo = xNuevo;
        }

        // Límite de seguridad
        if (contador > 50) {
            printf("└─────────────────────────────────────────────────────────────┘\n");
            printf("\n⚠️  Límite de 50 iteraciones alcanzado\n");
            break;
        }

    } while (error > tolerancia);

    if (error <= tolerancia) {
        printf("└─────────────────────────────────────────────────────────────┘\n");
        printf("\n✅ CONVERGENCIA EXITOSA!\n");
        printf("📍 Punto fijo encontrado: x* = %.10lf\n", xNuevo);
        printf("🔍 Verificación f(x*) = %.2e ≈ 0\n", f_verificacion(xNuevo));
        printf("📊 Error final: %.2e\n", error);
        printf("🔢 Iteraciones: %d\n", contador);
    }
    
    printf("\n📋 Presione Enter para continuar...\n");
    getchar(); getchar();
}
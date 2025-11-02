#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * MÉTODO DE NEWTON-RAPHSON PARA LOCALIZACIÓN DE RAÍCES
 * ===================================================
 * 
 * Para cambiar la función, modifique los métodos f(x) y fPrima(x)
 * directamente en el código fuente.
 * 
 * Función actual: f(x) = x² - 4
 * Derivada actual: f'(x) = 2x
 * Raíz esperada: x = 2 (o x = -2)
 */

class NewtonRapson {
private:
    double xViejo = 0.0;
    double error = 0.0;
    double tolerancia = 0.0;
    double xNuevo = 0.0;
    int contador = 0;

    /**
     * Función objetivo f(x)
     * MODIFICAR AQUÍ LA FUNCIÓN A EVALUAR
     */
    double f(double x) {
        return x * x - 4;  // f(x) = x² - 4
        
        // Otros ejemplos:
        // return x * x * x - 2 * x + 1;           // f(x) = x³ - 2x + 1
        // return 2 * x * x + 3 * x - 1;           // f(x) = 2x² + 3x - 1
        // return sin(x) - 0.5;                    // f(x) = sen(x) - 0.5
        // return exp(x) - 2;                      // f(x) = eˣ - 2
        // return x / (x + 1) - 0.5;               // f(x) = x/(x+1) - 0.5
        // return 3.0 / pow(x + 4, 2) - 0.25;      // f(x) = 3/(x+4)² - 0.25
    }

    /**
     * Derivada de la función objetivo f'(x)
     * MODIFICAR AQUÍ LA DERIVADA CORRESPONDIENTE
     */
    double fPrima(double x) {
        return 2 * x;  // f'(x) = 2x para f(x) = x² - 4
        
        // Derivadas correspondientes a los ejemplos anteriores:
        // return 3 * x * x - 2;                   // f'(x) = 3x² - 2
        // return 4 * x + 3;                       // f'(x) = 4x + 3
        // return cos(x);                          // f'(x) = cos(x)
        // return exp(x);                          // f'(x) = eˣ
        // return 1.0 / pow(x + 1, 2);             // f'(x) = 1/(x+1)²
        // return -6.0 / pow(x + 4, 3);            // f'(x) = -6/(x+4)³
    }

    /**
     * Error porcentual según fórmula del enunciado
     */
    double errorPorcentual(double xNuevo, double xViejo) {
        if (abs(xNuevo + xViejo) < 1e-12) return 0.0; // Evitar división por cero
        return abs(xNuevo - xViejo) / abs(xNuevo + xViejo) * 100.0;
    }

    /**
     * Error exacto respecto a la raíz real = 2
     * MODIFICAR si la raíz exacta es diferente
     */
    double errorExacto(double xAproximado) {
        return abs(xAproximado - 2.0);  // Raíz exacta = 2 para x² - 4 = 0
    }

public:
    /**
     * Método que implementa el algoritmo de Newton-Raphson
     */
    void newtonRaphson() {
        cout << "=== MÉTODO DE NEWTON-RAPHSON ===" << endl;
        cout << "Función: f(x) = x² - 4" << endl;
        cout << "Derivada: f'(x) = 2x" << endl;
        
        cout << "\nIngrese la tolerancia: ";
        cin >> tolerancia;
        
        cout << "Ingrese el punto inicial: ";
        cin >> xViejo;
        
        cout << "\nPunto inicial: x₀ = " << xViejo << endl;
        cout << "Tolerancia: " << tolerancia << endl;
        cout << "\n--- ITERACIONES ---" << endl;
        
        // Realizar iteraciones
        do {
            contador++;
            
            if (abs(fPrima(xViejo)) < 1e-10) {
                cout << "\n⚠️  DERIVADA PEQUEÑA - POSIBLE PROBLEMA DE CONVERGENCIA" << endl;
                break;
            }
            
            xNuevo = xViejo - (f(xViejo) / fPrima(xViejo));
            
            double errorEstimado = errorPorcentual(xNuevo, xViejo);
            double errorExactoVal = errorExacto(xNuevo);
            
            // Mostrar información de cada iteración
            cout << "Iteración " << contador << ":" << endl;
            cout << "  f(x" << (contador-1) << ") = " << scientific << setprecision(6) << f(xViejo) << endl;
            cout << "  f'(x" << (contador-1) << ") = " << scientific << setprecision(6) << fPrima(xViejo) << endl;
            cout << "  x" << contador << " = " << fixed << setprecision(10) << xNuevo << endl;
            
            // Mostrar detalles en la cuarta iteración
            if (contador == 4) {
                cout << "\n--- RESULTADOS ITERACIÓN 4 ---" << endl;
                cout << "  x₄ = " << fixed << setprecision(10) << xNuevo << endl;
                cout << "  Error estimado (%) = " << fixed << setprecision(6) << errorEstimado << "%" << endl;
                cout << "  Error exacto = " << fixed << setprecision(6) << errorExactoVal << endl;
            }
            
            error = abs(xNuevo - xViejo);
            xViejo = xNuevo;
            cout << endl;
            
        } while (error > tolerancia && contador < 100); // Límite de seguridad
        
        // Mostrar resultados finales
        cout << "\n=== RESULTADOS FINALES ===" << endl;
        cout << "✓ Raíz encontrada: x = " << fixed << setprecision(10) << xNuevo << endl;
        cout << "✓ Error final: " << scientific << setprecision(6) << error << endl;
        cout << "✓ Iteraciones: " << contador << endl;
        cout << "✓ Verificación: f(" << fixed << setprecision(6) << xNuevo << ") = " 
            << scientific << setprecision(6) << f(xNuevo) << endl;
        
        // Determinar si convergió
        if (error <= tolerancia) {
            cout << "✓ CONVERGENCIA EXITOSA" << endl;
        } else {
            cout << "⚠️  NO CONVERGIÓ EN " << contador << " ITERACIONES" << endl;
        }
    }
};

int main() {
    NewtonRapson nr;
    nr.newtonRaphson();
    return 0;
}
#include <cmath>
#include <iostream>
#include <iomanip>
#define L 4
#define T0 100
#define T1 20
#define Tt 60
#define t 10

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
    double xViejo = 0.05;
    double error = 0.0;
    double tolerancia = 1e-5;
    double xNuevo = 0.0;
    int contador = 0;

    /**
     * Función objetivo f(x)
     * MODIFICAR AQUÍ LA FUNCIÓN A EVALUAR
     */
    double f(double x) {
        return ( (L*L/(x*(M_PI*M_PI))) * log((T0 - T1)/(Tt - T1)) ) - 10;
    }

    /**
     * Derivada de la función objetivo f'(x)
     * MODIFICAR AQUÍ LA DERIVADA CORRESPONDIENTE
     */
    double fPrima(double x) {
        return - ( (L*L/(x*x*(M_PI*M_PI))) * log((T0 - T1)/(Tt - T1)) ) ;
        
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
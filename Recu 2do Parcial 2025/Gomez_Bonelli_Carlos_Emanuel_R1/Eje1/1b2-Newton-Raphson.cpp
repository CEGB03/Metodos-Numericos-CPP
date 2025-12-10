#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class NewtonRapson {
private:
    double xViejo = 0.0;
    double error = 0.0;
    double tolerancia = 0.0;
    double xNuevo = 0.0;
    int contador = 0;

    /**
     * Función objetivo f(x) = ln(x² + 1) - sin(x)
     */
    double f(double x) {
        return log(x * x + 1) - sin(x);
    }

    /**
     * Derivada de la función objetivo f'(x) = (2x)/(x²+1) - cos(x)
     */
    double fPrima(double x) {
        return (2 * x) / (x * x + 1) - cos(x);
    }

    /**
     * Error porcentual según fórmula del enunciado
     */
    double errorPorcentual(double xNuevo, double xViejo) {
        if (abs(xNuevo + xViejo) < 1e-12) return 0.0;
        return abs(xNuevo - xViejo) / abs(xNuevo + xViejo) * 100.0;
    }

public:
    /**
     * Método que implementa el algoritmo de Newton-Raphson
     */
    void newtonRaphson() {
        cout << "=== MÉTODO DE NEWTON-RAPHSON ===" << endl;
        cout << "Función: f(x) = ln(x² + 1) - sin(x)" << endl;
        cout << "Derivada: f'(x) = (2x)/(x²+1) - cos(x)" << endl;
        
        /* 
        cout << "\nIngrese la tolerancia: ";
        cin >> tolerancia;
        cout << "Ingrese el punto inicial: ";
        cin >> xViejo; */
        tolerancia = 1e-6;
        xViejo = 1;
        
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
            double errorAbsoluto = abs(xNuevo - xViejo);
            
            // Mostrar información de cada iteración
            cout << "Iteración " << contador << ":" << endl;
            cout << "  f(x" << (contador-1) << ") = " << scientific << setprecision(6) << f(xViejo) << endl;
            cout << "  f'(x" << (contador-1) << ") = " << scientific << setprecision(6) << fPrima(xViejo) << endl;
            cout << "  x" << contador << " = " << fixed << setprecision(10) << xNuevo << endl;
            cout << "  Error absoluto = " << fixed << setprecision(6) << errorAbsoluto << endl;
            
            // Mostrar detalles en la cuarta iteración
            if (contador == 4) {
                cout << "\n--- RESULTADOS ITERACIÓN 4 ---" << endl;
                cout << "  x₄ = " << fixed << setprecision(10) << xNuevo << endl;
                cout << "  Error estimado = " << fixed << setprecision(6) << errorEstimado << endl;
                cout << "  Error absoluto = " << fixed << setprecision(6) << errorAbsoluto << endl;
                cout << "  Error porcentual = " << fixed << setprecision(6) << errorEstimado << "%" << endl;
            }
            
            error = abs(xNuevo - xViejo);
            xViejo = xNuevo;
            cout << endl;
            
        } while (error > tolerancia && contador < 100);
        
        // Mostrar resultados finales
        cout << "\n=== RESULTADOS FINALES ===" << endl;
        cout << "✓ Raíz encontrada: x = " << fixed << setprecision(10) << xNuevo << endl;
        cout << "✓ Error final: " << scientific << setprecision(6) << error << endl;
        cout << "✓ Iteraciones: " << contador << endl;
        cout << "✓ Verificación: f(" << fixed << setprecision(6) << xNuevo << ") = " 
            << scientific << setprecision(6) << f(xNuevo) << endl;
        
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
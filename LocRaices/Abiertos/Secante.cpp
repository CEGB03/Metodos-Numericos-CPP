#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * METODO DE LA SECANTE
 * ====================
 * Variante sin derivada explícita. Requiere dos puntos iniciales distintos.
 * Cambia la función f(x) directamente en el método f.
 */
class Secante {
private:
    double xPrev = 0.0;   // x_{i-1}
    double xCurr = 0.0;   // x_i
    double xNext = 0.0;   // x_{i+1}
    double error = 0.0;   // |x_{i+1} - x_i|
    double tolerancia = 0.0;
    int contador = 0;
    const int maxIter = 100;

    // Función objetivo f(x) (modificar aquí)
    double f(double x) {
        return x * x - 4.0;  // f(x) = x^2 - 4 (raices en ±2)

        // Otros ejemplos:
        // return x * x * x - 2 * x + 1;           // f(x) = x^3 - 2x + 1
        // return 2 * x * x + 3 * x - 1;           // f(x) = 2x^2 + 3x - 1
        // return sin(x) - 0.5;                    // f(x) = sen(x) - 0.5
        // return exp(x) - 2;                      // f(x) = e^x - 2
    }

    // Error relativo porcentual (para reporte)
    double errorPorcentual(double nuevo, double viejo) {
        if (fabs(nuevo) < 1e-12) return 0.0;
        return fabs(nuevo - viejo) / fabs(nuevo) * 100.0;
    }

public:
    void secante() {
        cout << "=== METODO DE LA SECANTE ===" << endl;
        cout << "Funcion: f(x) = x^2 - 4" << endl;

        cout << "\nIngrese la tolerancia: ";
        cin >> tolerancia;

        cout << "Ingrese el primer punto inicial (x_{i-1}): ";
        cin >> xPrev;

        cout << "Ingrese el segundo punto inicial (x_i): ";
        cin >> xCurr;

        if (fabs(xCurr - xPrev) < 1e-12) {
            cout << "⚠️  Los puntos iniciales deben ser distintos. Ajustando x_i = x_{i-1} + 0.1" << endl;
            xCurr = xPrev + 0.1;
        }

        cout << "\n--- ITERACIONES ---" << endl;
        cout << left << setw(6) << "Iter" << setw(15) << "x_{i-1}" << setw(15) << "x_i" << setw(15)
             << "x_{i+1}" << setw(15) << "f(x_i)" << setw(15) << "Error" << "Err(%)" << endl;
        cout << string(80, '-') << endl;

        do {
            contador++;

            double fPrev = f(xPrev);
            double fCurr = f(xCurr);

            if (fabs(fPrev - fCurr) < 1e-12) {
                cout << "⚠️  Division por cero en la formula de secante (f(x_{i-1}) ≈ f(x_i))." << endl;
                break;
            }

            xNext = xCurr - fCurr * (xPrev - xCurr) / (fPrev - fCurr);
            error = fabs(xNext - xCurr);
            double errPct = errorPorcentual(xNext, xCurr);

            cout << left << setw(6) << contador
                 << setw(15) << fixed << setprecision(8) << xPrev
                 << setw(15) << xCurr
                 << setw(15) << xNext
                 << setw(15) << scientific << setprecision(6) << fCurr
                 << setw(15) << fixed << setprecision(6) << error
                 << fixed << setprecision(4) << errPct << endl;

            xPrev = xCurr;
            xCurr = xNext;

            if (fabs(f(xCurr)) < 1e-15) break;  // raiz exacta

        } while (error > tolerancia && contador < maxIter);

        cout << string(80, '-') << endl;
        cout << "Raiz aproximada: x = " << fixed << setprecision(10) << xCurr << endl;
        cout << "Error final: " << scientific << setprecision(6) << error << endl;
        cout << "Iteraciones: " << contador << endl;
        cout << "Verificacion: f(x) = " << scientific << setprecision(6) << f(xCurr) << endl;

        if (error <= tolerancia) {
            cout << "✓ CONVERGENCIA EXITOSA" << endl;
        } else if (contador >= maxIter) {
            cout << "⚠️  NO CONVERGIO EN EL LIMITE DE ITERACIONES" << endl;
        }
    }
};

int main() {
    Secante s;
    s.secante();
    return 0;
}

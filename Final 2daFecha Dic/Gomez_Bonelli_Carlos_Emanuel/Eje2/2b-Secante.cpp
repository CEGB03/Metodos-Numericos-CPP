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

    // Función polinómica a evaluar
    double funPolonomio(double x) {
        // Polinomio interpolado 2a:
        // 20*x^3 - 46*x^2 + 28*x + 20 = 0
        return 20*x*x*x - 46*x*x + 28*x + 20;
    }

    // Función objetivo f(x) (modificar aquí)
    double f(double x) {
        return funPolonomio(x)-( (x*x) + 2*x + 23 );  // f(x) = P(x) - ((x^2 + 2x + 23))
    }

    // Error relativo porcentual (para reporte)
    double errorPorcentual(double nuevo, double viejo) {
        if (fabs(nuevo) < 1e-12) return 0.0;
        return fabs(nuevo - viejo) / fabs(nuevo) * 100.0;
    }

public:
    void secante() {
        cout << "=== METODO DE LA SECANTE ===" << endl;
        cout << "Funcion: f(x) = 20*x^3 - 46*x^2 + 28*x + 20 - (x^2 + 2*x + 23)" << endl;

        cout << "\nIngrese la tolerancia: ";
        //cin >> tolerancia;
        tolerancia = 1e-5;

        cout << "Ingrese el primer punto inicial (x_{i-1}): ";
        //cin >> xPrev;
        xPrev = 0;

        cout << "Ingrese el segundo punto inicial (x_i): ";
        //cin >> xCurr;
        xCurr = 0.5;
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
        //cout << "Raiz aproximada: x = " << fixed << setprecision(10) << xCurr << endl;
        cout << "Raiz aproximada: x = ";
        printf("%.10f\n", xCurr);
        //cout << "rror absoluto final: " << fixed << setprecision(10) << error << endl;
        cout << "Error absoluto final: ";
        printf("%.10f\n", error);
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

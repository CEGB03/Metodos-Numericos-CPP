#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double funcion(double x);

void regulaFalsi();

int main() {
    regulaFalsi();
    return 0;
}

double funcion(double x) {
    return log(x*x + 1) - sin(x);
}

void regulaFalsi() {
    double a = 1.2, b = 1.5;
    double tolerancia = 0.0001;
    double c, error, c_anterior, errorEstimado;
    int iteraciones = 5;

    cout << "=== MÉTODO DE FALSA POSICIÓN - ITERACIÓN 5 ===" << endl;
    cout << "Función: f(x) = ln(x² + 1) - sin(x)" << endl;
    cout << "Intervalo: [" << a << ", " << b << "]" << endl;
    cout << "Iteraciones a realizar: " << iteraciones << endl;
    cout << endl;
    
    cout << setw(4) << "Iter" << setw(12) << "a" << setw(12) << "b" 
        << setw(12) << "c" << setw(15) << "f(c)" << setw(12) << "Error" << endl;
    cout << "------------------------------------------------------------" << endl;

    if (funcion(a) * funcion(b) < 0.0) {
        for (int contador = 1; contador <= iteraciones; contador++) {
            c = (a * funcion(b) - b * funcion(a)) / (funcion(b) - funcion(a));
            
            if (contador > 1) {
                error = fabs(c - c_anterior);
            } else {
                error = fabs(b - a);
            }
            
            cout << setw(4) << contador << setw(12) << fixed << setprecision(6) << a 
                << setw(12) << b << setw(12) << c << setw(15) << funcion(c) 
                << setw(12) << error << endl;
            
            if (funcion(a) * funcion(c) > 0) {
                a = c;
            } else {
                b = c;
            }
            

            if (fabs(c_anterior) > 1e-10) {  // Evitar división por cero
                errorEstimado = fabs((c - c_anterior) / c_anterior);
            } else {
                errorEstimado = fabs(c - c_anterior);  // Fallback a error absoluto
            }

            c_anterior = c;
            
            if (contador == 5) {
                cout << "\n--- RESULTADOS ITERACIÓN 5 ---" << endl;
                cout << "Raíz aproximada: " << fixed << setprecision(8) << c << endl;
                cout << "Error estimado: " << fixed << setprecision(8) << errorEstimado << endl;
                cout << "f(" << c << ") = " << fixed << setprecision(8) << funcion(c) << endl;
            }
        }
    } else {
        cout << "No hay raíz en el intervalo" << endl;
    }
}
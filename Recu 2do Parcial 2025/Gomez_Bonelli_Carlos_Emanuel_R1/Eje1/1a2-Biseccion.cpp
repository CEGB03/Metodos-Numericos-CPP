#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double funcion(double x);
void biseccion();

int main() {
    biseccion();
    return 0;
}

double funcion(double x) {
    return log(x*x + 1) - sin(x);
}

void biseccion() {
    double a = 1.0, b = 2.0;
    int iteraciones = 10; // Exactamente 10 iteraciones
    
    cout << "MÉTODO DE BISECCIÓN - 10 ITERACIONES" << endl;
    cout << "Función: ln(x² + 1) - sin(x)" << endl;
    cout << "Intervalo inicial: [" << a << ", " << b << "]" << endl;
    cout << endl;
    cout << setw(4) << "Iter" << setw(12) << "a" << setw(12) << "b" 
        << setw(12) << "c" << setw(15) << "f(c)" << setw(12) << "Error" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    if (funcion(a) * funcion(b) < 0.0) {
        double c, error;
        
        for (int i = 1; i <= iteraciones; i++) {
            c = (a + b) / 2.0;
            error = (b - a) / 2.0;
            
            cout << setw(4) << i << setw(12) << fixed << setprecision(6) << a 
                << setw(12) << b << setw(12) << c << setw(15) << funcion(c) 
                << setw(12) << error << endl;
            
            if (funcion(a) * funcion(c) > 0) {
                a = c;
            } else {
                b = c;
            }
        }
        
        cout << "\nRESULTADOS ITERACIÓN 10:" << endl;
        cout << "Raíz aproximada: " << fixed << setprecision(8) << c << endl;
        cout << "Error estimado: " << fixed << setprecision(8) << error << endl;
        
    } else {
        cout << "No hay raíz en el intervalo o hay un número par de raíces" << endl;
    }
}
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x) {
    return sqrt(1 + x*x);
}

void tablaDerivadas() {
    cout << "=== TABLA DE DERIVADAS [0,1] h=0.1 ===" << endl;
    cout << "x\tf'(x) aprox" << endl;
    cout << fixed << setprecision(4);
    
    double h = 0.1;
    
    // Primer punto (x=0) - diferencia hacia adelante
    double deriv_0 = (f(0+h) - f(0)) / h;
    cout << "0.0\t" << deriv_0 << endl;
    
    // Puntos internos (x=0.1 a 0.9) - diferencias centradas
    for(double x = 0.1; x <= 0.9; x += h) {
        double deriv = (f(x+h) - f(x-h)) / (2*h);
        cout << x << "\t" << deriv << endl;
    }
    
    // Último punto (x=1.0) - diferencia hacia atrás
    double deriv_1 = (f(1) - f(1-h)) / h;
    cout << "1.0\t" << deriv_1 << endl;
}

int main() {
    tablaDerivadas();
    return 0;
}
#include <iostream>
#include <cmath>
#include <iomanip>
#include "problema3.h"

using namespace std;

double f(double x, double y) {
    return y - x*x + 1;
}

double exacta(double x) {
    return pow(x + 1, 2) - 0.5 * exp(x);
}

void puntoMedio() {
    cout << "=== METODO DEL PUNTO MEDIO (h=0.2) ===" << endl;
    double x = 0, y = 0.5, h = 0.2;
    cout << fixed << setprecision(10);
    cout << "x0 = " << x << ", y0 = " << y << endl;
    double k1 = f(x, y);
    double x_medio = x + h/2;
    double y_medio = y + (h/2) * k1;
    double k2 = f(x_medio, y_medio);
    double y_next = y + h * k2;
    cout << "k1 = f(" << x << "," << y << ") = " << k1 << endl;
    cout << "x_medio = " << x_medio << ", y_medio = " << y_medio << endl;
    cout << "k2 = f(" << x_medio << "," << y_medio << ") = " << k2 << endl;
    cout << "y1 = " << y << " + " << h << " * " << k2 << " = " << y_next << endl;
    double error = fabs(exacta(x+h) - y_next);
    cout << "Valor exacto en x=0.2: " << exacta(0.2) << endl;
    cout << "Error absoluto: " << error << endl << endl;
}
int main(){
    // Inciso a)
    puntoMedio();

    return 0;
}

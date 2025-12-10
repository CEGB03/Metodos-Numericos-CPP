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

void RK4_38() {
    cout << "=== METODO RK4 3/8 (h=0.1) ===" << endl;
    double x = 0, y = 0.5, h = 0.1;
    int pasos_15 = 15, pasos_20 = 20; // para llegar a 1.5 y 2.0
    cout << fixed << setprecision(10);
    // Calcular hasta x=1.5
    for(int i = 0; i < pasos_15; i++) {
        double k1 = f(x, y);
        double k2 = f(x + h/3, y + h*k1/3);
        double k3 = f(x + 2*h/3, y - h*k1/3 + h*k2);
        double k4 = f(x + h, y + h*k1 - h*k2 + h*k3);
        y = y + (h/8)*(k1 + 3*k2 + 3*k3 + k4);
        x = x + h;
    }
    cout << "y(1.5) = " << y << endl;
    cout << "Exacto: " << exacta(1.5) << endl;
    cout << "Error: " << fabs(exacta(1.5) - y) << endl;
    // Calcular hasta x=2.0
    for(int i = 0; i < 5; i++) {
        double k1 = f(x, y);
        double k2 = f(x + h/3, y + h*k1/3);
        double k3 = f(x + 2*h/3, y - h*k1/3 + h*k2);
        double k4 = f(x + h, y + h*k1 - h*k2 + h*k3);
        y = y + (h/8)*(k1 + 3*k2 + 3*k3 + k4);
        x = x + h;
    }
    cout << "y(2.0) = " << y << endl;
    cout << "Exacto: " << exacta(2.0) << endl;
    cout << "Error: " << fabs(exacta(2.0) - y) << endl;
}
int main(){

    RK4_38();

    return 0;
}

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

void euler() {
    cout << "=== METODO DE EULER (h=0.2) ===" << endl;
    double x = 0, y = 0.5, h = 0.2;
    cout << fixed << setprecision(10);
    cout << "x0 = " << x << ", y0 = " << y << endl;
    double y_next = y + h * f(x, y);
    cout << "y1 = " << y << " + " << h << " * f(" << x << "," << y << ")" << endl;
    cout << "y1 = " << y << " + " << h << " * " << f(x,y) << endl;
    cout << "y1 = " << y_next << endl;
    double error = fabs(exacta(x+h) - y_next);
    cout << "Valor exacto en x=0.2: " << exacta(0.2) << endl;
    cout << "Error absoluto: " << error << endl << endl;
}
int main(){
    // Inciso a)
    euler();
    return 0;
}

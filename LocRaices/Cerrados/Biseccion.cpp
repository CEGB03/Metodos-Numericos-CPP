#include <iostream>
#include <cmath>

using namespace std;

double funcion(double x);
void biseccion();

int main() {
    biseccion();
    return 0;
}

double funcion(double x) {
    return log(x) + exp(sin(x)) - x;
}

void biseccion() {
    double a, b, tolerancia;
    int iterator = 0;

    cout << "Ingrese el límite inferior del intervalo: ";
    cin >> a;
    cout << "Ingrese el límite superior del intervalo: ";
    cin >> b;
    cout << "Ingrese la tolerancia: ";
    cin >> tolerancia;

    if (funcion(a) * funcion(b) < 0.0) {
        double c, error;

        do {
            c = (a + b) / 2;
            error = (b - a) / 2;

            if (funcion(a) * funcion(c) > 0) {
                a = c;
            } else if (funcion(a) * funcion(c) < 0) {
                b = c;
            } else {
                break;
            }

            iterator++;

        } while (error > tolerancia);

        cout << "\nResultado de la raíz: " << c << endl;
        cout << "Error estimado: " << error << endl;
        cout << "Cantidad de iteraciones: " << iterator << endl;

    } else {
        cout << "\nNo hay raíz o hay un número par de ellas\n";
    }
}
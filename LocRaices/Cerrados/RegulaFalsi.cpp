#include <stdio.h>
#include <math.h>

double funcion(double x);

void regulaFalsi();

int main() {

    regulaFalsi();

    return 0;
}

double funcion(double x) {

    return log(x) + exp(sin(x)) - x;

}

void regulaFalsi() {

    double a, b, tolerancia, c, error;
    int contador = 0;

    cout << "Ingrese el límite inferior del intervalo: ";
    cin >> a;
    cout << "Ingrese el límite superior del intervalo: ";
    cin >> b;
    cout << "Ingrese la tolerancia: ";
    cin >> tolerancia;

        if (funcion(a) * funcion(b) < 0.0) {
            do {
                contador++;

                c = (a*funcion(b) - b*funcion(a)) / (funcion(b) - funcion(a));
                if (funcion(a) * funcion(c) > 0) {
                    a = c;
                } else if (funcion(a) * funcion(c) < 0) {
                    b = c;
                } else {
                    break;
                }

                error = (b - a) / 2;

            } while (error > tolerancia);

            cout << "\nResultado de la raíz: %.10lf", c);
            cout << "\nError estimado: %.10lf", error);
            cout << "\nCantidad de iteraciones: %d\n", contador);
            
        } else {
            cout << "\nNo hay raíz o hay un número par de ellas\n");
        }
    
}
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

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

    double a, b, tolerancia, c, cAnterior, error;
    int contador = 0;

    cout << "Ingrese el límite inferior del intervalo: ";
    cin >> a;
    cout << "Ingrese el límite superior del intervalo: ";
    cin >> b;
    cout << "Ingrese la tolerancia: ";
    cin >> tolerancia;

        if (funcion(a) * funcion(b) < 0.0) {
            cAnterior = a;
            do {
                contador++;

                c = (a*funcion(b) - b*funcion(a)) / (funcion(b) - funcion(a));
                
                error = fabs(c - cAnterior);
                cAnterior = c;
                
                if (funcion(a) * funcion(c) > 0) {
                    a = c;
                } else if (funcion(a) * funcion(c) < 0) {
                    b = c;
                } else {
                    break;
                }
                

            } while (error > tolerancia);

            cout << "\nResultado de la raíz: " << c << endl;
            cout << "\nError estimado: " << error << endl;
            cout << "\nCantidad de iteraciones: " << contador << endl;
            
        } else {
            cout << "\nNo hay raíz o hay un número par de ellas\n";
        }
    
}
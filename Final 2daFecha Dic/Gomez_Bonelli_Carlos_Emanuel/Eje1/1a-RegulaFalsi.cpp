#include <stdio.h>
#include <iostream>
#include <cmath>
#define A 0.5


using namespace std;

double funcion(double x);

void regulaFalsi();

int main() {

    regulaFalsi();

    return 0;
}

double funcion(double x) {
    // funcion original
    // ln(x) + A*x = 5
    return log(x) + A*x - 5;
    //return (log(x)  - 5)/0.5;
}

void regulaFalsi() {

    double a=5, b=8, tolerancia=1e-5, c=0, error=0;
    int contador = 0;
    printf("Límite inferior del intervalo: %.2f\n", a);
    printf("Límite superior del intervalo: %.2f\n", b);
    printf("Tolerancia: %.10f\n", tolerancia);

    //printf("funcion(a) * funcion(b) < 0.0 -> %.10f * %.10f < 0.0 -> %.10f < 0.0\n", funcion(a), funcion(b), funcion(a)*funcion(b));
    if (funcion(a) * funcion(b) < 0.0) {
        do {
            contador++; // Incrementar el contador de iteraciones

                // Calcular el punto c usando la fórmula del método de la falsa posición
                double fa = funcion(a);
                double fb = funcion(b);
                c = (a * fb - b * fa) / (fb - fa);

                // Verificar en qué parte del intervalo está la raíz
                if (funcion(a) * funcion(c) > 0) {
                    a = c; // Si f(a) y f(c) tienen el mismo signo, mover a al valor de c
                } else if (funcion(a) * funcion(c) < 0) {
                    b = c; // Si f(a) y f(c) tienen signos opuestos, mover b al valor de c
                } else {
                    break; // Si f(c) es 0, hemos encontrado la raíz exacta
                }

                // Calcular el error como la mitad del tamaño del intervalo actual
                error = (b - a) / 2;
                // Repetir el proceso hasta que el error sea menor que la tolerancia o se alcance el máximo de iteraciones
            } while (error > tolerancia && contador < 150000);

        //cout << "\nResultado de la raíz: " << c << endl;
        printf("Resultado de la raíz: %.10f\n", c);
        printf("Resultado del Error estimado: %.10f\n", error);
        //cout << "\nError estimado: " << error << endl;
        cout << "\nCantidad de iteraciones: " << contador << endl;
        
    } else {
        cout << "\nNo hay raíz o hay un número par de ellas\n";
    }
    
}
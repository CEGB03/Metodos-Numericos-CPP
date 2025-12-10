#include <iostream>
#include <math.h>
using namespace std;

double f(double x){ //ingresar la funcion
	return exp(x)*sin(x);
}

int main(int argc, char *argv[]) {
	int cantidad_puntos;
	double a,b;
	double integral_aproximada, integral_exacta=0.9093306736, integral_error;
	double c0,c1,c2,c3,c4,c5,x0,x1,x2,x3,x4,x5;
	/*
	cout << "\nIngresar a\n";
	cin >> a;
	cout << "\nIngresar b\n";
	cin >> b;
	cout << "\nIngresar la cantidad de puntos\n";
	cin >> cantidad_puntos;
	*/
	cout << "\nIntegracion por el metodo de Gauss-Legendre\n";
	a = 0.0;
	b = 1.0;
	cantidad_puntos = 2;
	cout << "\nSe calculara la integral_aproximada de a=" << a << " a b=" << b << " con " << cantidad_puntos << " puntos de I entre [" << a << " ; " << b << "] de e^x*sen(x) dx\n";


	c0 = 1;
	c1 = 1; 
	x0 = - 0.577350269;
	x1 = 0.577350269;
	integral_aproximada = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2));

	integral_error = fabs(integral_exacta - integral_aproximada);


	cout << "\nEl valor exacto de la integral entre a=" << a << " y b=" << b << " es de: I=" << integral_exacta << endl;
	cout << "\nEl valor de la integral_aproximada entre a=" << a << " y b=" << b << " es de: I=" << integral_aproximada << endl;
	cout << "\nEl error absoluto es de: Error=" << integral_error << endl;
	return 0;
}


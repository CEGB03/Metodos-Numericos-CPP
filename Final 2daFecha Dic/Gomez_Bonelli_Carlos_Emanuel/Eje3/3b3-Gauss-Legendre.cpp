#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

/**
 * Función de prueba por defecto
 * Puede ser reemplazada por otras funciones según sea necesario
 */
double f(double x){ 
    return 1.481841*pow(x, 1.57181);
}

int main(int argc, char *argv[]) {
	int cantidad_puntos=2, tipo_funcion=1;
	double a=1, b=5;
	double integral;
	double c0, c1, c2, c3, c4, c5, x0, x1, x2, x3, x4, x5;
	
	cout << "\n╔═════════════════════════════════════════════════════╗" << endl;
	cout << "║      INTEGRACIÓN NUMÉRICA - MÉTODO GAUSS-LEGENDRE   ║" << endl;
	cout << "╚═════════════════════════════════════════════════════╝" << endl;
	
	// Validar cantidad de puntos
	if(cantidad_puntos < 2 || cantidad_puntos > 6) {
		cout << "❌ Error: La cantidad de puntos debe estar entre 2 y 6" << endl;
		return 1;
	}
	cout << "\n" << string(60, '-') << endl;
	cout << "📊 Parámetros de integración:" << endl;
	cout << "   Intervalo: [" << fixed << setprecision(4) << a << ", " << b << "]" << endl;
	cout << "   Cantidad de puntos: " << cantidad_puntos << endl;
	cout << string(60, '-') << endl;
	
	// Inicializar integral
	integral = 0;
	switch(cantidad_puntos){
	case 2:
		c0 = 1;
		c1 = 1; 
		x0 = -0.577350269;
		x1 = 0.577350269;
		integral = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2));
		break;
	default:
		cout << "❌ Error: La cantidad de puntos debe estar entre 2 y 6" << endl;
		integral = 0;
		break;
	}

	cout << "\n✅ RESULTADO:" << endl;
	cout << "═══════════════════════════════════════════════" << endl;
	cout << fixed << setprecision(10);
	cout << "∫[" << a << ", " << b << "] f(x)dx ≈ " << integral << endl;
	cout << "═══════════════════════════════════════════════" << endl;
	
	return 0;
}


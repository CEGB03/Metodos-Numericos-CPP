#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

/**
 * Función de prueba por defecto
 * Puede ser reemplazada por otras funciones según sea necesario
 */
double f(double x){ 
	return exp(x)*sin(x);
}

/**
 * Selecciona y evalúa la función según el tipo elegido por el usuario
 */
double evaluarFuncion(double x, int tipo) {
	switch(tipo) {
		case 1:
			return exp(x)*sin(x);
		case 2:
			return x*x;
		case 3:
			return 1.0/(1.0 + x*x);
		case 4:
			return sin(x);
		case 5:
			return cos(x);
		case 6:
			return exp(-x*x);
		default:
			return exp(x)*sin(x);  // Default
	}
}

/**
 * Muestra menú de funciones disponibles
 */
void mostrarMenuFunciones() {
	cout << "\n╔═════════════════════════════════════════╗" << endl;
	cout << "║      FUNCIONES DISPONIBLES              ║" << endl;
	cout << "╚═════════════════════════════════════════╝" << endl;
	cout << "1. f(x) = exp(x)*sin(x)  [por defecto]" << endl;
	cout << "2. f(x) = x²" << endl;
	cout << "3. f(x) = 1/(1+x²)" << endl;
	cout << "4. f(x) = sin(x)" << endl;
	cout << "5. f(x) = cos(x)" << endl;
	cout << "6. f(x) = e^(-x²)" << endl;
}

int main(int argc, char *argv[]) {
	int cantidad_puntos, tipo_funcion;
	double a, b;
	double integral;
	double c0, c1, c2, c3, c4, c5, x0, x1, x2, x3, x4, x5;
	
	cout << "\n╔═════════════════════════════════════════════════════╗" << endl;
	cout << "║      INTEGRACIÓN NUMÉRICA - MÉTODO GAUSS-LEGENDRE   ║" << endl;
	cout << "╚═════════════════════════════════════════════════════╝" << endl;
	
	// Solicitar límites de integración
	cout << "\nIngrese el límite inferior (a): ";
	cin >> a;
	cout << "Ingrese el límite superior (b): ";
	cin >> b;
	
	// Validar límites
	if(a >= b) {
		cout << "❌ Error: El límite inferior (a) debe ser menor que el superior (b)" << endl;
		return 1;
	}
	
	// Solicitar cantidad de puntos
	cout << "Ingrese la cantidad de puntos de Gauss (2-6): ";
	cin >> cantidad_puntos;
	
	// Validar cantidad de puntos
	if(cantidad_puntos < 2 || cantidad_puntos > 6) {
		cout << "❌ Error: La cantidad de puntos debe estar entre 2 y 6" << endl;
		return 1;
	}
	
	// Mostrar menú de funciones
	mostrarMenuFunciones();
	cout << "\nSeleccione la función (1-6, default=1): ";
	cin >> tipo_funcion;
	
	cout << "\n" << string(60, '─') << endl;
	cout << "📊 Parámetros de integración:" << endl;
	cout << "   Intervalo: [" << fixed << setprecision(4) << a << ", " << b << "]" << endl;
	cout << "   Cantidad de puntos: " << cantidad_puntos << endl;
	cout << string(60, '─') << endl;
	
	// Inicializar integral
	integral = 0;
	switch(cantidad_puntos){
	case 2:
		c0 = 1;
		c1 = 1; 
		x0 = -0.577350269;
		x1 = 0.577350269;
		integral = ((b-a)/2) * (c0 * evaluarFuncion(((b-a)/2) * x0 + (b+a)/2, tipo_funcion) + c1 * evaluarFuncion(((b-a)/2)*x1 + (b+a)/2, tipo_funcion));
		break;
	case 3: 
		c0 = 0.5555556;
		x0 = -0.774596669; 
		c1 = 0.8888889; 
		x1 = 0.0;
		c2 = 0.5555556; 
		x2 = 0.774596669;
		integral = ((b-a)/2) * (c0 * evaluarFuncion(((b-a)/2) * x0 + (b+a)/2, tipo_funcion) + c1 * evaluarFuncion(((b-a)/2)*x1 + (b+a)/2, tipo_funcion) + c2 * evaluarFuncion(((b-a)/2)*x2 + (b+a)/2, tipo_funcion));
		break; 
	case 4: 
		c0 = 0.3478548;
		x0 = -0.861136312;
		c1 = 0.6521452; 
		x1 = -0.339981044;
		c2 = 0.6521452;
		x2 = 0.339981044;
		c3 = 0.3478548; 
		x3 = 0.861136312;
		integral = ((b-a)/2) * (c0 * evaluarFuncion(((b-a)/2) * x0 + (b+a)/2, tipo_funcion) + c1 * evaluarFuncion(((b-a)/2)*x1 + (b+a)/2, tipo_funcion) + c2 * evaluarFuncion(((b-a)/2)*x2 + (b+a)/2, tipo_funcion) + c3 * evaluarFuncion(((b-a)/2)*x3 + (b+a)/2, tipo_funcion));	
		break;
	case 5: 
		c0 = 0.2369269;
		x0 = -0.906179846; 
		c1 = 0.4786287;
		x1 = -0.538469310;
		c2 = 0.5688889;
		x2 = 0.0;
		c3 = 0.4786287;
		x3 = 0.538469310;
		c4 = 0.2369269;
		x4 = 0.906179846;
		integral = ((b-a)/2) * (c0 * evaluarFuncion(((b-a)/2) * x0 + (b+a)/2, tipo_funcion) + c1 * evaluarFuncion(((b-a)/2)*x1 + (b+a)/2, tipo_funcion) + c2 * evaluarFuncion(((b-a)/2)*x2 + (b+a)/2, tipo_funcion) + c3 * evaluarFuncion(((b-a)/2)*x3 + (b+a)/2, tipo_funcion) + c4 * evaluarFuncion(((b-a)/2)*x4 + (b+a)/2, tipo_funcion));		
		break;
	case 6: 
		c0 = 0.1713245;
		x0 = -0.932469514;
		c1 = 0.3607616;
		x1 = -0.661209386;
		c2 = 0.4679139;
		x2 = -0.238619186;
		c3 = 0.4679139;
		x3 = 0.238619186;
		c4 = 0.3607616;
		x4 = 0.661209386;
		c5 = 0.1713245;
		x5 = 0.932469514;
		integral = ((b-a)/2) * (c0 * evaluarFuncion(((b-a)/2) * x0 + (b+a)/2, tipo_funcion) + c1 * evaluarFuncion(((b-a)/2)*x1 + (b+a)/2, tipo_funcion) + c2 * evaluarFuncion(((b-a)/2)*x2 + (b+a)/2, tipo_funcion) + c3 * evaluarFuncion(((b-a)/2)*x3 + (b+a)/2, tipo_funcion) + c4 * evaluarFuncion(((b-a)/2)*x4 + (b+a)/2, tipo_funcion) + c5 * evaluarFuncion(((b-a)/2)*x5 + (b+a)/2, tipo_funcion));		
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


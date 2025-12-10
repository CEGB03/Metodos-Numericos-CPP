#include <iostream>
#include <math.h>
#include <iomanip>
#define FILAS 9
using namespace std;

/**
 * Función exacta: f(x) = e^x
 * Derivada exacta: f'(x) = e^x
 * Usada para comparar con valores numéricos
 */
double f(double x){
	return exp(x);
}

double fDerivada(double x){
	return exp(x);
}
	
	int main(int argc, char *argv[]) {
		/**
		 * TABLA DE DATOS: f(x) = e^x en [0, 2] con h = 0.25
		 * Datos de la función exponencial en puntos equidistantes
		 */
		double a[FILAS][2] = {
			{0,1},{0.25,1.284},{0.5,1.649},{0.75,2.117},{1,2.718},
			{1.25,3.490},{1.5,4.482},{1.75,5.755},{2,7.389}
		};
		
		double deriv[FILAS][2] = {{0}};
		double derivExacta[FILAS][2] = {{0}};
		double error[FILAS] = {0};
		
		// Paso de integración (equidistante)
		double h = a[1][0] - a[0][0];
		
		cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
		cout << "║           DIFERENCIACIÓN NUMÉRICA - TABLA DE DATOS         ║" << endl;
		cout << "╚════════════════════════════════════════════════════════════╝" << endl;
		
		cout << "\n📊 Información de la tabla:" << endl;
		cout << "   Función: f(x) = e^x" << endl;
		cout << "   Intervalo: [0, 2]" << endl;
		cout << "   Puntos: " << FILAS << endl;
		cout << "   Paso h: " << fixed << setprecision(2) << h << endl;
		cout << "   Derivada exacta: f'(x) = e^x" << endl;
		
		// Copiar x a deriv y calcular derivada exacta
		for(int i = 0 ; i < FILAS ; i++){
			deriv[i][0] = a[i][0];
			derivExacta[i][0] = a[i][0];
			derivExacta[i][1] = fDerivada(a[i][0]);
		}
		
		// Primera derivada: diferencia adelantada (O(h²))
		deriv[0][1] = (-a[2][1] + 4*a[1][1] - 3*a[0][1]) / (2*h);
		error[0] = fabs(deriv[0][1] - derivExacta[0][1]);
		
		// Derivadas interiores: diferencia central (O(h²))
		for(int i = 1 ; i < FILAS-1 ; i++){
			deriv[i][1] = (a[i+1][1] - a[i-1][1]) / (2*h);
			error[i] = fabs(deriv[i][1] - derivExacta[i][1]);
		}
		
		// Última derivada: diferencia atrasada (O(h²))
		deriv[FILAS-1][1] = (3*a[FILAS-1][1] - 4*a[FILAS-2][1] + a[FILAS-3][1]) / (2*h);
		error[FILAS-1] = fabs(deriv[FILAS-1][1] - derivExacta[FILAS-1][1]);
		
		// Mostrar resultados tabulados
		cout << "\n" << string(120, '─') << endl;
		cout << setw(6) << "i" 
		     << setw(12) << "x_i" 
		     << setw(16) << "f(x_i)" 
		     << setw(16) << "f'(x_i) NUM." 
		     << setw(16) << "f'(x_i) EXACTA"
		     << setw(18) << "Error Absoluto"
		     << setw(16) << "Método" << endl;
		cout << string(120, '─') << endl;
		
		cout << fixed << setprecision(6);
		for(int i = 0 ; i < FILAS ; i++){
			string metodo;
			if(i == 0) {
				metodo = "Adelantada";
			} else if(i == FILAS-1) {
				metodo = "Atrasada";
			} else {
				metodo = "Central";
			}
			
			cout << setw(6) << i
			     << setw(12) << deriv[i][0]
			     << setw(16) << a[i][1]
			     << setw(16) << deriv[i][1]
			     << setw(16) << derivExacta[i][1]
			     << setw(18) << scientific << setprecision(2) << error[i]
			     << setw(16) << fixed << setprecision(0) << metodo << endl;
		}
		cout << string(120, '─') << endl;
		
		// Estadísticas de error
		cout << "\n📈 Estadísticas de error:" << endl;
		double errorMax = error[0], errorMin = error[0], errorProm = 0;
		for(int i = 0; i < FILAS; i++) {
			if(error[i] > errorMax) errorMax = error[i];
			if(error[i] < errorMin) errorMin = error[i];
			errorProm += error[i];
		}
		errorProm /= FILAS;
		
		cout << fixed << setprecision(2) << scientific;
		cout << "   Error máximo:   " << errorMax << endl;
		cout << "   Error mínimo:   " << errorMin << endl;
		cout << "   Error promedio: " << errorProm << endl;
		
		cout << "\n✅ Resultado: Diferenciación completada" << endl;
		
		return 0;
	}

#include <iostream>
#include <math.h>
#define ROWS 20
#define FILAS 2
using namespace std;


void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);


void regresionLineal(double m[ROWS][2] , int filas);

int main(int argc, char *argv[]) {
	double m[ROWS][2];
	m[0][0] = -1;	m[0][1] = 10;
	m[1][0] = 0;	m[1][1] = 9;
	m[2][0] = 1;	m[2][1] = 7;
	m[3][0] = 2;	m[3][1] = 5;
	m[4][0] = 3;	m[4][1] = 4;
	m[5][0] = 4;	m[5][1] = 3;
	m[6][0] = 5;	m[6][1] = 0;
	m[7][0] = 6;	m[7][1] = -1;
	int filas = 8; 
	cout << "\n--> Regresion Lineal\n";
	
	regresionLineal(m , filas);

	return 0;
	
}
void regresionLineal(double m[ROWS][2], int filas){
	double a[2][2] = {{0}};
	double b[2] = {0};
	double yProm = 0, r2 = 0, Sr = 0, St = 0, sum = 0; 
	
	// Construir el sistema de ecuaciones normales
	// [Σx²  Σx ] [a₁]   [Σxy]
	// [Σx   n  ] [a₀] = [Σy ]
	a[0][0] = 0; // Σx²
	a[0][1] = 0; // Σx
	a[1][0] = 0; // Σx
	a[1][1] = filas; // n
	
	for(int i = 0 ; i < filas ; i++){
		a[0][0] += pow(m[i][0], 2); // Σx²
		a[0][1] += m[i][0];          // Σx
		a[1][0] += m[i][0];          // Σx
		b[0] += m[i][0] * m[i][1];   // Σxy
		b[1] += m[i][1];             // Σy
	}

	cout << "\nSistema de Ecuaciones Normales:\n";
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < 2 ; j++){
			cout << "\t" << a[i][j];
		}
		cout << "\t=\t" << b[i] << endl;
	}
	
	double* x = (double*)malloc(2 * sizeof(double));
	triangulacion(a, b, x, 2);

	cout << "\n\n=== RESULTADOS DE LA REGRESIÓN LINEAL ===\n";
	cout << "\nCoeficientes:\n";
	cout << "a₁ (pendiente) = " << x[0] << "\n";
	cout << "a₀ (ordenada)  = " << x[1] << "\n";
	cout << "\nEcuación de la recta: y = " << x[0] << "x + " << x[1] << "\n";
 	
	// Calcular promedio de y
	for(int i = 0; i < filas ; i++){
		yProm += m[i][1];
	}
	yProm = yProm/filas;
	
	// Calcular St (variación total)
	for(int i = 0; i < filas ; i++){
		St += pow((m[i][1] - yProm), 2);
	}
	
	// Calcular suma de errores al cuadrado
	for(int i = 0; i < filas ; i++){
		double y_ajustada = x[0] * m[i][0] + x[1];
		sum += pow((m[i][1] - y_ajustada), 2);
	}
	
	// Error estándar de la regresión (con corrección por grados de libertad)
	Sr = sqrt(sum / (filas - 2));
	
	// Coeficiente de determinación r²
	r2 = (St - sum) / St;

	cout << "\n=== ESTADÍSTICAS ===\n";
	cout << "Promedio de y: " << yProm << "\n";
	cout << "Variación total (St): " << St << "\n";
	cout << "Suma de errores² (Sr): " << sum << "\n";
	cout << "Error estándar: " << Sr << "\n";
	cout << "Coeficiente de determinación (r²): " << r2 << "\n";
	cout << "Coeficiente de correlación (r): " << sqrt(r2) << "\n";
	
	free(x);
}
void triangulacion(double a[2][2], double b[2], double x[ROWS], int filas){
	for (int i = 0 ; i < (filas - 1) ; i++){
		pivot(a, b, filas , i);
		
		// Verificar pivote
		if(fabs(a[i][i]) < 1e-10){
			cout << "Error: Pivote nulo en fila " << i << endl;
			return;
		}
		
		for (int j = i + 1; j < filas; j++) {
			double factor = a[j][i] / a[i][i];
			for (int k = i; k < filas; ++k) {
				a[j][k] = a[j][k] - factor * a[i][k];
			}
			b[j] = b[j] - factor * b[i];
		}
	}
	
	double norma = determinante(a,b,x,filas);
	if(norma == 0.0){
		cout << "\n\nmatriz singular";
	}else{
		retrostutitucion(a, b, x, filas);
	}
}
		
void retrostutitucion(double a[2][2], double b[2], double x[ROWS], int filas){
	double value = 0;
	value = b[filas - 1] / a[filas - 1][filas - 1];
	x[filas - 1] = value;
	for (int i = filas - 2; i >= 0; --i) {
		double sum = 0;
		for (int j = i + 1; j < filas; ++j) {
			sum = sum + a[i][j] * x[j];
		}
		value = (b[i] - sum) / a[i][i];
		x[i] = value;
	}
	
}
			
void pivot(double a[2][2], double b[2], int filas, int i){
	// Buscar el pivote de mayor magnitud
	int maxRow = i;
	double maxVal = fabs(a[i][i]);
	
	for (int j = i + 1; j < filas; j++) {
		if (fabs(a[j][i]) > maxVal) {
			maxVal = fabs(a[j][i]);
			maxRow = j;
		}
	}
	
	// Intercambiar filas si se encontró un pivote mejor
	if (maxRow != i) {
		for (int k = i; k < filas; ++k) {
			double swap = a[i][k];
			a[i][k] = a[maxRow][k];
			a[maxRow][k] = swap;
		}
		double swap = b[i];
		b[i] = b[maxRow];
		b[maxRow] = swap;
	}
}
				
double determinante(double a[2][2], double b[2], double x[ROWS], int filas){
	double det = 1;
	for(int i = 0; i < filas ; i++){
		det = det * a[i][i];
	}
	return det;
}

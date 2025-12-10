#include <stdlib.h>
#include <iostream>
#include <math.h>
#define FILAS 20
#define COLUMNAS 20

using namespace std;

void fileReader (double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA (double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB (double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);

void jacobi (double a[FILAS][COLUMNAS] , double b[FILAS], int filas);
void gaussSeidel (double a[FILAS][COLUMNAS] , double b[FILAS], int filas);
void relajacion (double a[FILAS][COLUMNAS] , double b[FILAS], int filas);
bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas);


int main(int argc, char* argv[])
{
	double m[FILAS][COLUMNAS];
	double a[FILAS][COLUMNAS];
	double b[FILAS];
	int filas = 0, columnas = 0;
	fileReader(m, &filas, &columnas);
	matrizA(a,m,filas, columnas);
	matrizB(b,m,filas, columnas);
	
	int scanner;
	cout << "Seleccione:\n 1 --> Jacobi \n 2 --> Gauss Seidel \n 3 --> Gauss Seidel con Relajacion\n";
	cin >> scanner;
	switch(scanner){
		case 1:
			jacobi(a,b,filas);
			break;
			
		case 2: 
			gaussSeidel(a,b,filas);
			break;
		case 3: 
			relajacion(a,b,filas);
			break;
			
		default: 
			cout << "\n Se seleccionó mal la opcion";
	}
	

}
void fileReader (double m[FILAS][COLUMNAS],int* filas, int* columnas){
	
	
	FILE *fp;
	char c;
	fp = fopen("data.txt","r");
	if ( fp == NULL )
	{
		cout << "No se puede abrir el archivo";
	}
	int fila=0;
	int columna;
	while((c = fgetc(fp)) != EOF)
	{
		if(c == '\n'){
			fila++;
		}
	}
	
	fclose(fp);
	fp = fopen("data.txt","r");
	
	int i, j;
	for(i = 0; i < fila; i++) {
		j = 0;
		do {
			fscanf(fp, "%lf", &(m[i][j]));
			j++;
		} while((c = fgetc(fp)) != '\n');
	}
	columna = j;
	*columnas = columna;
	*filas = fila;
	
}
void matrizA (double a[FILAS][COLUMNAS],double m[FILAS][COLUMNAS], int filas, int columnas){
	for(int i = 0 ; i < filas ; i++){
		for (int j = 0 ; j < columnas - 1 ; j++){
			a[i][j] = m[i][j];
		}
	}
}
	
void matrizB (double b[FILAS],double m[FILAS][COLUMNAS], int filas, int columnas){

	for(int i = 0 ; i < filas ; i++){
		b[i] = m[i][columnas - 1];
	}
	
}
	
void jacobi(double a[FILAS][COLUMNAS] , double b[FILAS] , int filas){
	cout << "\n\n***Ha seleccionado método de jacobi***" << endl << endl;
	
	bool check = diagonalmenteDominante(a,filas);
	if(!check)
		exit(0);
	
	double suma = 0; 
	double* xNuevo = (double*)malloc(filas * sizeof(double));
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if(xNuevo == NULL || xViejo == NULL){
		cout << "Error: No se pudo asignar memoria.\n";
		exit(1);
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xNuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
	cout << "\nIngrese la tolerancia" << endl;
	cin >> tolerancia;
	
	do {
		iteraciones++;
		for (int i = 0; i < filas; i++) {
			suma = 0;
			for (int j = 0; j < filas; j++) {
				if (j != i)
					suma += a[i][j] * xViejo[j];
			}
			xNuevo[i] = (b[i] - suma) / a[i][i];
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xNuevo[i] - xViejo[i]) * (xNuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignaci�n del vector viejo para la pr�xima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xNuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	cout << "\n El resultado es: \nxnuevo = [\t";
	for (int i = 0; i < filas; i++) {
		cout << xNuevo[i] << "\t";
	}
	
	cout << "]\n La cantidad de iteraciones fueron: " << iteraciones << "\n El error es de " << error << endl;
	
	free(xNuevo);
	free(xViejo);
}
void gaussSeidel (double a[FILAS][COLUMNAS] , double b[FILAS], int filas){
	cout << "\n\n***Ha seleccionado método de Gauss Seidel***\n\n";

	bool check = diagonalmenteDominante(a,filas);
	if(!check)
		exit(0);
	
	double suma = 0; 
	double* xNuevo = (double*)malloc(filas * sizeof(double));
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if(xNuevo == NULL || xViejo == NULL){
		cout << "Error: No se pudo asignar memoria." << endl;
		exit(1);
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xNuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
	cout << "\nIngrese la tolerancia" << endl;
	cin >> tolerancia;
	
	do {
		iteraciones++;
		for (int i = 0; i < filas; i++) {
			suma = 0;
			// Usar valores ya actualizados (xNuevo) para j < i
			for(int j = 0 ; j < i ; j++){
				suma += a[i][j] * xNuevo[j];
			}
			// Usar valores de iteración anterior (xViejo) para j > i
			for(int j = i+1 ; j < filas ; j++){
				suma += a[i][j] * xViejo[j]; 
			}
			xNuevo[i] = (b[i] - suma)/a[i][i];
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xNuevo[i] - xViejo[i]) * (xNuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignaci�n del vector viejo para la pr�xima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xNuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	cout << "\n El resultado es: \nxnuevo = [\t";
	for (int i = 0; i < filas; i++) {
		cout << xNuevo[i] << "\t";
	}
	
	cout << "]\n La cantidad de iteraciones fueron: " << iteraciones << "\n El error es de " << error << endl;
	
	free(xNuevo);
	free(xViejo);
}
	
void relajacion (double a[FILAS][COLUMNAS] , double b[FILAS], int filas){
	cout << "\n\n***Ha seleccionado método de Gauss Seidel con Coeficiente de Relajacion***\n\n";
	bool check = diagonalmenteDominante(a,filas);
	if(!check)
		exit(0);
	
	double suma = 0; 
	double* xNuevo = (double*)malloc(filas * sizeof(double));
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if(xNuevo == NULL || xViejo == NULL){
		cout << "Error: No se pudo asignar memoria." << endl;
		exit(1);
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xNuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
	float factor_relajacion;
	cout << "\nIngrese la tolerancia" << endl;
	cin >> tolerancia;
	cout << "\nIngrese el factor relajacion" << endl;
	cin >> factor_relajacion;

	do {
		iteraciones++;
		for (int i = 0; i < filas; i++) {
			suma = 0;
			// Usar valores ya actualizados (xNuevo) para j < i
			for(int j = 0 ; j < i ; j++){
				suma += a[i][j] * xNuevo[j];
			}
			// Usar valores de iteración anterior (xViejo) para j > i
			for(int j = i+1 ; j < filas ; j++){
				suma += a[i][j] * xViejo[j]; 
			}
			// Calcular valor temporal sin relajación
			double x_temp = (b[i] - suma)/a[i][i];
			// Aplicar factor de relajación
			xNuevo[i] = factor_relajacion * x_temp + (1-factor_relajacion) * xViejo[i];
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xNuevo[i] - xViejo[i]) * (xNuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignaci�n del vector viejo para la pr�xima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xNuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	cout << "\n El resultado es: \nxnuevo = [\t";
	for (int i = 0; i < filas; i++) {
		cout << xNuevo[i] << "\t";
	}
	
	cout << "]\n La cantidad de iteraciones fueron: " << iteraciones << "\n El error es de " << error << endl;
	
	free(xNuevo);
	free(xViejo);
}
bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas){
	double suma = 0;
	bool esDominante = true;
	
	for(int i = 0; i < filas ; i++){
		// Verificar ceros en la diagonal
		if(fabs(a[i][i]) < 1e-10){
			cout << "\nError: Cero en la diagonal, fila " << (i+1) << endl;
			return false;
		}
		
		suma = 0; 
		for(int j = 0 ; j < filas ; j++){
			if(j != i){
				suma += fabs(a[i][j]);
			}
		}
		
		if(fabs(a[i][i]) < suma){
			cout << "\nAdvertencia: Fila " << (i+1) << " no es diagonalmente dominante" << endl;
			cout << "|a[" << (i+1) << "][" << (i+1) << "]| = " << fabs(a[i][i]) << " < " << suma << " (suma de |resto|)" << endl;
			esDominante = false;
		}
	}
	
	if(!esDominante){
		cout << "\nLa matriz NO es diagonalmente dominante. Los métodos pueden no converger." << endl;
	}
	
	return true; // Permitir continuar pero con advertencia
}

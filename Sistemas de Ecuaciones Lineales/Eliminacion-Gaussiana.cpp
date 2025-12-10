#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#define FILAS 20
#define COLUMNAS 20

using namespace std;

void fileReader (double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA (double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB (double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);

// Funci�n para triangular matriz
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);

//Funcion para retrostutituir matriz
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);

//
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i);

//verifica que en la diagonal no hayan ceros.
double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);

int main(int argc, char* argv[])
{
	double m[FILAS][COLUMNAS];
	double a[FILAS][COLUMNAS];
	double b[FILAS];
	int filas = 0, columnas = 0;
	fileReader(m, &filas, &columnas);
	matrizA(a,m,filas, columnas);
	matrizB(b,m,filas, columnas);
	
	// Llamar a la funci�n eliminacionGaussiana --> la llamo triangulacion
	double* x = (double*)malloc(filas * sizeof(double));
	triangulacion(a, b, x, filas);
	
}


void fileReader (double m[FILAS][COLUMNAS],int* filas, int* columnas){

	FILE *fp;
	char c;
	fp = fopen("data.txt","r");
	if ( fp == NULL )
	{
		cout <<"No se puede abrir el archivo";
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
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
	for (int i = 0 ; i < (filas - 1) ; i++){
		pivot(a, b, filas , i);
		
		// Verificar que el pivote no sea cero después del intercambio
		if(fabs(a[i][i]) < 1e-10){
			cout << "Error: No se puede continuar, pivote nulo en fila " << i << endl;
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
		cout << "\n\nmatriz singular" << endl;
	}else{
		retrostutitucion(a, b, x, filas);
	}
}
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
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
    cout << "Conjunto solucion: " << endl;
    for (int i = 0; i < filas; ++i) {
        cout << "x" << (i + 1) << " = " << x[i] << endl;
    }
}
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i){
	// Buscar el pivote de mayor magnitud (pivoteo parcial)
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
		cout << "Se realizo pivoteo: intercambio fila " << i << " con fila " << maxRow << endl;
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
double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
	double det = 1;
	for(int i = 0; i < filas ; i++){
		det = det * a[i][i];
	}
	cout <<"\nEl determinante es: " << det << endl;
	return det;
}



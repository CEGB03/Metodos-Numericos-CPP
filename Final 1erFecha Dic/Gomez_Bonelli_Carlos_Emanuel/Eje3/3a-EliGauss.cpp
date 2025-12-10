#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define FILAS 20
#define COLUMNAS 20

using namespace std;

void fileReader (double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA (double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB (double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);

// Función para mostrar la matriz aumentada
void mostrarMatriz(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int columnas);

// Funci�n para triangular matriz
void triangulation(double [FILAS][COLUMNAS], double [FILAS], int, int);

void retrosustitucion(double [FILAS][COLUMNAS], double [FILAS], double [FILAS], int, int);

void pivot(double [FILAS][COLUMNAS], double [FILAS], int, int, int);

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

	mostrarMatriz(a, b, filas, columnas);
	
	// Llamar a la funci�n eliminacionGaussiana --> la llamo triangulacion
	double* x = (double*)malloc(filas * sizeof(double));

    triangulation(a, b, filas, columnas);
    retrosustitucion(a, b, x, filas, columnas);
	
}


void fileReader (double m[FILAS][COLUMNAS],int* filas, int* columnas){

	FILE *fp;
	char c;
	fp = fopen("data.txt","r");
	if ( fp == NULL )
	{
		cout <<"No se puede abrir el archivo" << endl;
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
void triangulation(double m[FILAS][COLUMNAS], double b[FILAS], int rows, int columns) {
    for (int i = 0; i < rows - 1; ++i) {
        pivot(m, b, rows, columns, i);
		mostrarMatriz(m, b, rows, columns);
        for (int j = i + 1; j < rows; ++j) {
            double factor = -m[j][i] / m[i][i];
            for (int k = 0; k < columns; ++k) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    mostrarMatriz(m, b, rows, columns);
}

void pivot(double m[FILAS][COLUMNAS], double b[FILAS], int rows, int columns, int i) {
    double tolerance = pow(10, -3);
    if (fabs(m[i][i]) < tolerance) {
        for (int j = i + 1; j < rows; ++j) {
            if (fabs(m[j][i]) > fabs(m[i][i])) {
                for (int k = i; k < columns; ++k) {
                    printf("Se realizo pivoteo\n");
                    double swap = m[i][k];
                    m[i][k] = m[j][k];
                    m[j][k] = swap;
                }
                double swap = b[i];
                b[i] = b[j];
                b[j] = swap;
            }
        }
    }
}

void retrosustitucion(double m[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int rows, int columns) {
    double value = 0;
    value = b[rows - 1] / m[rows - 1][columns - 1];
    x[rows - 1] = value;
    for (int i = rows - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < columns; ++j) {
            sum = sum + m[i][j] * x[j];
        }
        value = (b[i] - sum) / m[i][i];
        x[i] = value;
    }
    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n", i + 1, x[i]);
    }
}

double determinante(double m[FILAS][COLUMNAS], double b[FILAS], int rows, int columns) {
    double norma = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            norma = norma + pow(m[i][j], 2);
        }
    }
    norma = sqrt(norma);
    return norma;
}


void mostrarMatriz(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int columnas){
	cout << "Matriz Aumentada:" << endl;
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < columnas - 1; ++j) {
			cout << a[i][j] << "\t";
		}
		cout << "| " << b[i] << endl;
	}
	cout << endl;
}
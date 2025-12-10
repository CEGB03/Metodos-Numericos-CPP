#include <stdlib.h>
#include <iostream>
#include <math.h>
#define FILAS 20
#define COLUMNAS 20

using namespace std;

void fileReader (double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA (double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB (double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);

void jacobi (double a[FILAS][COLUMNAS] , double b[FILAS], int filas, int columnas);
bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas);
// Función para mostrar la matriz aumentada
void mostrarMatriz(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int columnas);


int main(int argc, char* argv[])
{
	double m[FILAS][COLUMNAS];
	double a[FILAS][COLUMNAS];
	double b[FILAS];
	int filas = 0, columnas = 0;
	fileReader(m, &filas, &columnas);
	matrizA(a,m,filas, columnas);
	matrizB(b,m,filas, columnas);
	mostrarMatriz(a,b,filas,columnas);
	jacobi(a,b,filas,columnas-1);
	mostrarMatriz(a,b,filas,columnas);

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
	
void jacobi(double m[FILAS][COLUMNAS], double b[FILAS], int filas, int columnas) {

    double xv[FILAS] = {0, 0, 0, 0, 0};
    double xn[FILAS] = {0, 0, 0, 0, 0};
    double tolerancia=1e-3;
	/*
    printf("Ingrese la cantidad de cifras decimales de error\n");
    scanf("%lf", &tolerancia);
    tolerancia = pow(10, -tolerancia);
	*/
    double error;
    int iteraciones = 0;

    //Diagonalmente dominante
    for (int i = 0; i < filas; i++) {
        double sum = 0;
        for (int j = 0; j < columnas; j++) {
            if (i != j) {
                sum = sum + fabs(m[i][j]);
            }
        }
        if (fabs(m[i][i]) <= sum) {
            printf("La matriz no es diagonalmente dominante\n");
        }
    }

    do {
        error = 0;
        iteraciones++;
        for (int i = 0; i < filas; ++i) {
            double sum = 0;
            for (int j = 0; j < columnas; ++j) {
                if (i != j) {
                    sum = sum + m[i][j] * xv[j];
                }
            }
            xn[i] = (b[i] - sum) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }

        error = sqrt(error);

        if (iteraciones == 9999) {
            printf("Numero maximo de iteraciones alcanzado\n");
        }

    } while (error > tolerancia && iteraciones < 10000);

    printf("Conjunto solucion: \n");
	printf("Formato cientifico:\n");
    for (int i = 0; i < filas; ++i) {
        printf("x%d = %E\n", i + 1, xn[i]);
    }
	printf("Formato decimal:\n");
    for (int i = 0; i < filas; ++i) {
        printf("x%d = %.10f\n", i + 1, xn[i]);
    }
    printf("Error: %.10f\nIteraciones: %d", error, iteraciones);
}


bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas){
	double suma = 0; 
	int counter = 0;
	for(int i = 0; i < filas ; i++){
		suma = 0; 
		counter++;
		for(int j = 0 ; j < filas ; j++){
			if(j!=i){
				suma+= fabs(a[i][j]);
			}
		}
		
		if(fabs(a[i][i]) < suma)
			cout << "\nLa matriz no es diagonalmente dominante. Fila: " << counter;

		if(a[i][i] == 0){
			cout << "\nCeros en la diagonal" << endl;
			return false;
		}
	}
	return true;
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
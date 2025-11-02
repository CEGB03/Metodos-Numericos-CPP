#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define FILAS 20
using namespace std;


void fileReader (double m[FILAS][2], int* filas);


void lagrange (double m[FILAS][2], int fila);	
void polinomica (double [FILAS][2], int fila);


void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);


/* double func (double x){

	return x + 2/x;
}
 */
void mostrarPolinomio(double m[FILAS][2], int fila);


int main(int argc, char *argv[]) {
	double m[FILAS][2] ;
	int filas; 
	fileReader(m,&filas);
	int seleccion;
	cout << "\n========== INTERPOLACION ==========\n";
	cout << "Cantidad de puntos: " << filas << "\n";
	cout << "\nPuntos cargados (X ; Y):\n";
	for(int i = 0; i < filas ; i++){
		cout << "(" << m[i][0] << " ; " << m[i][1] << ")" << endl;
	}
	cout << "\nSeleccione el método de interpolación:\n";
	cout << "1 --> Método de Lagrange\n";
	cout << "2 --> Método Polinómico (Matriz de Vandermonde)\n";
	cout << "Opción: ";
	cin >> seleccion;
	switch (seleccion){
	case 1: 
		lagrange(m, filas);
		break;
	case 2: 
		polinomica(m, filas);
		break;
	default: 
		cout << "\nSe seleccionó mal la opcion";
		break;
	}
	return 0;
}


void fileReader (double m[FILAS][2],int* filas){
	
	
	FILE *fp;
	char c;
	fp = fopen("data.txt","r");
	
	if ( fp == NULL )
	{
		cout << "No se puede abrir el archivo\n";
		exit(10);
	}
	cout << "\nDatos cargados desde data.txt\n";
	int fila=0;
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
	
	*filas = fila;
	cout<< "Archivo leído con éxito.\n";
	fclose(fp);
}
	
void lagrange(double m[FILAS][2], int fila) {
    double x; // Valor a interpolar
    double e=0.0000000000000000000000000000000000000000000000000000000000000000000000000000003; // Error
    
    cout << "=== INTERPOLACIÓN DE LAGRANGE ===" << endl;
    cout << "Recuerde haber definido la función previamente" << endl;
    cout << "Ingrese el valor a interpolar: ";
    cin >> x;

    double sum = 0;
    for (int i = 0; i < fila; i++) {
        double producto = 1;
        for (int j = 0; j < fila; j++) {
            if (j != i) {
                // ✅ CORRECCIÓN: xi - xj en lugar de xi - xj
                producto *= ((x - m[j][0]) / (m[i][0] - m[j][0]));
            }
        }
        sum += m[i][1] * producto;
    }
    
    // Calcular error si hay función de referencia
    //e = fabs(func(x) - sum);
    
    cout << "El valor interpolado para " << x << " es: " << sum 
         << ", con un error de " << e << endl;

    // Mostrar polinomio interpolador
    mostrarPolinomio(m, fila);
}

void polinomica (double m[FILAS][2], int fila){
	cout << "\n=== INTERPOLACION POLINOMICA ===\n";
	double a[FILAS][FILAS]; 
	double b[FILAS];
	
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < fila; j++) {
			a[i][j] = pow(m[i][0], j);
		}
		b[i] = m[i][1];
	}
	cout << "\nMatriz a\n";
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < fila; j++) {
			cout << a[i][j];
			cout << "\t";
		}
		cout << "\n";
	}
	cout << "\nMatriz b\n";
	for (int i = 0; i < fila; i++) {
		cout << b[i];
		cout << "\t";
	}
	
	double* x = (double*)malloc(fila * sizeof(double));
	triangulacion(a, b, x, fila);
	free(x);
}
void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas){
	for (int i = 0 ; i < (filas - 1) ; i++){
		pivot(a, b, filas , i);
		for (int j = i + 1; j < filas; j++) {
			double factor = -a[j][i] / a[i][i];
			for (int k = 0; k < filas; ++k) {
				a[j][k] = a[i][k] * factor + a[j][k];
			}
			b[j] = b[i] * factor + b[j];
		}
	}
	
	double norma = determinante(a,b,x,filas);
	if(norma == 0.0){
		cout << "\n\nmatriz singular";
	}else{
		retrostutitucion(a, b, x, filas);
	}
}
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas){
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
	cout << "\n\n\n\nConjunto solución de coeficientes: \n";
	for (int i = 0; i < filas; ++i) {
		cout << "a" << i << " = " << x[i] << "\n";
	}
	
	cout << endl << endl << "Polinomio Interpolador P(x): \n";
	cout << "P(x) = ";
	
	for (int i = 0; i < filas; i++) {
		if (i == 0) {
			// Término independiente
			cout << x[i];
		} else {
			// Términos con potencias
			if (x[i] >= 0) {
				cout << " + ";
			} else {
				cout << " ";
			}
			
			if (i == 1) {
				cout << x[i] << "*x";
			} else {
				cout << x[i] << "*x^" << i;
			}
		}
	}
	cout << endl << endl;
	
	// Añadir opción para interpolar un valor
	double valorInterpolar;
	cout << "Ingrese el valor a interpolar: ";
	cin >> valorInterpolar;
	
	double resultado = 0;
	for (int i = 0; i < filas; i++) {
		resultado += x[i] * pow(valorInterpolar, i);
	}
	
	cout << "El valor interpolado para x = " << valorInterpolar << " es: " << resultado << endl;
}
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i){
	if (fabs(a[i][i]) < 0.0001) {
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
					cout << "Se realizo pivoteo\n";
					double swap = a[i][k];
					a[i][k] = a[j][k];
					a[j][k] = swap;
				}
				double swap = b[i];
				b[i] = b[j];
				b[j] = swap;
			}
		}
	}
}
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas){
	double norma = 1;
	for(int i = 0; i < filas ; i++){
		norma = norma * a[i][i];
	}
	return norma;
}

void mostrarPolinomio(double m[FILAS][2], int fila) {
    cout << "\n=== POLINOMIO INTERPOLADOR DE LAGRANGE ===" << endl;
    cout << "P(x) = ";
    
    for (int i = 0; i < fila; i++) {
        // Mostrar el coeficiente yi
        if (i > 0) {
            if (m[i][1] >= 0) {
                cout << " + ";
            } else {
                cout << " ";
            }
        }
        
        cout << m[i][1];
        
        // Mostrar los términos del polinomio base de Lagrange Li(x)
        bool primerTermino = true;
        for (int j = 0; j < fila; j++) {
            if (j != i) {
                if (primerTermino) {
                    cout << " * [";
                    primerTermino = false;
                } else {
                    cout << " * ";
                }
                
                // Mostrar (x - xj) / (xi - xj)
                cout << "(x";
                if (m[j][0] >= 0) {
                    cout << " - " << m[j][0];
                } else {
                    cout << " + " << -m[j][0];
                }
                cout << ") / (" << m[i][0];
                if (m[j][0] >= 0) {
                    cout << " - " << m[j][0];
                } else {
                    cout << " + " << -m[j][0];
                }
                cout << ")";
            }
        }
        
        if (!primerTermino) {
            cout << "]";
        }
        
        // Salto de línea después de cada término para mejor legibilidad
        if (i < fila - 1) {
            cout << endl << "     ";
        }
    }
    
    cout << endl << endl;
    
    // Versión simplificada del polinomio (sin mostrar las fracciones)
    cout << "=== FORMA SIMPLIFICADA ===" << endl;
    cout << "P(x) está compuesto por " << fila << " términos de Lagrange:" << endl;
    
    for (int i = 0; i < fila; i++) {
        cout << "L" << i << "(x) = ";
        
        // Calcular y mostrar el coeficiente numérico
        double coeficiente = m[i][1];
        for (int j = 0; j < fila; j++) {
            if (j != i) {
                coeficiente /= (m[i][0] - m[j][0]);
            }
        }
        
        cout << coeficiente;
        
        // Mostrar los términos (x - xj)
        for (int j = 0; j < fila; j++) {
            if (j != i) {
                cout << " * (x";
                if (m[j][0] >= 0) {
                    cout << " - " << m[j][0];
                } else {
                    cout << " + " << -m[j][0];
                }
                cout << ")";
            }
        }
        cout << endl;
    }
    
    cout << endl;
    
    // NUEVA SECCIÓN: POLINOMIO EN FORMA ESTÁNDAR
    cout << "\n=== POLINOMIO EN FORMA ESTÁNDAR ===" << endl;
    cout << "Expandiendo el polinomio de Lagrange..." << endl;
    
    // Calcular coeficientes del polinomio expandido
    double coeficientes[FILAS];
    for (int k = 0; k < fila; k++) {
        coeficientes[k] = 0.0;
    }
    
    // Para cada término de Lagrange Li(x) * yi
    for (int i = 0; i < fila; i++) {
        // Calcular el polinomio Li(x) expandido
        double terminos[FILAS];
        for (int k = 0; k < fila; k++) {
            terminos[k] = 0.0;
        }
        terminos[0] = 1.0; // Empezar con el polinomio constante 1
        
        // Multiplicar por cada factor (x - xj) / (xi - xj)
        for (int j = 0; j < fila; j++) {
            if (j != i) {
                double factor = 1.0 / (m[i][0] - m[j][0]);
                double raiz = m[j][0];
                
                // Multiplicar el polinomio actual por (x - raiz) * factor
                // Esto significa: terminos(x) = terminos(x) * (x - raiz) * factor
                double nuevosTerminos[FILAS];
                for (int k = 0; k < fila; k++) {
                    nuevosTerminos[k] = 0.0;
                }
                
                // terminos(x) * x * factor
                for (int k = 0; k < fila - 1; k++) {
                    nuevosTerminos[k + 1] += terminos[k] * factor;
                }
                
                // terminos(x) * (-raiz) * factor
                for (int k = 0; k < fila; k++) {
                    nuevosTerminos[k] += terminos[k] * (-raiz) * factor;
                }
                
                // Copiar de vuelta
                for (int k = 0; k < fila; k++) {
                    terminos[k] = nuevosTerminos[k];
                }
            }
        }
        
        // Multiplicar Li(x) por yi y sumar a los coeficientes totales
        for (int k = 0; k < fila; k++) {
            coeficientes[k] += terminos[k] * m[i][1];
        }
    }
    
    // Mostrar el polinomio en forma estándar
    cout << "P(x) = ";
    bool primerCoeficiente = true;
    
    // Recorrer desde la potencia más alta hacia la más baja
    for (int k = fila - 1; k >= 0; k--) {
        if (fabs(coeficientes[k]) > 1e-10) { // Solo mostrar coeficientes no nulos
            
            // Manejar signos
            if (!primerCoeficiente) {
                if (coeficientes[k] >= 0) {
                    cout << " + ";
                } else {
                    cout << " - ";
                    coeficientes[k] = -coeficientes[k]; // Hacer positivo para mostrar
                }
            } else {
                if (coeficientes[k] < 0) {
                    cout << "-";
                    coeficientes[k] = -coeficientes[k]; // Hacer positivo para mostrar
                }
                primerCoeficiente = false;
            }
            
            // Mostrar coeficiente y variable
            if (k == 0) {
                // Término independiente
                cout << coeficientes[k];
            } else if (k == 1) {
                // Término lineal
                if (fabs(coeficientes[k] - 1.0) > 1e-10) {
                    cout << coeficientes[k] << "*x";
                } else {
                    cout << "x";
                }
            } else {
                // Términos de potencia mayor
                if (fabs(coeficientes[k] - 1.0) > 1e-10) {
                    cout << coeficientes[k] << "*x^" << k;
                } else {
                    cout << "x^" << k;
                }
            }
        }
    }
    
    if (primerCoeficiente) {
        cout << "0"; // Polinomio nulo
    }
    
    cout << endl << endl;
    
    // Mostrar coeficientes individuales para verificación
    cout << "=== COEFICIENTES DEL POLINOMIO ===" << endl;
    cout << "P(x) = a₀ + a₁*x + a₂*x² + ... + aₙ*xⁿ" << endl;
    for (int k = 0; k < fila; k++) {
        if (fabs(coeficientes[k]) > 1e-10) {
            cout << "a" << k << " = " << coeficientes[k] << endl;
        }
    }
    
    cout << endl;
}

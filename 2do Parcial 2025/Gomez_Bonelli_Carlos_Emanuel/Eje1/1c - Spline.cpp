//spline cubica para Problema 1c

#include <iostream>
#include <math.h> 
#include <iomanip>
#include <cstdlib>
#define FILAS 100
#define COLUMNAS 100

using namespace std;

void buildMatrix(double m[FILAS][2], double a[FILAS][FILAS], double b[FILAS], int filas, int grado);
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado);
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado);
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);
double evaluarSpline(double m[FILAS][2], double coef[FILAS], int filas, int grado, double x);
void mostrarTablaEquiespaciada(double m[FILAS][2], double coef[FILAS], int filas, int grado);

int main(int argc, char *argv[]) {
    // Datos originales de la función f(x) = e^x sin x
    double datos_originales[7][2] = {
        {0.00, 0.0000},
        {0.20, 0.2426},
        {0.43, 0.6408},
        {0.55, 0.9059},
        {0.85, 1.7577},
        {0.90, 1.9267},
        {1.00, 2.2873}
    };
    
    int filas_originales = 7;
    int grado = 3; // Spline cúbico
    
    cout << "=== PROBLEMA 1c: INTERPOLACIÓN SPLINE CÚBICA NORMAL ===" << endl;
    cout << "Función: f(x) = e^x * sin x" << endl;
    cout << "Datos originales (7 puntos):" << endl;
    cout << "X\t\tY" << endl;
    cout << fixed << setprecision(4);
    for(int i = 0; i < filas_originales; i++){
        cout << datos_originales[i][0] << "\t\t" << datos_originales[i][1] << endl;
    }
    
    // Construir sistema para spline cúbica
    int n = filas_originales - 1;
    int coefPorTramo = grado + 1;
    int totalCoef = coefPorTramo * n;
    
    double a[FILAS][FILAS] = {{0}};
    double b[FILAS] = {0};
    double* x = (double*)malloc(totalCoef * sizeof(double));
    
    // Construir y resolver el sistema
    buildMatrix(datos_originales, a, b, filas_originales, grado);
    triangulacion(a, b, x, totalCoef, grado);
    
    cout << "\n=== TABLA DE 5 PUNTOS EQUIESPACIADOS ===" << endl;
    cout << "Obtenida por interpolación Spline Cúbica Normal:" << endl;
    cout << "X\t\tY" << endl;
    cout << fixed << setprecision(4);
    
    // Generar 5 puntos equiespaciados en [0,1]
    double puntos_equiespaciados[5] = {0.00, 0.25, 0.50, 0.75, 1.00};
    
    for(int i = 0; i < 5; i++){
        double x_val = puntos_equiespaciados[i];
        double y_val = evaluarSpline(datos_originales, x, filas_originales, grado, x_val);
        cout << x_val << "\t\t" << y_val << endl;
    }
    /*
    // Mostrar en formato array para código
    cout << "\n=== FORMATO ARRAY PARA CÓDIGO ===" << endl;
    cout << "double datos_spline[5][2] = {" << endl;
    for(int i = 0; i < 5; i++){
        double x_val = puntos_equiespaciados[i];
        double y_val = evaluarSpline(datos_originales, x, filas_originales, grado, x_val);
        cout << "    {" << fixed << setprecision(2) << x_val << ", " 
             << fixed << setprecision(4) << y_val << "}";
        if(i < 4) cout << ",";
        cout << endl;
    }
    cout << "};" << endl;
    */
    free(x);
    return 0;
}

double evaluarSpline(double m[FILAS][2], double coef[FILAS], int filas, int grado, double x) {
    int n = filas - 1;
    int coefPorTramo = grado + 1;
    double resultado = 0;
    
    if (x >= m[0][0] && x <= m[filas - 1][0]) {
        for (int i = 0; i < n; i++) {
            if(x >= m[i][0] && x <= m[i+1][0]) {
                for(int j = 0; j < coefPorTramo; j++) {
                    resultado += coef[coefPorTramo*i + j] * pow(x, grado - j);
                }
                break;
            }
        }
    }
    
    return resultado;
}

void buildMatrix(double m[FILAS][2], double a[FILAS][FILAS], double b[FILAS], int filas, int grado) {
    int n = filas - 1;
    int coefPorTramo = grado + 1;
    int totalCoef = coefPorTramo * n;
    
    // Construcción de las primeras 2n filas (condiciones de paso por puntos)
    for (int k = 0; k < n; k++) {
        for(int j = 0; j < coefPorTramo; j++) {
            a[2*k][coefPorTramo*k + j] = pow(m[k][0], grado - j);
            a[2*k + 1][coefPorTramo*k + j] = pow(m[k+1][0], grado - j);
        }
        b[2*k] = m[k][1];
        b[2*k + 1] = m[k + 1][1];
    }
    
    // Construcción de las condiciones de continuidad de derivadas
    int filaActual = 2 * n;
    for(int derivada = 1; derivada < grado; derivada++) {
        for(int k = 0; k < n - 1; k++) {
            for(int j = 0; j < coefPorTramo - derivada; j++) {
                double factorial = 1;
                for(int f = 0; f < derivada; f++) {
                    factorial *= (grado - j - f);
                }
                a[filaActual][coefPorTramo*k + j] = factorial * pow(m[k+1][0], grado - j - derivada);
                a[filaActual][coefPorTramo*(k+1) + j] = -factorial * pow(m[k+1][0], grado - j - derivada);
            }
            b[filaActual] = 0;
            filaActual++;
        }
    }
    
    // Condiciones de frontera naturales (solo segunda derivada para spline cúbico)
    // Para spline cúbico (grado == 3) fijamos S''(x0) = 0 y S''(xn) = 0
    if (grado >= 2) {
        int derivada = 2; // segunda derivada
        // En el primer punto
        for(int j = 0; j < coefPorTramo - derivada; j++) {
            double factorial = 1;
            for(int f = 0; f < derivada; f++) {
                factorial *= (grado - j - f);
            }
            // evitar pow(0,negativo)
            int expo = grado - j - derivada;
            double base = m[0][0];
            double p = (expo >= 0) ? pow(base, expo) : 0.0;
            a[filaActual][j] = factorial * p;
        }
        b[filaActual] = 0;
        filaActual++;

        // En el último punto
        for(int j = 0; j < coefPorTramo - derivada; j++) {
            double factorial = 1;
            for(int f = 0; f < derivada; f++) {
                factorial *= (grado - j - f);
            }
            int expo = grado - j - derivada;
            double base = m[n][0];
            double p = (expo >= 0) ? pow(base, expo) : 0.0;
            a[filaActual][coefPorTramo*(n-1) + j] = factorial * p;
        }
        b[filaActual] = 0;
        filaActual++;
    }
}

void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado) {
    for (int i = 0; i < (filas - 1); i++) {
        pivot(a, b, filas, i);
        for (int j = i + 1; j < filas; j++) {
            double factor = -a[j][i] / a[i][i];
            for (int k = 0; k < filas; ++k) {
                a[j][k] = a[i][k] * factor + a[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    
    double norma = determinante(a, b, x, filas);
    if(norma == 0.0) {
        cout << "\n\nMatriz singular" << endl;
        exit(EXIT_FAILURE); // no continuar con coeficientes no inicializados
    } else {
        retrostutitucion(a, b, x, filas, grado);
    }
}

void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado) {
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

void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i) {
    if (fabs(a[i][i]) < 0.0001) {
        for (int j = i + 1; j < filas; j++) {
            if (fabs(a[j][i]) > fabs(a[i][i])) {
                for (int k = i; k < filas; ++k) {
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

double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas) {
    double norma = 1;
    for(int i = 0; i < filas; i++) {
        norma = norma * a[i][i];
    }
    return norma;
}
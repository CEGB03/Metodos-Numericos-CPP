#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int N = 5; // Número de puntos en la tabla

// Estructura para almacenar los datos
struct Datos {
    double x[N];
    double y[N];
};

// Función para calcular interpolación de Lagrange
double lagrange(double punto, Datos datos) {
    double resultado = 0.0;
    
    for (int i = 0; i < N; i++) {
        double termino = datos.y[i];
        for (int j = 0; j < N; j++) {
            if (j != i) {
                termino *= (punto - datos.x[j]) / (datos.x[i] - datos.x[j]);
            }
        }
        resultado += termino;
    }
    return resultado;
}

// Función para mostrar el polinomio interpolador de Lagrange
void mostrarPolinomioLagrange(Datos datos) {
    cout << "\n=== POLINOMIO INTERPOLADOR DE LAGRANGE ===" << endl;
    cout << "P(x) = ";
    
    for (int i = 0; i < N; i++) {
        if (i > 0) {
            if (datos.y[i] >= 0) {
                cout << " + ";
            } else {
                cout << " ";
            }
        }
        
        cout << datos.y[i];
        
        for (int j = 0; j < N; j++) {
            if (j != i) {
                cout << " * [(x - " << datos.x[j] << ")/(" << datos.x[i] << " - " << datos.x[j] << ")]";
            }
        }
        
        if (i < N - 1) {
            cout << endl << "     ";
        }
    }
    cout << endl;
}

// Función para mostrar tabla de datos
void mostrarTabla(Datos datos) {
    cout << "TABLA DE DATOS:" << endl;
    cout << "x\t\tf(x)" << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << datos.x[i] << "\t\t" << datos.y[i] << endl;
    }
}

// Función para calcular coeficientes del polinomio estándar
void calcularPolinomioEstandar(Datos datos, double coeficientes[]) {
    for (int k = 0; k < N; k++) {
        coeficientes[k] = 0.0;
    }
    
    // Calcular coeficientes expandiendo el polinomio de Lagrange
    for (int i = 0; i < N; i++) {
        double termino[N] = {0.0};
        termino[0] = 1.0; // Polinomio constante 1
        
        double denominador = 1.0;
        
        // Construir el polinomio base Li(x)
        for (int j = 0; j < N; j++) {
            if (j != i) {
                denominador *= (datos.x[i] - datos.x[j]);
                
                // Multiplicar por (x - xj)
                double nuevo_termino[N] = {0.0};
                for (int k = 0; k < N - 1; k++) {
                    nuevo_termino[k + 1] += termino[k];      // x * termino[k]
                    nuevo_termino[k] += termino[k] * (-datos.x[j]); // -xj * termino[k]
                }
                
                // Copiar de vuelta a termino
                for (int k = 0; k < N; k++) {
                    termino[k] = nuevo_termino[k];
                }
            }
        }
        
        // Dividir por el denominador y sumar a los coeficientes totales
        for (int k = 0; k < N; k++) {
            coeficientes[k] += termino[k] * datos.y[i] / denominador;
        }
    }
}

// Función para mostrar polinomio en forma estándar
void mostrarPolinomioEstandar(double coeficientes[]) {
    cout << "\n=== POLINOMIO EN FORMA ESTÁNDAR ===" << endl;
    cout << "P(x) = ";
    bool primer_termino = true;
    
    for (int k = N - 1; k >= 0; k--) {
        if (fabs(coeficientes[k]) > 1e-8) {
            if (!primer_termino) {
                if (coeficientes[k] >= 0) {
                    cout << " + ";
                } else {
                    cout << " - ";
                }
            }
            
            double coef_mostrar = fabs(coeficientes[k]);
            
            if (k == 0) {
                cout << coef_mostrar;
            } else if (k == 1) {
                if (fabs(coef_mostrar - 1.0) > 1e-8) {
                    cout << coef_mostrar << "x";
                } else {
                    cout << "x";
                }
            } else {
                if (fabs(coef_mostrar - 1.0) > 1e-8) {
                    cout << coef_mostrar << "x^" << k;
                } else {
                    cout << "x^" << k;
                }
            }
            primer_termino = false;
        }
    }
    
    if (primer_termino) {
        cout << "0";
    }
    cout << endl;
    
    // Mostrar coeficientes numéricos
    cout << "\nCOEFICIENTES NUMÉRICOS:" << endl;
    cout << "P(x) = a₀ + a₁x + a₂x² + a₃x³ + a₄x⁴" << endl;
    for (int k = 0; k < N; k++) {
        cout << "a" << k << " = " << coeficientes[k] << endl;
    }
}

int main() {
    cout << "=== PROBLEMA 1c - POLINOMIO INTERPOLADOR ===" << endl;
    cout << "Función: f(x) = ln(x² + 1) - sin(x)" << endl;
    
    // Inicializar datos de la tabla
    Datos datos;
    double x_data[N] = {1.0, 1.2, 1.5, 1.75, 2.0};
    double y_data[N] = {-0.148, -0.040, 0.181, 0.419, 0.700};
    
    for (int i = 0; i < N; i++) {
        datos.x[i] = x_data[i];
        datos.y[i] = y_data[i];
    }
    
    // Mostrar tabla de datos
    mostrarTabla(datos);
    
    // Mostrar polinomio interpolador
    mostrarPolinomioLagrange(datos);
    
    // Calcular y mostrar polinomio en forma estándar
    double coeficientes[N];
    calcularPolinomioEstandar(datos, coeficientes);
    mostrarPolinomioEstandar(coeficientes);
    
    // Verificación con los puntos originales
    cout << "\n=== VERIFICACIÓN ===" << endl;
    cout << "x\t\tP(x)\t\tf(x)\t\tError" << endl;
    cout << "------------------------------------------------" << endl;
    
    for (int i = 0; i < N; i++) {
        double x_val = datos.x[i];
        double p_x = lagrange(x_val, datos);
        double f_x = datos.y[i];
        double error = fabs(p_x - f_x);
        
        cout << fixed << setprecision(3);
        cout << x_val << "\t\t" << p_x << "\t\t" << f_x << "\t\t" << error << endl;
    }
    
    return 0;
}
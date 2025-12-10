#include <iostream>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#define FILAS 20

using namespace std;

/**
 * FUNCIÓN DE PRUEBA
 * Función matemática f(x) = Q(t)² utilizada para demostrar los métodos
 * Su integral exacta es: ∫(Q(t)²)dx = Q(t)³/3 + C
 */
double funcion(double x){
    return (pow(x,2));
}

// Declaraciones de funciones
void trapecioFuncion();
bool sonEquidistantes(double arreglo[FILAS][2], int filas);
void leerDatos(double m[FILAS][2], int* filas);
void mostrarMenu();

int main(int argc, char *argv[]) {
    mostrarMenu();
    return 0;
}

void mostrarMenu(){
    int opcion;
    cout << "\n╔══════════════════════════════════════════════════╗" << endl;
    cout << "║        INTEGRACIÓN NUMÉRICA (NEWTON-COTES)       ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;
    cout << "2) 2. Trapecio - Tabla conocida" << endl;

    trapecioFuncion();
    cout << "¡Hasta luego!" << endl;
    
}

/**
 * MÉTODO DEL TRAPECIO CON FUNCIÓN CONOCIDA
 * Integra numéricamente f(x) = x² + 1 usando la regla del trapecio
 * Divide [a,b] en n subintervalos y aproxima con trapecios
 */
void trapecioFuncion(){
    double a = 0 , b = 5;
    int n = 10; 
    cout << "\n REGLA DEL TRAPECIO - FUNCIÓN CONOCIDA" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "Función: f(x) = x² + 1" << endl;
    cout << "Límite inferior (a): " << a << endl;
    //cin >> a;
    cout << "Límite superior (b): " << b << endl;
    //cin >> b;
    cout << "Número de subintervalos (n): " << n << endl;
    //cin >> n;
    
    double h = (b-a)/n;
    double suma = funcion(a) + funcion(b);
    
    cout << "\n Cálculo paso a paso:" << endl;
    cout << "h = (b-a)/n = (" << b << "-" << a << ")/" << n << " = " << h << endl;
    cout << "f(a) = f(" << a << ") = " << funcion(a) << endl;
    cout << "f(b) = f(" << b << ") = " << funcion(b) << endl;
    
    for(int i = 1; i < n; i++){
        double xi = a + i*h;
        double fi = funcion(xi);
        suma += 2 * fi;
        cout << "2·f(" << xi << ") = 2·" << fi << " = " << (2*fi) << endl;
    }
    
    double integral = (h/2) * suma;
    
    cout << fixed << setprecision(6);
    cout << "\n RESULTADOS:" << endl;
    cout << "────────────────────────────────────────" << endl;
    cout << "Paso (h): " << h << endl;
    cout << "Suma total: " << suma << endl;
    cout << "∫[" << a << "," << b << "] f(x)dx ≈ " << integral << endl;
    
    // Calcular valor exacto para comparación
    double exacto = (pow(b,3)/3 + b) - (pow(a,3)/3 + a);
    cout << "Valor exacto: " << exacto << endl;
    cout << "Error absoluto: " << fabs(integral - exacto) << endl;
    cout << "Error relativo: " << (fabs(integral - exacto)/fabs(exacto))*100 << "%" << endl;
}

/**
 * FUNCIÓN AUXILIAR: Verificar si los puntos están equidistantes
 * Importante para determinar si se puede aplicar Simpson
 */
bool sonEquidistantes(double arreglo[FILAS][2], int filas){
    if(filas < 2) return true;
    
    double diferencia = arreglo[1][0] - arreglo[0][0];
    const double tolerancia = 1e-10;  // Tolerancia para errores de redondeo
    
    for(int i = 1; i < filas - 1; i++) {
        double diff_actual = arreglo[i + 1][0] - arreglo[i][0];
        if(fabs(diff_actual - diferencia) > tolerancia) {
            return false;
        }
    }
    return true;
}
#include <iostream>
#include <math.h>
#include <iomanip>
#define FILAS 20

using namespace std;

void printMatrizA(double a[FILAS][FILAS], int filas){
	cout << "\nMatriz A:\n";
	for(int i = 0 ; i < filas ; i++){
		for(int j = 0 ; j < 2 ; j++){
			cout << "\t" << a[i][j];
		}
		cout << endl;
	}
}

/**
 * FUNCIÓN DE PRUEBA
 * Función matemática f(x) = x² + 1 utilizada para demostrar los métodos
 * Su integral exacta es: ∫(x² + 1)dx = x³/3 + x + C
 */
double funcion(double x){
    return 1.481841*pow(x, 1.57181);
}

// Declaraciones de funciones
void simpsonCompuestoFuncion();
void simpsonCompuestoTabla();
bool sonEquidistantes(double arreglo[FILAS][2], int filas);
void leerDatos(double m[FILAS][2], int* filas);
void mostrarMenu();

int main(int argc, char *argv[]) {
    mostrarMenu();
    return 0;
}

void mostrarMenu(){
    int opcion;
    bool salir = false;
    
    while(!salir) {
        cout << "\n╔══════════════════════════════════════════════════╗" << endl;
        cout << "║        INTEGRACIÓN NUMÉRICA (NEWTON-COTES)       ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝" << endl;
        cout << "3. Simpson Compuesto - Función conocida" << endl;
        cout << "4. Simpson Compuesto - Tabla de datos" << endl;
        /* cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion; */
    
        simpsonCompuestoFuncion();
        cout << "¡Hasta luego!" << endl; salir = true;
    }
}

/**
 * MÉTODO DE SIMPSON COMPUESTO CON FUNCIÓN CONOCIDA
 * Integra usando parábolas para mayor precisión
 * Requiere número PAR de subintervalos
 */
void simpsonCompuestoFuncion(){
    double a=1, b=5;
    int n=4; 
    
    cout << "\n🔧 REGLA DE SIMPSON COMPUESTO - FUNCIÓN CONOCIDA" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    /* cout << "Función: f(x) = x² + 1" << endl; */
    /* cout << "Límite inferior (a): ";
    cin >> a;
    cout << "Límite superior (b): ";
    cin >> b;
    cout << "Número de subintervalos (n): ";
    cin >> n; */
    
    if(n <= 0) {
        cout << "❌ Error: El número de subintervalos debe ser positivo" << endl;
        return;
    }
    
    if(a >= b) {
        cout << "❌ Error: El límite inferior (a) debe ser menor que el superior (b)" << endl;
        return;
    }
    
    if(n % 2 != 0) {
        cout << "❌ Error: El número de intervalos debe ser PAR para Simpson" << endl;
        cout << "💡 Sugerencia: Use " << (n+1) << " o " << (n-1) << " intervalos" << endl;
        return;
    }
    
    double h = (b-a)/n;
    double suma = funcion(a) + funcion(b);
    
    cout << "\n📊 Cálculo paso a paso:" << endl;
    cout << "h = (b-a)/n = (" << b << "-" << a << ")/" << n << " = " << h << endl;
    cout << "f(a) + f(b) = f(" << a << ") + f(" << b << ") = " << funcion(a) << " + " << funcion(b) << " = " << suma << endl;
    cout << "Patrón de coeficientes: 1-4-2-4-2-...-4-1" << endl;
    
    for(int i = 1; i <= n-1; i++){
        double x = a + i * h;
        double fx = funcion(x);
        if(i % 2 == 1){
            suma += 4 * fx;
            cout << "4·f(" << x << ") = 4·" << fx << " = " << (4*fx) << " (índice impar)" << endl;
        } else {
            suma += 2 * fx;
            cout << "2·f(" << x << ") = 2·" << fx << " = " << (2*fx) << " (índice par)" << endl;
        }
    }
    
    double integral = (h/3) * suma;
    
    cout << fixed << setprecision(6);
    cout << "\n✅ RESULTADOS:" << endl;
    cout << "────────────────────────────────────────" << endl;
    cout << "Paso (h): " << h << endl;
    cout << "Suma total: " << suma << endl;
    cout << "∫[" << a << "," << b << "] f(x)dx ≈ " << integral << endl;
    
    // Valor exacto
    double exacto = (pow(b,3)/3 + b) - (pow(a,3)/3 + a);
    cout << "Valor exacto: " << exacto << endl;
    cout << "Error absoluto: " << fabs(integral - exacto) << endl;
    cout << "Error relativo: " << (fabs(integral - exacto)/fabs(exacto))*100 << "%" << endl;
    cout << "⭐ Nota: Simpson es exacto para polinomios de grado ≤ 3" << endl;
}
